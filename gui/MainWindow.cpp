#include "MainWindow.h"
#include "ui_mainwindow.h"
#include "DatabaseOptions.h"
#include "CreateClient.h"
#include "ClientData.h"

QSettings* settings;

MainWindow::MainWindow(QWidget* parent) :
	ui(new Ui::MainWindow){

	settings = new QSettings("Ty", "Abaci");
	ui->setupUi(this);
	QMenuBar* menuBar = this->menuBar();
		{
			QMenu* fileMenu = new QMenu("&Program");
			QAction* minimize = new QAction("Minimize");
			connect(minimize, &QAction::triggered, this, &MainWindow::showMinimized);
			fileMenu->addAction(minimize);

			QAction* exit = new QAction("Exit", this);
			connect(exit, &QAction::triggered, this, &MainWindow::close);
			fileMenu->addAction(exit);
	
		menuBar->addMenu(fileMenu);
		menuBar->show();
		}
		{
				QMenu* sessionMenu = new QMenu("&Session",this);
				QMenu* clientMenu = new QMenu("&Clients",this);
				
				QAction* edit = new QAction("&View selected client",this);
				connect(edit, &QAction::triggered, this, &MainWindow::showClientDetails);
				clientMenu->addAction(edit);

				QAction* kick = new QAction("&Kick selected client",this);
				connect(edit, &QAction::triggered, this, &MainWindow::btnKickClient);
				clientMenu->addAction(kick);

				sessionMenu->addMenu(clientMenu);

				menuBar->addMenu(sessionMenu);
		}
		{
				QMenu* databaseMenu = new QMenu("&Database", this);
				QMenu* clientMenu = new QMenu("&Clients", this);

				QAction* edit = new QAction("&View selected client", this);
				connect(edit, &QAction::triggered, this, &MainWindow::showClientDetailsDB);
				clientMenu->addAction(edit);
				
				QAction* actionDelete = new QAction("&Delete selected client", this); // 'delete' is a reserved keyword
				connect(actionDelete, &QAction::triggered, this, &MainWindow::deleteClient);
				clientMenu->addAction(actionDelete);

				QAction* create = new QAction("&Create client", this);
				connect(create, &QAction::triggered, this, &MainWindow::showCreateClient);
				clientMenu->addAction(create);
				databaseMenu->addMenu(clientMenu);

				
				menuBar->addMenu(databaseMenu);
		}
		{

		}

	ui->tableClients->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	
	
	ui->tableResults->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	
	ui->tableSessionClients->insertColumn(ui->tableSessionClients->columnCount());
	ui->tableSessionClients->insertColumn(ui->tableSessionClients->columnCount());
	ui->tableSessionClients->insertColumn(ui->tableSessionClients->columnCount());
	ui->tableSessionClients->insertColumn(ui->tableSessionClients->columnCount());
	ui->tableSessionClients->insertColumn(ui->tableSessionClients->columnCount());

	ui->tableSessionClients->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->tableSessionClients->setHorizontalHeaderLabels(QStringList({ "ID","Username","Work Completed","Processor Count","Processor Info","Platform" }));

	ui->statusbar->setStyleSheet("color: green");
	if (settings->value("DatabaseConfigured", false).toBool() || settings->value("Databaseless",false).toBool()) {
		if (settings->value("Databaseless").toBool()) {
			ui->statusbar->showMessage("Welcome to Abaci server, running with no database!",5000);
			ui->btnDeleteClient->setDisabled(true);
			ui->tableClients->setDisabled(true);
			ui->tableResults->setDisabled(true);
			ui->btnClientDetailsDB->setDisabled(true);
			ui->chkRefresh->setDisabled(true);
			ui->numRefreshSeconds->setDisabled(true);
			ui->btnReload->setDisabled(true);
		}
		else {
		ui->statusbar->showMessage("Welcome to Abaci Server, Connecting to Database", 5000);
		QtConcurrent::run(this, &MainWindow::ConnectSQL);
		connect(ui->btnDeleteClient, &QPushButton::clicked, this, &MainWindow::deleteClient);
		connect(ui->btnClientDetailsDB, &QPushButton::clicked, this, &MainWindow::showClientDetailsDB);
		connect(ui->btnCreateAClient, &QPushButton::clicked, this, &MainWindow::showCreateClient);
		}
		connect(ui->btnReload, &QPushButton::clicked, this, &MainWindow::refresh);
		connect(ui->btnConfigureDatabase, &QPushButton::clicked, this, &MainWindow::showDatabase);
		connect(ui->chkRefresh, &QCheckBox::clicked, this, &MainWindow::chkRefreshClicked);
		connect(ui->numRefreshSeconds, qOverload<int>(&QSpinBox::valueChanged), this, &MainWindow::refreshNumChanged);
		connect(ui->btnKickClient, &QCheckBox::clicked, this, &MainWindow::btnKickClient);
		QtConcurrent::run(this, &MainWindow::ScanIps);
	}
	else
	{
		QMessageBox msgUseDatabase(this);
		msgUseDatabase.setText(QString("When running Abaci server you can either run it with a database or databaseless\n") +
			"Warning: when running databaseless, Abaci doesn't store results on disk, only memory, and there is no authentication!\n" +
			"[Yes] - Run with database | [No] Run databaseless");
		msgUseDatabase.addButton(QMessageBox::Yes);
		msgUseDatabase.addButton(QMessageBox::No);
		msgUseDatabase.setWindowTitle("Showing first time configuration prompt");
		if (msgUseDatabase.exec() == QMessageBox::Yes) {
			settings->setValue("Databaseless", false);
			QApplication::processEvents();
			showDatabase();
		}
		else
		{
			settings->setValue("Databaseless", true);
		}
		ui->tableClients->resizeColumnsToContents();
	}
}

