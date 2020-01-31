#include "ClientData.h"
#include "ui_clientdata.h"
#include "SqlServer.h"

ClientData::ClientData(SingleClientData* clientDataarg,QSqlDatabase localDB,QWidget* parent) :
	ui(new Ui::ClientData){
	
	ui->setupUi(this);
	
	this->clientData = clientDataarg;
	this->localConnection = localDB;
	this->localConnection.open();

	/*
	 *
	 *	Show client information
	 * 
	 */
	refreshClientInfo();
	
	
	/*
	 *
	 *	Create button handlers
	 * 
	 */
	if (!settings->value("Databaseless").toBool()) { // If we are running with a database
		connect(ui->btnEditCompletedWork, &QPushButton::clicked, this, &ClientData::btnCompletedWorkEditClicked);
		connect(ui->txtEditCompletedWork, &QLineEdit::returnPressed, this, &ClientData::btnCompletedWorkEditClicked);
		connect(ui->btnEditUsername, &QPushButton::clicked, this, &ClientData::btnUsernameEditClicked);
		connect(ui->txtEditUsername, &QLineEdit::returnPressed, this, &ClientData::btnUsernameEditClicked);
		connect(ui->btnEditHashedPass, &QPushButton::clicked, this, &ClientData::btnPasswordEditClicked);
		connect(ui->txtEditPassword, &QLineEdit::returnPressed, this, &ClientData::btnPasswordEditClicked);
		connect(ui->btnEditCPUInfo, &QPushButton::clicked, this, &ClientData::btnCPUInfoEditClicked);
		connect(ui->txtEditCPUInfo, &QLineEdit::returnPressed, this, &ClientData::btnCPUInfoEditClicked);
		connect(ui->btnEditPlatform, &QPushButton::clicked, this, &ClientData::btnPlatformEditClicked);
		connect(ui->txtEditPlatform, &QLineEdit::returnPressed, this, &ClientData::btnPlatformEditClicked);

		connect(this, &QMainWindow::close, this, &ClientData::sqlSaveSettings); // Save the settings on window close
	}
	else
	{
		ui->btnEditCompletedWork->setEnabled(false);
		ui->txtEditCompletedWork->setEnabled(false);
		ui->btnEditUsername->setEnabled(false);
		ui->txtEditUsername->setEnabled(false);
		ui->btnEditHashedPass->setEnabled(false);
		ui->txtEditPassword->setEnabled(false);
		ui->btnEditCPUInfo->setEnabled(false);
		ui->txtEditCPUInfo->setEnabled(false);
		ui->btnEditPlatform->setEnabled(false);
		ui->txtEditPlatform->setEnabled(false);
	}
	connect(ui->rdoHidePassword, &QRadioButton::clicked, this, &ClientData::rdoHidePasswordChanged);
}
ClientData::~ClientData(){
	delete ui;
}

void ClientData::refreshClientInfo(){
	
	this->setWindowTitle("Information for client " + clientData->Username);
	ui->lblClientID->setText(QString::number(clientData->ID));
	ui->lblUsername->setText(clientData->Username);
	ui->lblHashedPass->setText(clientData->HashedPassword);
	ui->lblCompletedWork->setText(QString::number(clientData->WorkCompleted));
	ui->lblCPUInfo->setText(clientData->ProcessorInfo);
	ui->lblCPUCount->setText(QString::number(clientData->ProcessorCoreCount));
	ui->lblPlatform->setText(clientData->Platform);
}

void ClientData::btnUsernameEditClicked(){
		
	QSqlQuery query(this->localConnection);
	
	
	query.prepare("SELECT * FROM " + settings->value("DatabaseClientTable").toString() + " WHERE Username = :username"); // Can't bind value to table name
	// Unsure why that is
	query.bindValue(":username", ui->txtEditUsername->text());
	
	query.exec();
	
	if(query.next())
	{
		QMessageBox("Unique username check failed",
			"Please use a unique username!",
			QMessageBox::Critical, QMessageBox::Ok,
			0, 0).exec();
		return;
	}

	clientData->Username = ui->txtEditUsername->text();
	clientData->changed = true;
	
	sqlSaveSettings();
}

