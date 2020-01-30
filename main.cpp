#include <qapplication.h>
#include <iostream>
#include "sqlServer.h"
#include "Server.h"
#include "gui/MainWindow.h"
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlRecord>

int main(int argc, char* argv[]) {
	
	qRegisterMetaType<QAbstractSocket::SocketState>("QAbstractSocket::SocketState");
 	QApplication a(argc, argv);
	QThread thread;
	
	MainWindow mainWindow;
	ThreadedAbaciServer* server = new ThreadedAbaciServer(&mainWindow);
	mainWindow.connect(&mainWindow, &MainWindow::gdhReady, server, &ThreadedAbaciServer::setGDH);
	mainWindow.connect(&mainWindow, &MainWindow::onCloseEvent,server,&ThreadedAbaciServer::shutdown);
	mainWindow.connect(&mainWindow, &MainWindow::kickClientRequest, server, &ThreadedAbaciServer::kickClientRequest);
	mainWindow.show();

	server->moveToThread(&thread);
	thread.start();

	
	return a.exec();
}
