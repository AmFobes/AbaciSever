#include "DatabaseOptions.h"
#include "ui_databaseoptions.h"
#include "sqlServer.h"
#include <QtCore>
#include <QSqlQuery>
#include <QMessageBox>

DatabaseOptions::DatabaseOptions(QWidget* parent) :
	ui(new Ui::DatabaseOptions), parent(parent){
	
	ui->setupUi(this);
	ui->lstTestConnection->setVisible(false);

	if (settings->value("DatabaseConfigured", false).toBool())
	{
		// If the database is configured
		ui->txtHostname->setText(settings->value("DatabaseHostname").toString());
		ui->txtDatabase->setText(settings->value("DatabaseName").toString());
		ui->numPort->setValue(settings->value("DatabasePort", 1433).toInt());
		ui->txtUsername->setText(settings->value("DatabaseUsername").toString());
		ui->txtPassword->setText(settings->value("DatabasePassword").toString());
	}
	
	connect(ui->btnNext, &QPushButton::clicked, this, &DatabaseOptions::nextButtonClicked);
	connect(ui->btnBack, &QPushButton::clicked, this, &DatabaseOptions::backButtonClicked);
	connect(ui->btnCancel, &QPushButton::clicked, this, &DatabaseOptions::close);
	connect(ui->chkShowPassword, &QCheckBox::stateChanged, this, &DatabaseOptions::showpassButtonClicked);
	connect(ui->wizardPanel, &QStackedWidget::currentChanged, this, &DatabaseOptions::wizardPanelChanged);
	connect(ui->btnTestConnection, &QPushButton::clicked, this, &DatabaseOptions::testConnectionClicked);

	connect(ui->btnRefreshTables, &QPushButton::clicked, this, &DatabaseOptions::refreshTablesClicked);
	connect(ui->btnVerifyTables, &QPushButton::clicked, this, &DatabaseOptions::verifyTablesClicked);

	connect(ui->btnCreateClients, &QPushButton::clicked, this, &DatabaseOptions::createClientsClicked);
	connect(ui->btnCreateResults, &QPushButton::clicked, this, &DatabaseOptions::createResultsClicked);

	connect(ui->btnDatabaseless, &QPushButton::clicked, this, &DatabaseOptions::databaselessClicked);
}

DatabaseOptions::~DatabaseOptions(){

	delete connection;
	delete ui;	
	
}

void DatabaseOptions::nextButtonClicked(){
	
	if(ui->wizardPanel->currentIndex() == 2){
		
		settings->setValue("DatabaseHostname", ui->txtHostname->text());
		settings->setValue("DatabaseName", ui->txtDatabase->text());
		settings->setValue("DatabasePort", ui->numPort->value());
		settings->setValue("DatabaseUsername", ui->txtUsername->text());
		settings->setValue("DatabasePassword", ui->txtPassword->text()); // You would never store passwords in plaintext but ¿?

		settings->setValue("DatabaseClientTable", ui->cmbClientTable->currentText());
		settings->setValue("DatabaseResultsTable", ui->cmbResultTable->currentText());
		settings->setValue("DatabaseConfigured", true);
		settings->setValue("Databaseless", false);
		QMetaObject::invokeMethod(parent,"refresh"); // Call refresh on the main window
		this->close();
	}

	ui->wizardPanel->setCurrentIndex(ui->wizardPanel->currentIndex() + 1);
}

void DatabaseOptions::backButtonClicked(){
	ui->wizardPanel->setCurrentIndex(ui->wizardPanel->currentIndex() - 1);
}

void DatabaseOptions::wizardPanelChanged(int newIndex){
	
	ui->btnNext->setText("Next");
	switch(newIndex)
	{
		case 0: // Prompt
			ui->btnBack->setEnabled(false);
			ui->btnNext->setEnabled(true);
			break;
		case 1: // Host
			ui->btnBack->setEnabled(true);
			ui->btnNext->setEnabled(false);
			break;
		case 2: // Table
			ui->btnBack->setEnabled(true);
			ui->btnNext->setEnabled(false);
			ui->btnNext->setText("Save");
			refreshTablesClicked(); // Show the tables in the combo boxes
			break;	
		
	}
}

