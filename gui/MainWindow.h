#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>
#include <QSqlRecord>
#include <QtNetwork/QNetworkInterface>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableWidget>
#include <QTableView>
#include <QCloseEvent>
#include "sqlServer.h"

namespace Ui {
	class MainWindow;
};

extern QSettings* settings;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = 0);
	~MainWindow();

signals:
	void gdhReady(double prime);
	void onCloseEvent(QCloseEvent* event);
	void kickClientRequest(const QString &clientUsername);

protected:
	void closeEvent(QCloseEvent* event);
private:
	SQLServer *managerDB;
	Ui::MainWindow* ui;
	QSqlTableModel* resultTable = nullptr;
	QSqlTableModel* clientTable = nullptr;
	unsigned short refreshDelay = 1; // Use this global object instead of having to call main thread to get refresh delay
	double maxPrime;
	bool sqlConnected = false;
	void ConnectSQL();
	void ScanIps();
	
public slots:
	void refresh();
	void exit();
	void sqlStatusUpdate(bool success);
	void IpUpdate(QString ip_string_internal);
	void showDatabase();
	void showClientDetails();
	void showClientDetailsDB();
	void showCreateClient();
	void deleteClient();
	bool tryAuth(QString username, QString Password);
	int getClientID(QString username);
	bool resetPassword(QString username, QString newPassword);
	int getWorkCompleted(QString username);
	QString getProcessorInfo(QString username);
	int getProcessorCoreCount(QString username);
	QString getPlatform(QString username);

	bool setClientUsername(QString username, QString newUsername);
	bool setClientProcessorInfo(QString username, QString newProcessorInfo);
	bool setClientPlatform(QString username, QString newPlatform);
	bool checkUserExists(QString username);

	bool deleteClientOnClientRequest(QString username);
	
	void requestMaxPrime(double* prime);
	void addResult(std::vector<double> result, int clientID);

	void clientConnected(const QString& username);
	void clientDisconnected(const QString& username);

	void refreshLoop();
	void chkRefreshClicked(bool checked);
	void refreshNumChanged(int newValue);

	void btnKickClient();
};

#endif // MAINWINDOW_H
