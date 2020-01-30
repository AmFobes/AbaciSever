#pragma once
#include <vector>
#include <QMainWindow>
#include "sqlServer.h"
#include "MainWindow.h"

namespace Ui
{
	class DatabaseOptions;
}

class DatabaseOptions : public QMainWindow
{
	Q_OBJECT

public:
	explicit DatabaseOptions(QWidget* parent = 0);
	~DatabaseOptions();
private:
	QWidget* parent;
	Ui::DatabaseOptions* ui;
	SQLServer *connection;
	struct ColumnRequirements
	{
		QString columnName;
		QString columnType;
		unsigned int maxColumnSize;
		bool valid = false; // True when column is valid type
		ColumnRequirements(QString name, QString type, unsigned int size) : columnName(name.toLower()), columnType(type.toLower()), maxColumnSize(size) {};
	};
	std::vector<ColumnRequirements> clientColumns{
		ColumnRequirements("id","int",0),
		ColumnRequirements("username","nvarchar",10),
		ColumnRequirements("hashedpassword","nvarchar",128),
		ColumnRequirements("passwordsalt","nvarchar",50),
		ColumnRequirements("workcompleted","int",0),
		ColumnRequirements("processorinfo","nvarchar",-1),
		ColumnRequirements("processorcorecount","int",0),
		ColumnRequirements("platform","nvarchar",-1),
	};
	
	std::vector<ColumnRequirements> resultColumns{
		ColumnRequirements("id","bigint",0),
		ColumnRequirements("Prime","bigint",0),
		ColumnRequirements("clientverified","int",0),
		ColumnRequirements("clientreverified","int",0),
		ColumnRequirements("datefound","datetime",0),
	};
public slots:

	void nextButtonClicked();
	void backButtonClicked();
	void wizardPanelChanged(int newIndex);
	void showpassButtonClicked(bool checked);
	void testConnectionClicked();
	void refreshTablesClicked();
	void verifyTablesClicked();
	void createClientsClicked();
	void createResultsClicked();
	void databaselessClicked();
};
