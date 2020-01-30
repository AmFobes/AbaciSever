/********************************************************************************
** Form generated from reading UI file 'clientdata.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTDATA_H
#define UI_CLIENTDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientData
{
public:
    QWidget *centralwidget;
    QLabel *label_2;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLabel *lblStaticUsername;
    QPushButton *btnEditCompletedWork;
    QLabel *lblStaticCompletedWork;
    QLabel *lblClientID;
    QLabel *lblUsername;
    QLabel *lblStaticCPUCount;
    QPushButton *btnEditHashedPass;
    QLabel *lblHashedPass;
    QLabel *lblStaticPlatform;
    QPushButton *btnEditCPUInfo;
    QLabel *lblCPUInfo;
    QLabel *lblPlatform;
    QLabel *lblCompletedWork;
    QPushButton *btnEditUsername;
    QLabel *lblStaticCPUInfo;
    QLabel *lblStaticHashedPass;
    QLineEdit *txtEditPassword;
    QLabel *lblCPUCount;
    QPushButton *btnEditPlatform;
    QLabel *lblStaticClientID;
    QRadioButton *rdoHidePassword;
    QLineEdit *txtEditUsername;
    QLineEdit *txtEditCompletedWork;
    QLineEdit *txtEditCPUInfo;
    QLineEdit *txtEditPlatform;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ClientData)
    {
        if (ClientData->objectName().isEmpty())
            ClientData->setObjectName(QString::fromUtf8("ClientData"));
        ClientData->resize(527, 285);
        centralwidget = new QWidget(ClientData);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(570, 240, 0, 16));
        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(0, 0, 521, 231));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        lblStaticUsername = new QLabel(gridLayoutWidget_2);
        lblStaticUsername->setObjectName(QString::fromUtf8("lblStaticUsername"));

        gridLayout_2->addWidget(lblStaticUsername, 1, 0, 1, 1);

        btnEditCompletedWork = new QPushButton(gridLayoutWidget_2);
        btnEditCompletedWork->setObjectName(QString::fromUtf8("btnEditCompletedWork"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnEditCompletedWork->sizePolicy().hasHeightForWidth());
        btnEditCompletedWork->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(btnEditCompletedWork, 3, 2, 1, 1);

        lblStaticCompletedWork = new QLabel(gridLayoutWidget_2);
        lblStaticCompletedWork->setObjectName(QString::fromUtf8("lblStaticCompletedWork"));

        gridLayout_2->addWidget(lblStaticCompletedWork, 3, 0, 1, 1);

        lblClientID = new QLabel(gridLayoutWidget_2);
        lblClientID->setObjectName(QString::fromUtf8("lblClientID"));

        gridLayout_2->addWidget(lblClientID, 0, 1, 1, 1);

        lblUsername = new QLabel(gridLayoutWidget_2);
        lblUsername->setObjectName(QString::fromUtf8("lblUsername"));

        gridLayout_2->addWidget(lblUsername, 1, 1, 1, 1);

        lblStaticCPUCount = new QLabel(gridLayoutWidget_2);
        lblStaticCPUCount->setObjectName(QString::fromUtf8("lblStaticCPUCount"));

        gridLayout_2->addWidget(lblStaticCPUCount, 5, 0, 1, 1);

        btnEditHashedPass = new QPushButton(gridLayoutWidget_2);
        btnEditHashedPass->setObjectName(QString::fromUtf8("btnEditHashedPass"));
        sizePolicy.setHeightForWidth(btnEditHashedPass->sizePolicy().hasHeightForWidth());
        btnEditHashedPass->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(btnEditHashedPass, 2, 2, 1, 1);

        lblHashedPass = new QLabel(gridLayoutWidget_2);
        lblHashedPass->setObjectName(QString::fromUtf8("lblHashedPass"));

        gridLayout_2->addWidget(lblHashedPass, 2, 1, 1, 1);

        lblStaticPlatform = new QLabel(gridLayoutWidget_2);
        lblStaticPlatform->setObjectName(QString::fromUtf8("lblStaticPlatform"));

        gridLayout_2->addWidget(lblStaticPlatform, 6, 0, 1, 1);

        btnEditCPUInfo = new QPushButton(gridLayoutWidget_2);
        btnEditCPUInfo->setObjectName(QString::fromUtf8("btnEditCPUInfo"));
        sizePolicy.setHeightForWidth(btnEditCPUInfo->sizePolicy().hasHeightForWidth());
        btnEditCPUInfo->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(btnEditCPUInfo, 4, 2, 1, 1);

        lblCPUInfo = new QLabel(gridLayoutWidget_2);
        lblCPUInfo->setObjectName(QString::fromUtf8("lblCPUInfo"));

        gridLayout_2->addWidget(lblCPUInfo, 4, 1, 1, 1);

        lblPlatform = new QLabel(gridLayoutWidget_2);
        lblPlatform->setObjectName(QString::fromUtf8("lblPlatform"));

        gridLayout_2->addWidget(lblPlatform, 6, 1, 1, 1);

        lblCompletedWork = new QLabel(gridLayoutWidget_2);
        lblCompletedWork->setObjectName(QString::fromUtf8("lblCompletedWork"));

        gridLayout_2->addWidget(lblCompletedWork, 3, 1, 1, 1);

        btnEditUsername = new QPushButton(gridLayoutWidget_2);
        btnEditUsername->setObjectName(QString::fromUtf8("btnEditUsername"));
        sizePolicy.setHeightForWidth(btnEditUsername->sizePolicy().hasHeightForWidth());
        btnEditUsername->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(btnEditUsername, 1, 2, 1, 1);

        lblStaticCPUInfo = new QLabel(gridLayoutWidget_2);
        lblStaticCPUInfo->setObjectName(QString::fromUtf8("lblStaticCPUInfo"));

        gridLayout_2->addWidget(lblStaticCPUInfo, 4, 0, 1, 1);

        lblStaticHashedPass = new QLabel(gridLayoutWidget_2);
        lblStaticHashedPass->setObjectName(QString::fromUtf8("lblStaticHashedPass"));

        gridLayout_2->addWidget(lblStaticHashedPass, 2, 0, 1, 1);

        txtEditPassword = new QLineEdit(gridLayoutWidget_2);
        txtEditPassword->setObjectName(QString::fromUtf8("txtEditPassword"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(txtEditPassword->sizePolicy().hasHeightForWidth());
        txtEditPassword->setSizePolicy(sizePolicy1);
        txtEditPassword->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(txtEditPassword, 2, 3, 1, 1);

        lblCPUCount = new QLabel(gridLayoutWidget_2);
        lblCPUCount->setObjectName(QString::fromUtf8("lblCPUCount"));

        gridLayout_2->addWidget(lblCPUCount, 5, 1, 1, 1);

        btnEditPlatform = new QPushButton(gridLayoutWidget_2);
        btnEditPlatform->setObjectName(QString::fromUtf8("btnEditPlatform"));
        sizePolicy.setHeightForWidth(btnEditPlatform->sizePolicy().hasHeightForWidth());
        btnEditPlatform->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(btnEditPlatform, 6, 2, 1, 1);

        lblStaticClientID = new QLabel(gridLayoutWidget_2);
        lblStaticClientID->setObjectName(QString::fromUtf8("lblStaticClientID"));

        gridLayout_2->addWidget(lblStaticClientID, 0, 0, 1, 1);

        rdoHidePassword = new QRadioButton(gridLayoutWidget_2);
        rdoHidePassword->setObjectName(QString::fromUtf8("rdoHidePassword"));
        rdoHidePassword->setChecked(true);

        gridLayout_2->addWidget(rdoHidePassword, 2, 4, 1, 1);

        txtEditUsername = new QLineEdit(gridLayoutWidget_2);
        txtEditUsername->setObjectName(QString::fromUtf8("txtEditUsername"));
        sizePolicy1.setHeightForWidth(txtEditUsername->sizePolicy().hasHeightForWidth());
        txtEditUsername->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(txtEditUsername, 1, 3, 1, 2);

        txtEditCompletedWork = new QLineEdit(gridLayoutWidget_2);
        txtEditCompletedWork->setObjectName(QString::fromUtf8("txtEditCompletedWork"));
        sizePolicy1.setHeightForWidth(txtEditCompletedWork->sizePolicy().hasHeightForWidth());
        txtEditCompletedWork->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(txtEditCompletedWork, 3, 3, 1, 2);

        txtEditCPUInfo = new QLineEdit(gridLayoutWidget_2);
        txtEditCPUInfo->setObjectName(QString::fromUtf8("txtEditCPUInfo"));
        sizePolicy1.setHeightForWidth(txtEditCPUInfo->sizePolicy().hasHeightForWidth());
        txtEditCPUInfo->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(txtEditCPUInfo, 4, 3, 1, 2);

        txtEditPlatform = new QLineEdit(gridLayoutWidget_2);
        txtEditPlatform->setObjectName(QString::fromUtf8("txtEditPlatform"));
        sizePolicy1.setHeightForWidth(txtEditPlatform->sizePolicy().hasHeightForWidth());
        txtEditPlatform->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(txtEditPlatform, 6, 3, 1, 2);

        ClientData->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ClientData);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 527, 26));
        ClientData->setMenuBar(menubar);
        statusbar = new QStatusBar(ClientData);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ClientData->setStatusBar(statusbar);

        retranslateUi(ClientData);

        QMetaObject::connectSlotsByName(ClientData);
    } // setupUi

    void retranslateUi(QMainWindow *ClientData)
    {
        ClientData->setWindowTitle(QApplication::translate("ClientData", "Information for client", nullptr));
        label_2->setText(QString());
        lblStaticUsername->setText(QApplication::translate("ClientData", "Username", nullptr));
        btnEditCompletedWork->setText(QApplication::translate("ClientData", "Edit", nullptr));
        lblStaticCompletedWork->setText(QApplication::translate("ClientData", "Completed Work", nullptr));
        lblClientID->setText(QString());
        lblUsername->setText(QString());
        lblStaticCPUCount->setText(QApplication::translate("ClientData", "CPU Count", nullptr));
        btnEditHashedPass->setText(QApplication::translate("ClientData", "Edit", nullptr));
        lblHashedPass->setText(QString());
        lblStaticPlatform->setText(QApplication::translate("ClientData", "Platform", nullptr));
        btnEditCPUInfo->setText(QApplication::translate("ClientData", "Edit", nullptr));
        lblCPUInfo->setText(QString());
        lblPlatform->setText(QString());
        lblCompletedWork->setText(QString());
        btnEditUsername->setText(QApplication::translate("ClientData", "Edit", nullptr));
        lblStaticCPUInfo->setText(QApplication::translate("ClientData", "CPU Info", nullptr));
        lblStaticHashedPass->setText(QApplication::translate("ClientData", "Hashed Password", nullptr));
        txtEditPassword->setPlaceholderText(QApplication::translate("ClientData", "Plaintext password", nullptr));
        lblCPUCount->setText(QString());
        btnEditPlatform->setText(QApplication::translate("ClientData", "Edit", nullptr));
        lblStaticClientID->setText(QApplication::translate("ClientData", "Client ID", nullptr));
        rdoHidePassword->setText(QApplication::translate("ClientData", "Hide", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientData: public Ui_ClientData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTDATA_H