MainWindow::~MainWindow() {
	delete ui;
	delete settings;
}

void MainWindow::refresh() {
	if (settings->value("Databaseless").toBool()) {
		ui->btnDeleteClient->setDisabled(true);
		ui->tableClients->setDisabled(true);
		ui->tableResults->setDisabled(true);
		ui->btnClientDetailsDB->setDisabled(true);
		ui->chkRefresh->setDisabled(true);
		ui->numRefreshSeconds->setDisabled(true);
		ui->btnReload->setDisabled(true);
	}
	else {
		ui->btnDeleteClient->setDisabled(false);
		ui->tableClients->setDisabled(false);
		ui->tableResults->setDisabled(false);
		ui->btnClientDetailsDB->setDisabled(false);
		ui->chkRefresh->setDisabled(false);
		ui->numRefreshSeconds->setDisabled(false);
		ui->btnReload->setDisabled(false);

		if (resultTable == nullptr)
			resultTable = new QSqlTableModel(this,managerDB->DB);
		resultTable->clear();
		resultTable->setTable(settings->value("DatabaseResultsTable").toString());
		resultTable->setSort(0, Qt::SortOrder::DescendingOrder);
		resultTable->setEditStrategy(QSqlTableModel::OnManualSubmit);
		resultTable->select();

		
		QSqlQuery selectQuery(managerDB->DB);
		selectQuery.prepare("SELECT TOP (1) Prime FROM " + settings->value("DatabaseResultsTable").toString() + " ORDER BY ID DESC ");
		selectQuery.exec();
		selectQuery.next();
		maxPrime = selectQuery.value("Prime").toDouble();
		if (maxPrime < 0)
			emit gdhReady(0);
		else
			emit gdhReady(maxPrime);
		ui->tableResults->setModel(resultTable);
		ui->tableResults->resizeColumnsToContents();

		if (clientTable != nullptr)
			delete clientTable;
		clientTable = new QSqlTableModel(this, managerDB->DB);
		clientTable->setTable(settings->value("DatabaseClientTable").toString());
		clientTable->setEditStrategy(QSqlTableModel::OnManualSubmit);
		clientTable->select();
		clientTable->setHeaderData(0, Qt::Horizontal, tr("ID"));
		clientTable->removeColumns(2, 2);
		ui->tableClients->setModel(clientTable);
		ui->tableClients->resizeColumnsToContents();
	}

	QtConcurrent::run(this, &MainWindow::ScanIps);
}

void MainWindow::exit() {
	this->exit();
}

void MainWindow::ConnectSQL() {
	managerDB = new SQLServer(
		settings->value("DatabaseUsername").toString().toStdString(),
		settings->value("DatabasePassword").toString().toStdString(),
		settings->value("DatabaseHostname").toString().toStdString(),
		settings->value("DatabasePort").toString().toStdString(),
		settings->value("DatabaseName").toString().toStdString());

	QMetaObject::invokeMethod(this, "sqlStatusUpdate",
		Q_ARG(bool, managerDB->Connected()));
	QApplication::processEvents();
}

