/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *screenLabel;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *spinBox;
    QLabel *label;
    QCheckBox *checkBox;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *newScreenShotButton;
    QPushButton *savePictureButton;
    QPushButton *quitButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(710, 771);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        screenLabel = new QLabel(centralWidget);
        screenLabel->setObjectName(QStringLiteral("screenLabel"));

        verticalLayout_3->addWidget(screenLabel);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setStyleSheet(QStringLiteral("background-image: url(:/images/66.jpg);"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setStyleSheet(QLatin1String("background: transparent;\n"
""));
        spinBox->setMinimum(1);

        horizontalLayout_2->addWidget(spinBox);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QString::fromUtf8("background: transparent;\n"
"font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(label);


        verticalLayout->addLayout(horizontalLayout_2);

        checkBox = new QCheckBox(groupBox);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setStyleSheet(QString::fromUtf8("background: transparent;\n"
"font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(checkBox);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        newScreenShotButton = new QPushButton(groupBox);
        newScreenShotButton->setObjectName(QStringLiteral("newScreenShotButton"));
        newScreenShotButton->setStyleSheet(QString::fromUtf8("background: transparent;\n"
"font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);\n"
""));
        newScreenShotButton->setFlat(true);

        horizontalLayout->addWidget(newScreenShotButton);

        savePictureButton = new QPushButton(groupBox);
        savePictureButton->setObjectName(QStringLiteral("savePictureButton"));
        savePictureButton->setStyleSheet(QString::fromUtf8("background: transparent;\n"
"color: rgb(255, 255, 255);\n"
"font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        savePictureButton->setFlat(true);

        horizontalLayout->addWidget(savePictureButton);

        quitButton = new QPushButton(groupBox);
        quitButton->setObjectName(QStringLiteral("quitButton"));
        quitButton->setStyleSheet(QString::fromUtf8("background: transparent;\n"
"color: rgb(255, 255, 255);\n"
"font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        quitButton->setFlat(true);

        horizontalLayout->addWidget(quitButton);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_3->addWidget(groupBox);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 710, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        screenLabel->setText(QString());
        groupBox->setTitle(QApplication::translate("MainWindow", "\345\273\266\346\227\266\351\200\211\351\241\271", 0));
        label->setText(QApplication::translate("MainWindow", "\345\273\266\346\227\266\346\227\266\351\227\264\357\274\210s)", 0));
        checkBox->setText(QApplication::translate("MainWindow", "\346\230\257\345\220\246\345\273\266\346\227\266", 0));
        newScreenShotButton->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\346\210\252\345\233\276", 0));
        savePictureButton->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\346\210\252\345\233\276", 0));
        quitButton->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
