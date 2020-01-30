#include "CreateClient.h"
#include "ui_createclient.h"

CreateClient::CreateClient(QSqlDatabase localDB,QWidget* parent) : ui(new Ui::CreateClient) {
	ui->setupUi(this);
	localDB.open();
	this->classDBInstance = localDB;
	QSqlQuery selectQuery(localDB);
	selectQuery.prepare("SELECT TOP 1 ID FROM " + settings->value("DatabaseClientTable").toString() + " ORDER BY ID DESC");
	selectQuery.exec();
	selectQuery.next();
	ui->lblClientID->setText(QString::number(selectQuery.value("ID").toInt() + 1));

	connect(ui->btnCreateClient, &QPushButton::clicked, this, &CreateClient::btnCreateClient);
	connect(ui->btnExit, &QPushButton::clicked, this, &CreateClient::btnExit);
}

CreateClient::~CreateClient() {
	delete ui;
}

void CreateClient::btnExit() {
	this->close();
}

void CreateClient::btnCreateClient() {
	if (ui->txtClientUsername->text().isEmpty()) {
		QMessageBox(QMessageBox::Icon::Critical, "Abaci Create a Client", "Username cannot be blank", QMessageBox::Button::Ok, this).exec();
		return;
	}
	
	/* Check if user exists */
	bool userExists = false;
	QMetaObject::invokeMethod(this->parent(), "checkUserExists", Qt::BlockingQueuedConnection, Q_RETURN_ARG(bool, userExists), Q_ARG(QString, ui->txtClientUsername->text()));
	if (userExists) {
		QMessageBox(QMessageBox::Icon::Critical, "Abaci Create a Client", "Username already in use", QMessageBox::Button::Ok, this).exec();
		return;
	}

	if (ui->txtClientPassword->text().isEmpty()) {
		QMessageBox(QMessageBox::Icon::Critical, "Abaci Create a Client", "Password cannot be blank", QMessageBox::Button::Ok, this).exec();
		return;
	}

	QString hashedPassword = SQLServer::hashPass(ui->txtClientPassword->text(), QString::number(ui->lblClientID->text().toInt() ^ 2 / 2));

	/* Try to insert the user into the database*/
	QSqlQuery insertQuery(this->classDBInstance);

	insertQuery.prepare("INSERT INTO " + settings->value("DatabaseClientTable").toString() + " (Username,HashedPassword,PasswordSalt,WorkCompleted,ProcessorInfo,ProcessorCoreCount,Platform)" +
		" VALUES (:username,:hashedPassword,:passwordSalt,:workCompleted,:cpuInfo,:cpuCount,:platform)");
	insertQuery.bindValue(":username", ui->txtClientUsername->text());
	insertQuery.bindValue(":hashedPassword", hashedPassword);
	insertQuery.bindValue(":passwordSalt", QString::number(ui->lblClientID->text().toInt() ^ 2 / 2));
	insertQuery.bindValue(":workCompleted", 0);
	insertQuery.bindValue(":cpuInfo", ui->txtClientCPUInfo->text());
	insertQuery.bindValue(":cpuCount", ui->numClientCPUCount->value());
	insertQuery.bindValue(":platform", ui->txtClientPlatform->text());

	if (!insertQuery.exec()) {
		QMessageBox(QMessageBox::Icon::Critical, "Abaci Create a Client", "Unable to insert user.\nReason (if any): " + insertQuery.lastError().text(),QMessageBox::Button::Ok).exec();
	}
	else {
		QMessageBox(QMessageBox::Icon::Information, "Abaci Create a Client", "Created client '" + ui->txtClientUsername->text() + "'", QMessageBox::Button::Ok).exec();
		emit clientCreated();
	}
}