void MainWindow::sqlStatusUpdate(bool success) {

	if (success) {
		sqlConnected = true;
		ui->statusbar->setStyleSheet("color: green");
		ui->statusbar->showMessage("Connected to database!", 5000);
	
		QSqlTableModel* model = new QSqlTableModel(this, managerDB->DB);
		model->setTable(settings->value("DatabaseClientTable").toString());
		model->setEditStrategy(QSqlTableModel::OnManualSubmit);
		model->select();
		model->setHeaderData(0, Qt::Horizontal, tr("ID"));
		model->removeColumns(2, 2);
		ui->tableClients->setModel(model);
		ui->tableClients->resizeColumnsToContents();

		QSqlTableModel* resultModel = new QSqlTableModel(this, managerDB->DB);
		resultModel->setTable(settings->value("DatabaseResultsTable").toString());
		resultModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
		resultModel->select();
		
		ui->tableResults->setModel(resultModel);
		ui->tableResults->resizeColumnsToContents();
		refresh();
	}
	else {
		ui->statusbar->setStyleSheet("color: red");
		ui->statusbar->showMessage("Unable to connect to database! Please configure the database", 5000);
	}
}

void MainWindow::showDatabase() {
	auto* dboptions = new DatabaseOptions(this);
	dboptions->setVisible(true);
}

void MainWindow::ScanIps() {
	// This function is executed on a different thread to prevent UI blocks
	QString internalIps;
	for (auto& interface : QNetworkInterface::allInterfaces()) {
		if (interface.flags().testFlag(QNetworkInterface::IsUp) && !interface.flags().testFlag(QNetworkInterface::IsLoopBack))
			for (auto& entry : interface.addressEntries()) {
				if (interface.hardwareAddress() != "00:00:00:00:00:00" && entry.ip().toString().contains(".") && !interface.humanReadableName().contains("VM"))
					internalIps.append(entry.ip().toString() + ", ");
			}
	}

	QMetaObject::invokeMethod(this, "IpUpdate",
		Q_ARG(QString, internalIps));
}

void MainWindow::IpUpdate(QString ip_string_internal) {
	ui->lblInternalIps->setText(ip_string_internal);
}

void MainWindow::showClientDetails() {
	if (!ui->tableSessionClients->selectionModel()->hasSelection() || ui->tableSessionClients->selectionModel()->selectedRows().count() == 0) {
		QMessageBox msgInvalidSelected(this);
		msgInvalidSelected.setWindowTitle("Invalid Selection");
		msgInvalidSelected.setText("Invalid selection for connected clients list, please select a full row");
		msgInvalidSelected.exec();
	}

	const auto selectedRow = ui->tableSessionClients->selectionModel()->selection().indexes();
	const auto tableModel = ui->tableSessionClients->model();
	auto* singleClientData = new SingleClientData();
	singleClientData->ID = tableModel->data(selectedRow.at(0)).toUInt();
	singleClientData->Username = tableModel->data(selectedRow.at(1)).toString();
	singleClientData->WorkCompleted = tableModel->data(selectedRow.at(2)).toUInt();
	singleClientData->ProcessorInfo = tableModel->data(selectedRow.at(3)).toString();
	singleClientData->ProcessorCoreCount = tableModel->data(selectedRow.at(4)).toUInt();
	singleClientData->Platform = tableModel->data(selectedRow.at(5)).toString();

	ClientData* clientDataForm = new ClientData(singleClientData, QSqlDatabase::cloneDatabase(this->managerDB->DB, "ClientDataDB"));
	clientDataForm->setWindowModality(Qt::ApplicationModal);
	clientDataForm->setVisible(true);
}

