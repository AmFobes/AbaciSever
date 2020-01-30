/********************************************************************************
** Form generated from reading UI file 'databaseoptions.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATABASEOPTIONS_H
#define UI_DATABASEOPTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DatabaseOptions
{
public:
    QWidget *centralwidget;
    QPushButton *btnBack;
    QStackedWidget *wizardPanel;
    QWidget *page_4;
    QLabel *lblInitialPrompt;
    QLabel *lblInitialPrompt_2;
    QLabel *label_8;
    QWidget *page_5;
    QLineEdit *txtHostname;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLineEdit *txtUsername;
    QLabel *label_12;
    QLineEdit *txtPassword;
    QCheckBox *chkShowPassword;
    QSpinBox *numPort;
    QPushButton *btnTestConnection;
    QListWidget *lstTestConnection;
    QLabel *label_13;
    QLineEdit *txtDatabase;
    QWidget *page_6;
    QLabel *label_14;
    QComboBox *cmbClientTable;
    QLabel *lblClientTable;
    QLabel *lblJobTable;
    QComboBox *cmbResultTable;
    QPushButton *btnRefreshTables;
    QPushButton *btnVerifyTables;
    QPushButton *btnCreateClients;
    QPushButton *btnCreateResults;
    QPushButton *btnCancel;
    QPushButton *btnNext;
    QPushButton *btnDatabaseless;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DatabaseOptions)
    {
        if (DatabaseOptions->objectName().isEmpty())
            DatabaseOptions->setObjectName(QString::fromUtf8("DatabaseOptions"));
        DatabaseOptions->resize(491, 434);
        centralwidget = new QWidget(DatabaseOptions);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        btnBack = new QPushButton(centralwidget);
        btnBack->setObjectName(QString::fromUtf8("btnBack"));
        btnBack->setEnabled(false);
        btnBack->setGeometry(QRect(270, 340, 93, 28));
        wizardPanel = new QStackedWidget(centralwidget);
        wizardPanel->setObjectName(QString::fromUtf8("wizardPanel"));
        wizardPanel->setEnabled(true);
        wizardPanel->setGeometry(QRect(0, 0, 471, 331));
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        lblInitialPrompt = new QLabel(page_4);
        lblInitialPrompt->setObjectName(QString::fromUtf8("lblInitialPrompt"));
        lblInitialPrompt->setGeometry(QRect(50, 0, 381, 111));
        QFont font;
        font.setPointSize(14);
        lblInitialPrompt->setFont(font);
        lblInitialPrompt_2 = new QLabel(page_4);
        lblInitialPrompt_2->setObjectName(QString::fromUtf8("lblInitialPrompt_2"));
        lblInitialPrompt_2->setGeometry(QRect(100, 30, 381, 111));
        lblInitialPrompt_2->setFont(font);
        label_8 = new QLabel(page_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(150, 130, 201, 191));
        label_8->setPixmap(QPixmap(QString::fromUtf8(":/DB/resources/DB.png")));
        label_8->setScaledContents(true);
        wizardPanel->addWidget(page_4);
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        txtHostname = new QLineEdit(page_5);
        txtHostname->setObjectName(QString::fromUtf8("txtHostname"));
        txtHostname->setGeometry(QRect(120, 80, 251, 22));
        label_9 = new QLabel(page_5);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 80, 91, 20));
        label_10 = new QLabel(page_5);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(20, 20, 351, 41));
        QFont font1;
        font1.setPointSize(16);
        label_10->setFont(font1);
        label_11 = new QLabel(page_5);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(40, 140, 61, 21));
        txtUsername = new QLineEdit(page_5);
        txtUsername->setObjectName(QString::fromUtf8("txtUsername"));
        txtUsername->setGeometry(QRect(120, 140, 151, 22));
        label_12 = new QLabel(page_5);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(40, 170, 61, 21));
        txtPassword = new QLineEdit(page_5);
        txtPassword->setObjectName(QString::fromUtf8("txtPassword"));
        txtPassword->setGeometry(QRect(120, 170, 151, 22));
        txtPassword->setEchoMode(QLineEdit::Password);
        chkShowPassword = new QCheckBox(page_5);
        chkShowPassword->setObjectName(QString::fromUtf8("chkShowPassword"));
        chkShowPassword->setGeometry(QRect(280, 170, 81, 20));
        numPort = new QSpinBox(page_5);
        numPort->setObjectName(QString::fromUtf8("numPort"));
        numPort->setGeometry(QRect(380, 80, 71, 22));
        numPort->setMinimum(1);
        numPort->setMaximum(65535);
        numPort->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);
        numPort->setValue(1433);
        btnTestConnection = new QPushButton(page_5);
        btnTestConnection->setObjectName(QString::fromUtf8("btnTestConnection"));
        btnTestConnection->setGeometry(QRect(120, 200, 151, 28));
        lstTestConnection = new QListWidget(page_5);
        lstTestConnection->setObjectName(QString::fromUtf8("lstTestConnection"));
        lstTestConnection->setGeometry(QRect(30, 230, 441, 101));
        label_13 = new QLabel(page_5);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(40, 110, 61, 21));
        txtDatabase = new QLineEdit(page_5);
        txtDatabase->setObjectName(QString::fromUtf8("txtDatabase"));
        txtDatabase->setGeometry(QRect(120, 110, 151, 22));
        wizardPanel->addWidget(page_5);
        page_6 = new QWidget();
        page_6->setObjectName(QString::fromUtf8("page_6"));
        label_14 = new QLabel(page_6);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(20, 20, 81, 41));
        label_14->setFont(font1);
        cmbClientTable = new QComboBox(page_6);
        cmbClientTable->setObjectName(QString::fromUtf8("cmbClientTable"));
        cmbClientTable->setGeometry(QRect(160, 70, 191, 22));
        lblClientTable = new QLabel(page_6);
        lblClientTable->setObjectName(QString::fromUtf8("lblClientTable"));
        lblClientTable->setGeometry(QRect(80, 70, 81, 21));
        lblJobTable = new QLabel(page_6);
        lblJobTable->setObjectName(QString::fromUtf8("lblJobTable"));
        lblJobTable->setGeometry(QRect(80, 100, 81, 21));
        cmbResultTable = new QComboBox(page_6);
        cmbResultTable->setObjectName(QString::fromUtf8("cmbResultTable"));
        cmbResultTable->setGeometry(QRect(160, 100, 191, 22));
        btnRefreshTables = new QPushButton(page_6);
        btnRefreshTables->setObjectName(QString::fromUtf8("btnRefreshTables"));
        btnRefreshTables->setGeometry(QRect(160, 130, 93, 28));
        btnVerifyTables = new QPushButton(page_6);
        btnVerifyTables->setObjectName(QString::fromUtf8("btnVerifyTables"));
        btnVerifyTables->setGeometry(QRect(260, 130, 93, 28));
        btnCreateClients = new QPushButton(page_6);
        btnCreateClients->setObjectName(QString::fromUtf8("btnCreateClients"));
        btnCreateClients->setGeometry(QRect(160, 170, 93, 28));
        btnCreateResults = new QPushButton(page_6);
        btnCreateResults->setObjectName(QString::fromUtf8("btnCreateResults"));
        btnCreateResults->setGeometry(QRect(260, 170, 93, 28));
        wizardPanel->addWidget(page_6);
        btnCancel = new QPushButton(centralwidget);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(160, 340, 93, 28));
        btnNext = new QPushButton(centralwidget);
        btnNext->setObjectName(QString::fromUtf8("btnNext"));
        btnNext->setGeometry(QRect(380, 340, 93, 28));
        btnDatabaseless = new QPushButton(centralwidget);
        btnDatabaseless->setObjectName(QString::fromUtf8("btnDatabaseless"));
        btnDatabaseless->setEnabled(false);
        btnDatabaseless->setGeometry(QRect(50, 340, 93, 28));
        DatabaseOptions->setCentralWidget(centralwidget);
        menubar = new QMenuBar(DatabaseOptions);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 491, 26));
        DatabaseOptions->setMenuBar(menubar);
        statusbar = new QStatusBar(DatabaseOptions);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        DatabaseOptions->setStatusBar(statusbar);
        QWidget::setTabOrder(txtHostname, numPort);
        QWidget::setTabOrder(numPort, txtDatabase);
        QWidget::setTabOrder(txtDatabase, txtUsername);
        QWidget::setTabOrder(txtUsername, txtPassword);
        QWidget::setTabOrder(txtPassword, btnTestConnection);
        QWidget::setTabOrder(btnTestConnection, btnNext);
        QWidget::setTabOrder(btnNext, btnBack);
        QWidget::setTabOrder(btnBack, btnCancel);
        QWidget::setTabOrder(btnCancel, chkShowPassword);
        QWidget::setTabOrder(chkShowPassword, lstTestConnection);
        QWidget::setTabOrder(lstTestConnection, cmbClientTable);
        QWidget::setTabOrder(cmbClientTable, cmbResultTable);
        QWidget::setTabOrder(cmbResultTable, btnRefreshTables);
        QWidget::setTabOrder(btnRefreshTables, btnVerifyTables);
        QWidget::setTabOrder(btnVerifyTables, btnCreateClients);
        QWidget::setTabOrder(btnCreateClients, btnCreateResults);

        retranslateUi(DatabaseOptions);

        wizardPanel->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DatabaseOptions);
    } // setupUi

    void retranslateUi(QMainWindow *DatabaseOptions)
    {
        DatabaseOptions->setWindowTitle(QApplication::translate("DatabaseOptions", "Database Options", nullptr));
        btnBack->setText(QApplication::translate("DatabaseOptions", "Back", nullptr));
        lblInitialPrompt->setText(QApplication::translate("DatabaseOptions", "This wizard allows you to connect to ", nullptr));
        lblInitialPrompt_2->setText(QApplication::translate("DatabaseOptions", "the Abaci Database Server.", nullptr));
        label_8->setText(QString());
        label_9->setText(QApplication::translate("DatabaseOptions", "Hostname / IP", nullptr));
        label_10->setText(QApplication::translate("DatabaseOptions", "Connection ", nullptr));
        label_11->setText(QApplication::translate("DatabaseOptions", "Username", nullptr));
        label_12->setText(QApplication::translate("DatabaseOptions", "Password", nullptr));
        chkShowPassword->setText(QApplication::translate("DatabaseOptions", "Show", nullptr));
        btnTestConnection->setText(QApplication::translate("DatabaseOptions", "Test Connection", nullptr));
        label_13->setText(QApplication::translate("DatabaseOptions", "Database", nullptr));
        label_14->setText(QApplication::translate("DatabaseOptions", "Table", nullptr));
        lblClientTable->setText(QApplication::translate("DatabaseOptions", "Client Table", nullptr));
        lblJobTable->setText(QApplication::translate("DatabaseOptions", "Results Table", nullptr));
        btnRefreshTables->setText(QApplication::translate("DatabaseOptions", "Refresh Tables", nullptr));
        btnVerifyTables->setText(QApplication::translate("DatabaseOptions", "Verify Tables", nullptr));
        btnCreateClients->setText(QApplication::translate("DatabaseOptions", "Create Clients", nullptr));
        btnCreateResults->setText(QApplication::translate("DatabaseOptions", "Create Results", nullptr));
        btnCancel->setText(QApplication::translate("DatabaseOptions", "Cancel", nullptr));
        btnNext->setText(QApplication::translate("DatabaseOptions", "Next", nullptr));
        btnDatabaseless->setText(QApplication::translate("DatabaseOptions", "Databaseless", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DatabaseOptions: public Ui_DatabaseOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATABASEOPTIONS_H
