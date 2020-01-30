#pragma once

#include <QSqlDatabase>
#include <QCryptographicHash>
#include <QSql>
#include <QSqlError>
#include <iostream>

class SQLServer {
	std::string HostName, DatabaseName, Username = "Manager", Password = "SecurePassword123";

public:
	QSqlDatabase DB;
	bool validConnection = false;
	SQLServer(const std::string Username,const std::string Password,const std::string HostName = "localhost",const std::string Port = "1433", const std::string DatabaseName = "AbaciDB",const QString conName = nullptr) noexcept : Username(Username),Password(Password),HostName(HostName), DatabaseName(DatabaseName) {

		QSqlDatabase db;
		if (conName == nullptr)
			db = QSqlDatabase::addDatabase("QODBC");
		else
			db = QSqlDatabase::addDatabase("QODBC", conName);

		bool driverAvailable = QSqlDatabase::isDriverAvailable("QODBC");
	
		const QString connectionTemplate = QString("DRIVER={SQL Server};Server=%1;Database=%2;Uid=%3;Port=%4;Pwd=%5;");
		auto connectionString = connectionTemplate.arg(HostName.c_str()).arg(DatabaseName.c_str()).arg(Username.c_str()).arg(Port.c_str()).arg(Password.c_str());
		
		db.setDatabaseName(connectionString);
		db.open();
		this->DB = db;
		validConnection = true;
	}

	~SQLServer() {
		DB.close();
	}
	bool Connected() { return validConnection && DB.isOpen(); };

	static QString hashPass(QString plainPassword,QString salt)
	{
		plainPassword.push_front(salt);	// Add salt to front and back of password `password` -> `10password10`
		plainPassword.push_back(salt);	
		QCryptographicHash hasher(QCryptographicHash::Keccak_512);
		QByteArray rawHash = QCryptographicHash::hash(QByteArray::fromStdString(plainPassword.toStdString()), QCryptographicHash::Keccak_512);
		QString hashedPassword = QString(QLatin1String(rawHash.toHex()));
		return hashedPassword;
	}
};