void MainWindow::showClientDetailsDB() {
	if (!ui->tableClients->selectionModel()->hasSelection() || ui->tableClients->selectionModel()->selectedRows().count() == 0) {
		QMessageBox msgInvalidSelected(this);
		msgInvalidSelected.setWindowTitle("Invalid Selction");
		msgInvalidSelected.setText("Invalid selection for database client list, please select a full row");
		msgInvalidSelected.exec();
	}

	const auto selectedRow = ui->tableClients->selectionModel()->selection().indexes();
	const auto tableModel = ui->tableClients->model();
	auto* singleClientData = new SingleClientData();
	singleClientData->ID = tableModel->data(selectedRow.at(0)).toUInt();
	singleClientData->Username = tableModel->data(selectedRow.at(1)).toString();
	singleClientData->WorkCompleted = tableModel->data(selectedRow.at(2)).toUInt();
	singleClientData->ProcessorInfo = tableModel->data(selectedRow.at(3)).toString();
	singleClientData->ProcessorCoreCount = tableModel->data(selectedRow.at(4)).toUInt();
	singleClientData->Platform = tableModel->data(selectedRow.at(5)).toString();

	ClientData* clientDataForm = new ClientData(singleClientData, QSqlDatabase::cloneDatabase(this->managerDB->DB, "ClientDataDB"));
	clientDataForm->setWindowModality(Qt::ApplicationModal);
	clientDataForm->setVisible(true);
}

void MainWindow::deleteClient() {
	if (!ui->tableClients->selectionModel()->hasSelection() || ui->tableClients->selectionModel()->selectedRows().count() == 0) {
		QMessageBox msgInvalidSelected(this);
		msgInvalidSelected.setWindowTitle("Invalid Selection");
		msgInvalidSelected.setText("Invalid selection for clients list, please select a full row to delete a client");
		msgInvalidSelected.exec();
	}

	const auto selectedRow = ui->tableClients->selectionModel()->selection().indexes();
	const auto tableModel = ui->tableClients->model();
	
	auto clientID = tableModel->data(selectedRow.at(0)).toUInt();

	QSqlQuery query = QSqlQuery(managerDB->DB);
	query.prepare(QString("DELETE FROM %1 WHERE ID=%2").arg(settings->value("DatabaseClientTable").toString()).arg(clientID));
	if (!query.exec()) {
		QMessageBox(QMessageBox::Icon::Critical, "Error when deleting client", query.lastError().text(), QMessageBox::Ok).exec();
	}
	refresh();
}

bool MainWindow::tryAuth(QString username, QString password) {
	QSqlQuery fetchQuery(managerDB->DB);
	fetchQuery.prepare("SELECT * FROM " + settings->value("DatabaseClientTable").toString() + " WHERE Username=:username");
	fetchQuery.bindValue(":username", username);
	fetchQuery.exec();

	if (fetchQuery.size() == 0) // If no clients are in the database with that username
		return false;
	fetchQuery.next();

	QString HashedPass = fetchQuery.value("HashedPassword").toString();
	QString salt = fetchQuery.value("PasswordSalt").toString();
	QString givenPass = SQLServer::hashPass(password, salt);
	if (givenPass != HashedPass)
		return false;
	else
		return true; 

}

int MainWindow::getClientID(QString username) {
	QSqlQuery fetchQuery(managerDB->DB);
	fetchQuery.prepare("SELECT * FROM " + settings->value("DatabaseClientTable").toString() + " WHERE Username=:username");
	fetchQuery.bindValue(":username", username);
	fetchQuery.exec();

	if (fetchQuery.size() == 0)
		return -1;
	fetchQuery.next();
	return fetchQuery.value("ID").toInt();
}

bool MainWindow::resetPassword(QString username, QString newPassword) {
	QSqlQuery fetchQuery(managerDB->DB);
	fetchQuery.prepare("SELECT PasswordSalt FROM " + settings->value("DatabaseClientTable").toString() + " WHERE Username=:username");
	fetchQuery.bindValue(":username",username);
	fetchQuery.exec();

	if (fetchQuery.size() == 0)
		return false;

	fetchQuery.next();
	QString newHashedPassword = SQLServer::hashPass(newPassword, fetchQuery.value("PasswordSalt").toString());

	QSqlQuery updateQuery(managerDB->DB);
	updateQuery.prepare("UPDATE " + settings->value("DatabaseClientTable").toString() + " SET HashedPassword=:newHashedPassword WHERE Username=:username");
	updateQuery.bindValue(":newHashedPassword", newHashedPassword);
	updateQuery.bindValue(":username", username);

	std::cout << updateQuery.lastError().text().toStdString() << std::endl;
	return updateQuery.exec();
}

int MainWindow::getWorkCompleted(QString username) {
	QSqlQuery fetchQuery(managerDB->DB);
	fetchQuery.prepare("SELECT WorkCompleted FROM " + settings->value("DatabaseClientTable").toString() + " WHERE Username=:username");
	fetchQuery.bindValue(":username", username);

	fetchQuery.exec();

	if (fetchQuery.size() == 0)
		return -1;

	fetchQuery.next();

	return fetchQuery.value("WorkCompleted").toInt();
}

