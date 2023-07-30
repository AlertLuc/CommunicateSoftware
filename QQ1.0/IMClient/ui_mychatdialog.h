/********************************************************************************
** Form generated from reading UI file 'mychatdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYCHATDIALOG_H
#define UI_MYCHATDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyChatDialog
{
public:
    QLabel *lb_name;
    QPushButton *pb_icon;
    QLineEdit *le_feeling;
    QTabWidget *tabWidget;
    QWidget *page_space;
    QWidget *page_friend;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QWidget *wdg_list;
    QWidget *page_group;
    QPushButton *pb_menu;
    QPushButton *pushButton_3;
    QPushButton *pb_tool4;
    QPushButton *pb_tool5;
    QPushButton *pb_tool1;
    QPushButton *pb_tool2;

    void setupUi(QDialog *MyChatDialog)
    {
        if (MyChatDialog->objectName().isEmpty())
            MyChatDialog->setObjectName(QStringLiteral("MyChatDialog"));
        MyChatDialog->resize(300, 600);
        MyChatDialog->setMinimumSize(QSize(300, 600));
        MyChatDialog->setMaximumSize(QSize(300, 600));
        MyChatDialog->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        lb_name = new QLabel(MyChatDialog);
        lb_name->setObjectName(QStringLiteral("lb_name"));
        lb_name->setGeometry(QRect(90, 20, 118, 30));
        lb_name->setStyleSheet(QLatin1String("frame\n"
"{\n"
"alternate-background-color: rgb(255, 255, 255);\n"
"}"));
        pb_icon = new QPushButton(MyChatDialog);
        pb_icon->setObjectName(QStringLiteral("pb_icon"));
        pb_icon->setGeometry(QRect(10, 20, 60, 60));
        QIcon icon;
        icon.addFile(QStringLiteral(":/tx/5.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_icon->setIcon(icon);
        pb_icon->setIconSize(QSize(60, 60));
        le_feeling = new QLineEdit(MyChatDialog);
        le_feeling->setObjectName(QStringLiteral("le_feeling"));
        le_feeling->setGeometry(QRect(80, 50, 201, 30));
        le_feeling->setStyleSheet(QLatin1String("frame{\n"
"background-color: rgb(255, 255, 255);\n"
"}"));
        tabWidget = new QTabWidget(MyChatDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 90, 281, 481));
        tabWidget->setMinimumSize(QSize(0, 0));
        tabWidget->setMaximumSize(QSize(300, 600));
        tabWidget->setStyleSheet(QStringLiteral(""));
        page_space = new QWidget();
        page_space->setObjectName(QStringLiteral("page_space"));
        page_space->setStyleSheet(QStringLiteral("background-image: url(:/images/12.jpg);"));
        tabWidget->addTab(page_space, QString());
        page_friend = new QWidget();
        page_friend->setObjectName(QStringLiteral("page_friend"));
        page_friend->setStyleSheet(QStringLiteral("background-image: url(:/images/9.jpg);"));
        scrollArea = new QScrollArea(page_friend);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(0, 0, 281, 461));
        scrollArea->setStyleSheet(QStringLiteral(""));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 279, 459));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 3, 0, 3);
        wdg_list = new QWidget(scrollAreaWidgetContents);
        wdg_list->setObjectName(QStringLiteral("wdg_list"));
        wdg_list->setStyleSheet(QStringLiteral(""));

        verticalLayout->addWidget(wdg_list);

        scrollArea->setWidget(scrollAreaWidgetContents);
        tabWidget->addTab(page_friend, QString());
        page_group = new QWidget();
        page_group->setObjectName(QStringLiteral("page_group"));
        page_group->setStyleSheet(QStringLiteral("background-image: url(:/images/8.jpg);"));
        tabWidget->addTab(page_group, QString());
        pb_menu = new QPushButton(MyChatDialog);
        pb_menu->setObjectName(QStringLiteral("pb_menu"));
        pb_menu->setGeometry(QRect(10, 570, 30, 30));
        pb_menu->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/ic_sysmen.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_menu->setIcon(icon1);
        pb_menu->setIconSize(QSize(50, 50));
        pb_menu->setFlat(true);
        pushButton_3 = new QPushButton(MyChatDialog);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(180, 570, 30, 30));
        pushButton_3->setStyleSheet(QStringLiteral("background: transparent;"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/01.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_3->setIcon(icon2);
        pushButton_3->setIconSize(QSize(26, 26));
        pushButton_3->setFlat(true);
        pb_tool4 = new QPushButton(MyChatDialog);
        pb_tool4->setObjectName(QStringLiteral("pb_tool4"));
        pb_tool4->setGeometry(QRect(220, 570, 30, 30));
        pb_tool4->setStyleSheet(QStringLiteral("background: transparent;"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/3.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_tool4->setIcon(icon3);
        pb_tool4->setIconSize(QSize(26, 26));
        pb_tool4->setFlat(true);
        pb_tool5 = new QPushButton(MyChatDialog);
        pb_tool5->setObjectName(QStringLiteral("pb_tool5"));
        pb_tool5->setGeometry(QRect(260, 570, 30, 30));
        pb_tool5->setStyleSheet(QStringLiteral("background: transparent;"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/2.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        pb_tool5->setIcon(icon4);
        pb_tool5->setIconSize(QSize(50, 50));
        pb_tool5->setFlat(true);
        pb_tool1 = new QPushButton(MyChatDialog);
        pb_tool1->setObjectName(QStringLiteral("pb_tool1"));
        pb_tool1->setGeometry(QRect(140, 570, 30, 30));
        pb_tool1->setMinimumSize(QSize(30, 30));
        pb_tool1->setMaximumSize(QSize(30, 30));
        pb_tool1->setStyleSheet(QStringLiteral("background: transparent;"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/4.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_tool1->setIcon(icon5);
        pb_tool1->setIconSize(QSize(24, 24));
        pb_tool1->setFlat(true);
        pb_tool2 = new QPushButton(MyChatDialog);
        pb_tool2->setObjectName(QStringLiteral("pb_tool2"));
        pb_tool2->setGeometry(QRect(100, 570, 30, 30));
        pb_tool2->setMinimumSize(QSize(30, 30));
        pb_tool2->setMaximumSize(QSize(30, 30));
        pb_tool2->setStyleSheet(QStringLiteral("background: transparent;"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/groupChat 2.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_tool2->setIcon(icon6);
        pb_tool2->setIconSize(QSize(30, 30));
        pb_tool2->setFlat(true);

        retranslateUi(MyChatDialog);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MyChatDialog);
    } // setupUi

    void retranslateUi(QDialog *MyChatDialog)
    {
        MyChatDialog->setWindowTitle(QApplication::translate("MyChatDialog", "MyChatDialog", 0));
        lb_name->setText(QApplication::translate("MyChatDialog", "Luc", 0));
        pb_icon->setText(QString());
        le_feeling->setText(QApplication::translate("MyChatDialog", "\350\202\245\345\256\205\344\270\200\344\270\252", 0));
        tabWidget->setTabText(tabWidget->indexOf(page_space), QApplication::translate("MyChatDialog", "\347\251\272\351\227\264", 0));
        tabWidget->setTabText(tabWidget->indexOf(page_friend), QApplication::translate("MyChatDialog", "\345\245\275\345\217\213", 0));
        tabWidget->setTabText(tabWidget->indexOf(page_group), QApplication::translate("MyChatDialog", "\347\276\244\347\273\204", 0));
        pb_menu->setText(QString());
        pushButton_3->setText(QString());
        pb_tool4->setText(QString());
        pb_tool5->setText(QString());
        pb_tool1->setText(QString());
        pb_tool2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MyChatDialog: public Ui_MyChatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYCHATDIALOG_H
