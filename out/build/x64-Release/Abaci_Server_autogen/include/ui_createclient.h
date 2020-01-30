/********************************************************************************
** Form generated from reading UI file 'createclient.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATECLIENT_H
#define UI_CREATECLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CreateClient
{
public:
    QWidget *centralwidget;
    QFormLayout *formLayout;
    QLabel *lblClientIDprmpt;
    QLabel *lblClientUsernameprmpt;
    QLabel *lblClientCPUCountprmpt;
    QLabel *lblClientCPUInfo;
    QLabel *lblClientPlatformprmpt;
    QLabel *lblClientWorkCompletedprmpt;
    QLabel *lblClientPassword;
    QLineEdit *txtClientUsername;
    QLabel *lblClientID;
    QLineEdit *txtClientPassword;
    QLabel *lblClientWorkCompleted;
    QSpinBox *numClientCPUCount;
    QLineEdit *txtClientCPUInfo;
    QLineEdit *txtClientPlatform;
    QPushButton *btnExit;
    QPushButton *btnCreateClient;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *CreateClient)
    {
        if (CreateClient->objectName().isEmpty())
            CreateClient->setObjectName(QString::fromUtf8("CreateClient"));
        CreateClient->resize(372, 302);
        centralwidget = new QWidget(CreateClient);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        formLayout = new QFormLayout(centralwidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        lblClientIDprmpt = new QLabel(centralwidget);
        lblClientIDprmpt->setObjectName(QString::fromUtf8("lblClientIDprmpt"));

        formLayout->setWidget(0, QFormLayout::LabelRole, lblClientIDprmpt);

        lblClientUsernameprmpt = new QLabel(centralwidget);
        lblClientUsernameprmpt->setObjectName(QString::fromUtf8("lblClientUsernameprmpt"));

        formLayout->setWidget(1, QFormLayout::LabelRole, lblClientUsernameprmpt);

        lblClientCPUCountprmpt = new QLabel(centralwidget);
        lblClientCPUCountprmpt->setObjectName(QString::fromUtf8("lblClientCPUCountprmpt"));

        formLayout->setWidget(4, QFormLayout::LabelRole, lblClientCPUCountprmpt);

        lblClientCPUInfo = new QLabel(centralwidget);
        lblClientCPUInfo->setObjectName(QString::fromUtf8("lblClientCPUInfo"));

        formLayout->setWidget(5, QFormLayout::LabelRole, lblClientCPUInfo);

        lblClientPlatformprmpt = new QLabel(centralwidget);
        lblClientPlatformprmpt->setObjectName(QString::fromUtf8("lblClientPlatformprmpt"));

        formLayout->setWidget(6, QFormLayout::LabelRole, lblClientPlatformprmpt);

        lblClientWorkCompletedprmpt = new QLabel(centralwidget);
        lblClientWorkCompletedprmpt->setObjectName(QString::fromUtf8("lblClientWorkCompletedprmpt"));

        formLayout->setWidget(3, QFormLayout::LabelRole, lblClientWorkCompletedprmpt);

        lblClientPassword = new QLabel(centralwidget);
        lblClientPassword->setObjectName(QString::fromUtf8("lblClientPassword"));

        formLayout->setWidget(2, QFormLayout::LabelRole, lblClientPassword);

        txtClientUsername = new QLineEdit(centralwidget);
        txtClientUsername->setObjectName(QString::fromUtf8("txtClientUsername"));

        formLayout->setWidget(1, QFormLayout::FieldRole, txtClientUsername);

        lblClientID = new QLabel(centralwidget);
        lblClientID->setObjectName(QString::fromUtf8("lblClientID"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lblClientID);

        txtClientPassword = new QLineEdit(centralwidget);
        txtClientPassword->setObjectName(QString::fromUtf8("txtClientPassword"));

        formLayout->setWidget(2, QFormLayout::FieldRole, txtClientPassword);

        lblClientWorkCompleted = new QLabel(centralwidget);
        lblClientWorkCompleted->setObjectName(QString::fromUtf8("lblClientWorkCompleted"));

        formLayout->setWidget(3, QFormLayout::FieldRole, lblClientWorkCompleted);

        numClientCPUCount = new QSpinBox(centralwidget);
        numClientCPUCount->setObjectName(QString::fromUtf8("numClientCPUCount"));
        numClientCPUCount->setMinimum(1);
        numClientCPUCount->setMaximum(126);

        formLayout->setWidget(4, QFormLayout::FieldRole, numClientCPUCount);

        txtClientCPUInfo = new QLineEdit(centralwidget);
        txtClientCPUInfo->setObjectName(QString::fromUtf8("txtClientCPUInfo"));

        formLayout->setWidget(5, QFormLayout::FieldRole, txtClientCPUInfo);

        txtClientPlatform = new QLineEdit(centralwidget);
        txtClientPlatform->setObjectName(QString::fromUtf8("txtClientPlatform"));

        formLayout->setWidget(6, QFormLayout::FieldRole, txtClientPlatform);

        btnExit = new QPushButton(centralwidget);
        btnExit->setObjectName(QString::fromUtf8("btnExit"));

        formLayout->setWidget(7, QFormLayout::LabelRole, btnExit);

        btnCreateClient = new QPushButton(centralwidget);
        btnCreateClient->setObjectName(QString::fromUtf8("btnCreateClient"));

        formLayout->setWidget(7, QFormLayout::FieldRole, btnCreateClient);

        CreateClient->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CreateClient);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 372, 26));
        CreateClient->setMenuBar(menubar);
        statusbar = new QStatusBar(CreateClient);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        CreateClient->setStatusBar(statusbar);

        retranslateUi(CreateClient);

        QMetaObject::connectSlotsByName(CreateClient);
    } // setupUi

    void retranslateUi(QMainWindow *CreateClient)
    {
        CreateClient->setWindowTitle(QApplication::translate("CreateClient", "Create a Client", nullptr));
        lblClientIDprmpt->setText(QApplication::translate("CreateClient", "ClientID:", nullptr));
        lblClientUsernameprmpt->setText(QApplication::translate("CreateClient", "Username:", nullptr));
        lblClientCPUCountprmpt->setText(QApplication::translate("CreateClient", "CPUCount", nullptr));
        lblClientCPUInfo->setText(QApplication::translate("CreateClient", "CPUInfo", nullptr));
        lblClientPlatformprmpt->setText(QApplication::translate("CreateClient", "Platform", nullptr));
        lblClientWorkCompletedprmpt->setText(QApplication::translate("CreateClient", "WorkCompleted", nullptr));
        lblClientPassword->setText(QApplication::translate("CreateClient", "Password", nullptr));
        lblClientID->setText(QString());
        lblClientWorkCompleted->setText(QApplication::translate("CreateClient", "0", nullptr));
        btnExit->setText(QApplication::translate("CreateClient", "Exit", nullptr));
        btnCreateClient->setText(QApplication::translate("CreateClient", "Create Client Profile", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateClient: public Ui_CreateClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATECLIENT_H