QString MainWindow::getProcessorInfo(QString username) {
	QSqlQuery fetchQuery(managerDB->DB);
	fetchQuery.prepare("SELECT ProcessorInfo FROM " + settings->value("DatabaseClientTable").toString() + " WHERE Username=:username");
	fetchQuery.bindValue(":username", username);

	fetchQuery.exec();

	if (fetchQuery.size() == 0)
		return "";

	fetchQuery.next();

	return fetchQuery.value("ProcessorInfo").toString();
}

int MainWindow::getProcessorCoreCount(QString username) {
	QSqlQuery fetchQuery(managerDB->DB);
	fetchQuery.prepare("SELECT ProcessorCoreCount FROM " + settings->value("DatabaseClientTable").toString() + " WHERE Username=:username");
	fetchQuery.bindValue(":username", username);

	fetchQuery.exec();

	if (fetchQuery.size() == 0)
		return -1;

	fetchQuery.next();

	return fetchQuery.value("ProcessorCoreCount").toInt();
}

QString MainWindow::getPlatform(QString username) {
	QSqlQuery fetchQuery(managerDB->DB);
	fetchQuery.prepare("SELECT Platform FROM " + settings->value("DatabaseClientTable").toString() + " WHERE Username=:username");
	fetchQuery.bindValue(":username", username);

	fetchQuery.exec();

	if (fetchQuery.size() == 0)
		return "";

	fetchQuery.next();

	return fetchQuery.value("Platform").toString();
}

bool MainWindow::checkUserExists(QString username) {
	QSqlQuery fetchQuery(managerDB->DB);
	fetchQuery.prepare("SELECT * FROM " + settings->value("DatabaseClientTable").toString() + " WHERE Username=:username");
	fetchQuery.bindValue(":username", username);

	fetchQuery.exec();
	
	if (fetchQuery.next())
		return true;

	return false;
}

bool MainWindow::setClientUsername(QString username, QString newUsername) {
	QSqlQuery updateQuery(managerDB->DB);
	updateQuery.prepare("UPDATE " + settings->value("DatabaseClientTable").toString() + " SET Username=:newUsername WHERE Username=:username");
	updateQuery.bindValue(":newUsername", newUsername);
	updateQuery.bindValue(":username", username);

	return updateQuery.exec();
}

bool MainWindow::setClientProcessorInfo(QString username, QString newProcessorInfo) {
	QSqlQuery updateQuery(managerDB->DB);
	updateQuery.prepare("UPDATE  " + settings->value("DatabaseClientTable").toString() + " SET ProcessorInfo=:newProcessorInfo WHERE Username=:username");
	updateQuery.bindValue(":newProcessorInfo", newProcessorInfo);
	updateQuery.bindValue(":username", username);

	return updateQuery.exec();
}

bool MainWindow::setClientPlatform(QString username, QString newPlatform) {
	QSqlQuery updateQuery(managerDB->DB);
	updateQuery.prepare("UPDATE  " + settings->value("DatabaseClientTable").toString() + " SET Platform=:newPlatform WHERE Username=:username");
	updateQuery.bindValue(":newPlatform", newPlatform);
	updateQuery.bindValue(":username", username);

	return updateQuery.exec();
}

bool MainWindow::deleteClientOnClientRequest(QString username) {
	QSqlQuery deleteQuery(managerDB->DB);
	deleteQuery.prepare("DELETE FROM " + settings->value("DatabaseClientTable").toString() + " WHERE Username=:username");
	deleteQuery.bindValue(":username", username);

	return deleteQuery.exec();
}

void MainWindow::addResult(std::vector<double> result, int clientID) {

	QString primeValues;
	for (auto& prime : result) {
		primeValues.append("(" + QString::number(prime,'f') + "," + QString::number(clientID) + ",GETDATE()),");
	}
	primeValues.remove(primeValues.size() - 1, 1);
		QSqlQuery insertQuery(managerDB->DB);
		insertQuery.prepare("INSERT INTO " + settings->value("DatabaseResultsTable").toString() + "(Prime,ClientVerified,DateFound) VALUES " + primeValues);
		insertQuery.bindValue(":clientID", clientID);
		insertQuery.bindValue(":now", QDateTime::currentDateTime());
		insertQuery.exec();
		QSqlQuery updateQuery(managerDB->DB);
		updateQuery.prepare("UPDATE " + settings->value("DatabaseClientTable").toString() + " SET WorkCompleted = WorkCompleted + :wcCount WHERE ID = :clID");
		updateQuery.bindValue(":wcCount", result.size());
		updateQuery.bindValue(":clID", clientID);
		updateQuery.exec();
	QApplication::processEvents();
	

}