void DatabaseOptions::showpassButtonClicked(bool checked){
	
	if (checked)
		ui->txtPassword->setEchoMode(QLineEdit::Normal);
	else
		ui->txtPassword->setEchoMode(QLineEdit::Password);
}

void DatabaseOptions::testConnectionClicked(){
	
	ui->lstTestConnection->setVisible(true);
	ui->lstTestConnection->clear();
	ui->statusbar->setStyleSheet("color: yellow");
	ui->statusbar->showMessage("Starting connection test");
	ui->lstTestConnection->addItem("Starting Connection test");

	if(ui->txtHostname->text().isEmpty() || ui->txtDatabase->text().isEmpty()
		|| ui->txtUsername->text().isEmpty())
	{
		ui->lstTestConnection->addItem("Please make sure you have your hostname, database name, and username fields filled in");
		return;
	}
	if(ui->txtPassword->text().isEmpty())
	{
		ui->lstTestConnection->addItem("No password for user authentication (Is this purposeful?)");
	}
	ui->lstTestConnection->addItem(QString("Host:%1:%2").arg(ui->txtHostname->text()).arg(ui->numPort->text()));
	connection = new SQLServer(ui->txtUsername->text().toStdString(), ui->txtPassword->text().toStdString(), 
		ui->txtHostname->text().toStdString(), ui->numPort->text().toStdString(),ui->txtDatabase->text().toStdString(),"dboptions");
	ui->lstTestConnection->addItem("Finished connection attempt");
	if (connection->Connected()) {
		ui->statusbar->setStyleSheet("color: green");
		ui->statusbar->showMessage("Connected to database!");
		ui->lstTestConnection->addItem("Connected to database!");
		ui->btnNext->setEnabled(true);
	}
	else
	{
		ui->statusbar->setStyleSheet("color: red");
		ui->statusbar->showMessage("Failed to connect to database, check status log for error!");
		ui->lstTestConnection->addItem("Failed to connect to database, last error:");
		ui->lstTestConnection->addItem(connection->DB.lastError().text());
	}
}

void DatabaseOptions::refreshTablesClicked(){
	
	ui->statusbar->setStyleSheet("color: yellow");
	ui->statusbar->showMessage("Refreshing database table view");
	ui->cmbClientTable->clear();
	ui->cmbResultTable->clear();
	QSqlQuery query(connection->DB);
	query.exec("SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_TYPE='BASE TABLE'");
	while(query.next())
	{
		ui->cmbClientTable->addItem(query.value(2).toString());
		QCoreApplication::processEvents(); // NON-Blocking UI, this function is not asynchronous 
		ui->cmbResultTable->addItem(query.value(2).toString());
	}
	ui->statusbar->setStyleSheet("color: green");
	ui->statusbar->showMessage("Finished fetching all tables");

}