void ClientData::btnPasswordEditClicked(){
	
	QString newPassword = ui->txtEditPassword->text().trimmed();
	
	if(newPassword.isEmpty() || newPassword.isNull())
	{
		QMessageBox("Password check failed",
			"The password field cannot be empty!",
			QMessageBox::Icon::Critical, QMessageBox::Button::Ok,
			0, 0).exec();
		return;
	}
	QString	hashedPassword = SQLServer::hashPass(newPassword, QString::number(this->clientData->ID ^ 2 / 2));

	this->clientData->HashedPassword = hashedPassword;
	this->clientData->changed = true;
	sqlSaveSettings();
}

void ClientData::btnCompletedWorkEditClicked(){
	
	QString newNumWork = ui->txtEditCompletedWork->text();
	bool ok;
	unsigned int newNumWorkInt = newNumWork.toUInt(&ok);
	if(!ok)
	{
		QMessageBox("Number parsing error", 
			"The number you have entered is not valid", 
			QMessageBox::Icon::Critical, QMessageBox::Button::Ok, 
			0, 0).exec();
		
		return;
	}

	this->clientData->WorkCompleted = newNumWorkInt;
	this->clientData->changed = true;
	sqlSaveSettings();
}

void ClientData::btnCPUInfoEditClicked(){

	QString newCPUInfo = ui->txtEditCPUInfo->text();
	/* an empty string is okay */
	this->clientData->ProcessorInfo = newCPUInfo;
	this->clientData->changed = true;
	sqlSaveSettings();
}

void ClientData::btnPlatformEditClicked(){
	
	QString newPlatform = ui->txtEditPlatform->text();
	/* an empty string is okay */
	this->clientData->Platform = newPlatform;
	this->clientData->changed = true;
	sqlSaveSettings();
	
}

void ClientData::rdoHidePasswordChanged(bool checked){
	
	if(checked)	{
		ui->txtEditPassword->setEchoMode(QLineEdit::Password);
	}
	else{
		ui->txtEditPassword->setEchoMode(QLineEdit::Normal);
	}
}

void ClientData::sqlSaveSettings(){
	
	if (!this->clientData->changed) // If the data isn't changed
		return;

	QSqlQuery query(this->localConnection);
	query.prepare("UPDATE " + settings->value("DatabaseClientTable").toString() +" SET Username=:username,HashedPassword=:hashedpassword,PasswordSalt=:passwordsalt,WorkCompleted=:workcompleted,ProcessorInfo=:processorinfo,Platform=:platform WHERE ID = :id");
	query.bindValue(":username", this->clientData->Username);
	query.bindValue(":hashedpassword", this->clientData->HashedPassword);
	query.bindValue(":passwordsalt", QString::number(this->clientData->ID ^ 2 / 2));
	query.bindValue(":workcompleted", this->clientData->WorkCompleted);
	query.bindValue(":processorinfo", this->clientData->ProcessorInfo);
	query.bindValue(":platform", this->clientData->Platform);
	query.bindValue(":id", this->clientData->ID);
	query.exec();
	if(query.lastError().isValid())
	{
		QMessageBox("Client Data sql connection error",
			"Erorr when saving client settings: " + query.lastError().text(),
			QMessageBox::Critical, QMessageBox::Ok, 0, 0).exec();
		
		return;
	}
	
	this->clientData->changed = false;
	refreshClientInfo();
}


void ClientData::closeEvent(QCloseEvent* event){

	sqlSaveSettings();

	this->localConnection.close();
	this->localConnection.removeDatabase("ClientDataDB");
	this->hide();
	//delete this; // A sad case of suicide :C
}