void MainWindow::requestMaxPrime(double* prime) {
	if(settings->value("Databaseless").toBool())
	*prime = maxPrime;
	else {
		while (sqlConnected && managerDB->Connected() == false) {
			QApplication::processEvents();
		}
		*prime = maxPrime;
	}
}

void MainWindow::clientConnected(const QString &username) {
	QString id = "???";
	QString wc = "???";
	QString cpucount= "???";
	QString cpuinfo = "???";
	QString platform = "???";
	if (checkUserExists(username))
	{
		id = QString::number(getClientID(username));
		wc = QString::number(getWorkCompleted(username));
		cpucount = QString::number(getProcessorCoreCount(username));
		cpuinfo = getProcessorInfo(username);
		platform = getPlatform(username);
	}

	ui->tableSessionClients->insertRow(ui->tableSessionClients->rowCount());
	ui->tableSessionClients->setItem(ui->tableSessionClients->rowCount() - 1,0,
		new QTableWidgetItem(id));
	ui->tableSessionClients->setItem(ui->tableSessionClients->rowCount() - 1, 1,
		new QTableWidgetItem(username));
	ui->tableSessionClients->setItem(ui->tableSessionClients->rowCount() - 1, 2,
		new QTableWidgetItem(wc));
	ui->tableSessionClients->setItem(ui->tableSessionClients->rowCount() - 1, 3,
		new QTableWidgetItem(cpucount));
	ui->tableSessionClients->setItem(ui->tableSessionClients->rowCount() - 1, 4,
		new QTableWidgetItem(cpuinfo));
	ui->tableSessionClients->setItem(ui->tableSessionClients->rowCount() - 1, 5,
		new QTableWidgetItem(platform));
}

void MainWindow::showCreateClient() {
	CreateClient *createClient = new CreateClient(QSqlDatabase::cloneDatabase(this->managerDB->DB, "CreateClientDB"));
	connect(createClient, &CreateClient::clientCreated, this, &MainWindow::refresh);
	createClient->setWindowModality(Qt::WindowModality::ApplicationModal);
	createClient->show();
}

void MainWindow::clientDisconnected(const QString& username) {
	for (int row = 0; row < ui->tableSessionClients->rowCount(); row++) {
		if (ui->tableSessionClients->item(row, 1)->data(Qt::DisplayRole).toString() == username) {
			ui->tableSessionClients->removeRow(row);
		}
	}
}

void MainWindow::closeEvent(QCloseEvent* event) {
	emit onCloseEvent(event);
	refreshDelay = 0;
}

void MainWindow::refreshLoop() {
	while (refreshDelay != 0) { // When refresh delay is 0, that means that the user does not want the auto refresh function
		QMetaObject::invokeMethod(this, "refresh");
		QThread::sleep(refreshDelay);
	}
}

void MainWindow::chkRefreshClicked(bool checked) {
	if (checked) {
		refreshDelay = ui->numRefreshSeconds->value();
		QtConcurrent::run(this, &MainWindow::refreshLoop);
	}
	else
		refreshDelay = 0;
}

void MainWindow::refreshNumChanged(int newValue) {
	refreshDelay = newValue;
}

void MainWindow::btnKickClient() {
		if (!ui->tableSessionClients->selectionModel()->hasSelection() || ui->tableSessionClients->selectionModel()->selectedRows().count() == 0) {
			QMessageBox msgInvalidSelected(this);
			msgInvalidSelected.setWindowTitle("Invalid Selection");
			msgInvalidSelected.setText("Pleas select a full row to be able to kick a client");
			msgInvalidSelected.exec();
			return;
		}

		const auto selectedRow = ui->tableSessionClients->selectionModel()->selection().indexes();
		const auto tableModel = ui->tableSessionClients->model();
		emit kickClientRequest(tableModel->data(selectedRow.at(1)).toString());
}
