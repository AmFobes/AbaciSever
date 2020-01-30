#pragma once

#include <QApplication>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include "MainWindow.h"

namespace Ui {
	class CreateClient;
}

class CreateClient : public QMainWindow {
	Q_OBJECT
public:
	explicit CreateClient(QSqlDatabase localDB,QWidget* parent = nullptr);
	~CreateClient();
signals:
	void clientCreated();
private:
	Ui::CreateClient* ui;
	QSqlDatabase classDBInstance;
public slots:
	void btnCreateClient();
	void btnExit();
};