void DatabaseOptions::verifyTablesClicked(){
	
	QString selectColumnsTemplate("SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = N'%1'");

	QString resultsTableQuery = selectColumnsTemplate.arg(ui->cmbResultTable->currentText());

	QSqlQuery clients(connection->DB);
	QSqlQuery results(connection->DB);
	clients.exec(selectColumnsTemplate.arg(ui->cmbClientTable->currentText()));
	results.exec(selectColumnsTemplate.arg(ui->cmbResultTable->currentText()));

	std::cout << clients.lastError().text().toStdString() << std::endl;
	std::cout << results.lastError().text().toStdString() << std::endl;
	/*
	 *
	 *	Verifies that the table columns are correct
	 *
	 */

	for(auto &column : clientColumns)
	{
		column.valid = false;
	}
	for(auto &column: resultColumns)
	{
		column.valid = false;
	}
	
	 // Iterates through the columns in the table
	
	for (int i = 0; clients.next(); i++){

		if (i == clientColumns.size()) // We scanned all of the columns required
			break;
		if (clients.value(3).toString().toLower() == clientColumns[i].columnName &&
			clients.value(7).toString().toLower() == clientColumns[i].columnType &&
			(clients.value(8).isNull() || clients.value(8).toInt() == -1 ||
			clients.value(8).toInt() ? clients.value(8) == clientColumns[i].maxColumnSize : true))
			clientColumns[i].valid = true;

	}
	
	QApplication::processEvents();
	for (int i = 0; results.next(); i++){
		
		if (i == resultColumns.size()) // We scanned all of the columns required
			break;
		if (results.value(3).toString().toLower() == resultColumns[i].columnName &&
			results.value(7).toString().toLower() == resultColumns[i].columnType &&
			(results.value(8).isNull() || clients.value(8).toInt() == -1 ||
			results.value(8).toInt() ? results.value(8) == resultColumns[i].maxColumnSize : true))
			resultColumns[i].valid = true;
	}
	
	QApplication::processEvents();

	
	for(auto &column : clientColumns){
		if (!column.valid) {
			QMessageBox msg(this);
			const QString errorTemplate = "Invalid client column. Column ID: %1, Column Type: %2,Maximum length (if varchar):%3 \nTable not supported";
			msg.setWindowTitle("Verifying table error");
			msg.setText(errorTemplate.arg(column.columnName).arg(column.columnType).arg(column.maxColumnSize));	
			msg.addButton(QMessageBox::Ok);
			msg.exec();
			return;
		}
	}
	for (auto& column : resultColumns) {
		if (!column.valid) {
			QMessageBox msg;
			const QString errorTemplate = "Invalid result column. Column ID: %1, Column Type: %2 \nTable not supported";
			msg.setWindowTitle("Verifying table error");
			msg.setText(errorTemplate.arg(column.columnName).arg(column.columnType));
			msg.addButton(QMessageBox::Ok);
			msg.exec();
			return;
		}
	}
	// If we made it here, the tables are compatible 
	ui->btnNext->setEnabled(true);
	ui->statusbar->setStyleSheet("color: green");
	ui->statusbar->showMessage("Tables successfully verified!");
}

void DatabaseOptions::createClientsClicked(){
	
	ui->statusbar->setStyleSheet("color: yellow");
	ui->statusbar->showMessage("Creating compatible client table named 'Clients'");
	QApplication::processEvents();
	QSqlQuery query(connection->DB);

	bool result = query.exec(QString("CREATE TABLE Clients(") +
		"ID int IDENTITY(0,1)," +
		"Username nvarchar(10)," +
		"HashedPassword nvarchar(128)," +
		"PasswordSalt nvarchar(50)," +
		"WorkCompleted int," +
		"ProcessorInfo nvarchar(MAX)," +
		"ProcessorCoreCount int," +
		"Platform nvarchar(MAX));");

	if (result) {
		ui->statusbar->setStyleSheet("color: green");
		ui->statusbar->showMessage("Table 'Clients' successfully created");
	}
	else
	{
		ui->statusbar->setStyleSheet("color: red");
		ui->statusbar->showMessage("Table 'Clients' unable to be created");
	}
	QApplication::processEvents();
	refreshTablesClicked(); // Update comboboxes 
}

void DatabaseOptions::createResultsClicked() {

	ui->statusbar->setStyleSheet("color: yellow");
	ui->statusbar->showMessage("Creating compatible result table named 'Results'");
	QApplication::processEvents();
	QSqlQuery query(connection->DB);

	bool result = query.exec(QString("CREATE TABLE Results(") +
		"ID bigint IDENTITY(0,1)," +
		"Prime bigint," +
		"ClientVerified int,"
		"ClientReverified int," +
		"DateFound datetime);");

	if (result) {
		ui->statusbar->setStyleSheet("color: green");
		ui->statusbar->showMessage("Table 'Results' successfully created");
	}
	else
	{
		ui->statusbar->setStyleSheet("color: red");
		ui->statusbar->showMessage("Table 'Results' unable to be created");
	}
	QApplication::processEvents();
	refreshTablesClicked(); // Update comboboxes 
}

void DatabaseOptions::databaselessClicked() {
	settings->setValue("Databaseless", true);
	QMetaObject::invokeMethod(parent, "refresh"); // Call refresh on the main window
	this->close();
}
