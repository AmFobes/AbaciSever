#pragma once

#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QSqlQuery>
#include "MainWindow.h"

namespace Ui{
	class ClientData;
}

struct SingleClientData
{
	unsigned int ID;
	QString Username;
	QString HashedPassword;
	QString PasswordSalt;
	unsigned int WorkCompleted;
	QString ProcessorInfo;
	unsigned int ProcessorCoreCount;
	QString Platform;
	bool changed = false;
	SingleClientData(
		/* Client data constructor*/

		/* Arguments */
		const unsigned int ID,
		const QString username,
		const QString hashedPassword,
		const QString passwordSalt,
		const unsigned int workCompleted,
		const QString processorInfo,
		const unsigned int processorCoreCount,
		const QString platform)

		:
		/* Initializer list*/
		ID(ID),
		Username(username),
		HashedPassword(hashedPassword),
		PasswordSalt(passwordSalt),
		WorkCompleted(workCompleted),
		ProcessorCoreCount(processorCoreCount),
		Platform(platform){};

	SingleClientData(){}; // Provide empty constructor
};

class ClientData : public QMainWindow
{
	Q_OBJECT

public:
	explicit ClientData(SingleClientData *clientData,QSqlDatabase localDB,QWidget* parent = 0);
	~ClientData();

private:
	Ui::ClientData* ui;
	SingleClientData *clientData;
	QSqlDatabase localConnection;
private slots:
	void refreshClientInfo();
	void sqlSaveSettings();
	void btnUsernameEditClicked();
	void btnPasswordEditClicked();
	void btnCompletedWorkEditClicked();
	void btnCPUInfoEditClicked();
	void btnPlatformEditClicked();
	void rdoHidePasswordChanged(bool checked);
protected:
	 void closeEvent(QCloseEvent* event); // Called when window closes
};
