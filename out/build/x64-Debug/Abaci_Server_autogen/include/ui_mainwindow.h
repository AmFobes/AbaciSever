/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *actionMinimize;
    QAction *actionExit_2;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout_5;
    QLabel *lblInternalIps;
    QLabel *label_8;
    QGridLayout *gridLayout_3;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *btnKickClient;
    QPushButton *btnDeleteClient;
    QFrame *line_2;
    QTableWidget *tableSessionClients;
    QLabel *label;
    QPushButton *btnCreateAClient;
    QTableView *tableClients;
    QPushButton *btnClientDetailsDB;
    QPushButton *btnClientDetails;
    QGridLayout *gridLayout;
    QSpinBox *numRefreshSeconds;
    QPushButton *btnConfigureDatabase;
    QPushButton *btnReload;
    QFrame *line;
    QLabel *label_2;
    QCheckBox *chkRefresh;
    QTableView *tableResults;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(943, 834);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionMinimize = new QAction(MainWindow);
        actionMinimize->setObjectName(QString::fromUtf8("actionMinimize"));
        actionExit_2 = new QAction(MainWindow);
        actionExit_2->setObjectName(QString::fromUtf8("actionExit_2"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        lblInternalIps = new QLabel(centralwidget);
        lblInternalIps->setObjectName(QString::fromUtf8("lblInternalIps"));

        gridLayout_5->addWidget(lblInternalIps, 0, 1, 1, 1);

        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(label_8, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout_5, 2, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_5, 0, 0, 1, 2);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 1, 0, 1, 1);

        btnKickClient = new QPushButton(centralwidget);
        btnKickClient->setObjectName(QString::fromUtf8("btnKickClient"));

        gridLayout_3->addWidget(btnKickClient, 5, 0, 1, 1);

        btnDeleteClient = new QPushButton(centralwidget);
        btnDeleteClient->setObjectName(QString::fromUtf8("btnDeleteClient"));

        gridLayout_3->addWidget(btnDeleteClient, 12, 0, 1, 1);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_2, 7, 0, 1, 2);

        tableSessionClients = new QTableWidget(centralwidget);
        if (tableSessionClients->columnCount() < 1)
            tableSessionClients->setColumnCount(1);
        tableSessionClients->setObjectName(QString::fromUtf8("tableSessionClients"));
        tableSessionClients->setColumnCount(1);
        tableSessionClients->horizontalHeader()->setCascadingSectionResizes(true);
        tableSessionClients->horizontalHeader()->setMinimumSectionSize(0);
        tableSessionClients->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tableSessionClients->verticalHeader()->setCascadingSectionResizes(true);

        gridLayout_3->addWidget(tableSessionClients, 2, 0, 1, 2);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 9, 0, 1, 1);

        btnCreateAClient = new QPushButton(centralwidget);
        btnCreateAClient->setObjectName(QString::fromUtf8("btnCreateAClient"));

        gridLayout_3->addWidget(btnCreateAClient, 13, 0, 1, 1);

        tableClients = new QTableView(centralwidget);
        tableClients->setObjectName(QString::fromUtf8("tableClients"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableClients->sizePolicy().hasHeightForWidth());
        tableClients->setSizePolicy(sizePolicy1);
        tableClients->horizontalHeader()->setCascadingSectionResizes(true);
        tableClients->horizontalHeader()->setStretchLastSection(true);
        tableClients->verticalHeader()->setVisible(true);

        gridLayout_3->addWidget(tableClients, 11, 0, 1, 2);

        btnClientDetailsDB = new QPushButton(centralwidget);
        btnClientDetailsDB->setObjectName(QString::fromUtf8("btnClientDetailsDB"));

        gridLayout_3->addWidget(btnClientDetailsDB, 12, 1, 1, 1);

        btnClientDetails = new QPushButton(centralwidget);
        btnClientDetails->setObjectName(QString::fromUtf8("btnClientDetails"));

        gridLayout_3->addWidget(btnClientDetails, 5, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout_3, 1, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        gridLayout->setHorizontalSpacing(200);
        numRefreshSeconds = new QSpinBox(centralwidget);
        numRefreshSeconds->setObjectName(QString::fromUtf8("numRefreshSeconds"));
        numRefreshSeconds->setMinimum(1);
        numRefreshSeconds->setMaximum(999999999);
        numRefreshSeconds->setSingleStep(1);
        numRefreshSeconds->setValue(10);

        gridLayout->addWidget(numRefreshSeconds, 12, 1, 1, 1);

        btnConfigureDatabase = new QPushButton(centralwidget);
        btnConfigureDatabase->setObjectName(QString::fromUtf8("btnConfigureDatabase"));

        gridLayout->addWidget(btnConfigureDatabase, 14, 1, 1, 1);

        btnReload = new QPushButton(centralwidget);
        btnReload->setObjectName(QString::fromUtf8("btnReload"));

        gridLayout->addWidget(btnReload, 14, 0, 1, 1);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 5, 0, 1, 2);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 0, 0, 1, 2);

        chkRefresh = new QCheckBox(centralwidget);
        chkRefresh->setObjectName(QString::fromUtf8("chkRefresh"));

        gridLayout->addWidget(chkRefresh, 12, 0, 1, 1);

        tableResults = new QTableView(centralwidget);
        tableResults->setObjectName(QString::fromUtf8("tableResults"));
        tableResults->horizontalHeader()->setCascadingSectionResizes(true);
        tableResults->horizontalHeader()->setStretchLastSection(true);

        gridLayout->addWidget(tableResults, 10, 0, 1, 2);


        gridLayout_2->addLayout(gridLayout, 1, 2, 2, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 943, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Abaci Server", nullptr));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        actionMinimize->setText(QApplication::translate("MainWindow", "Minimize", nullptr));
        actionExit_2->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        lblInternalIps->setText(QString());
        label_8->setText(QApplication::translate("MainWindow", "Internal Ip(s):", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Clients", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Connected Clients", nullptr));
        btnKickClient->setText(QApplication::translate("MainWindow", "Kick Client", nullptr));
        btnDeleteClient->setText(QApplication::translate("MainWindow", "Delete Client", nullptr));
        label->setText(QApplication::translate("MainWindow", "Database Clients", nullptr));
        btnCreateAClient->setText(QApplication::translate("MainWindow", "Create a Client", nullptr));
#ifndef QT_NO_TOOLTIP
        tableClients->setToolTip(QApplication::translate("MainWindow", "Authenticated clients are shown here", nullptr));
#endif // QT_NO_TOOLTIP
        btnClientDetailsDB->setText(QApplication::translate("MainWindow", "View Client Details", nullptr));
        btnClientDetails->setText(QApplication::translate("MainWindow", "View Client Details", nullptr));
#ifndef QT_NO_TOOLTIP
        numRefreshSeconds->setToolTip(QApplication::translate("MainWindow", "Number of seconds to wait before refeshing", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        btnConfigureDatabase->setToolTip(QApplication::translate("MainWindow", "Reconfigure the database", nullptr));
#endif // QT_NO_TOOLTIP
        btnConfigureDatabase->setText(QApplication::translate("MainWindow", "Configure", nullptr));
#ifndef QT_NO_TOOLTIP
        btnReload->setToolTip(QApplication::translate("MainWindow", "Reload data from the database", nullptr));
#endif // QT_NO_TOOLTIP
        btnReload->setText(QApplication::translate("MainWindow", "Reload", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Results", nullptr));
#ifndef QT_NO_TOOLTIP
        chkRefresh->setToolTip(QApplication::translate("MainWindow", "Refresh the data tables every second", nullptr));
#endif // QT_NO_TOOLTIP
        chkRefresh->setText(QApplication::translate("MainWindow", "Refresh every second", nullptr));
#ifndef QT_NO_TOOLTIP
        tableResults->setToolTip(QApplication::translate("MainWindow", "Prime numbers found will be shown here", nullptr));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
