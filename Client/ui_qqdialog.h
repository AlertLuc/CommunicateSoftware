/********************************************************************************
** Form generated from reading UI file 'qqdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QQDIALOG_H
#define UI_QQDIALOG_H

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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QQDialog
{
public:
    QPushButton *pb_icon;
    QLabel *lb_name;
    QLineEdit *le_feeling;
    QTabWidget *tw_page;
    QWidget *page_message;
    QWidget *page_friend;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QSpacerItem *verticalSpacer;
    QWidget *page_space;
    QPushButton *pb_tool1;
    QPushButton *pb_tool2;
    QPushButton *pb_tool3;
    QPushButton *pb_tool4;

    void setupUi(QDialog *QQDialog)
    {
        if (QQDialog->objectName().isEmpty())
            QQDialog->setObjectName(QStringLiteral("QQDialog"));
        QQDialog->resize(320, 700);
        pb_icon = new QPushButton(QQDialog);
        pb_icon->setObjectName(QStringLiteral("pb_icon"));
        pb_icon->setGeometry(QRect(10, 20, 60, 60));
        QIcon icon;
        icon.addFile(QStringLiteral(":/tx/24.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_icon->setIcon(icon);
        pb_icon->setIconSize(QSize(60, 60));
        pb_icon->setFlat(true);
        lb_name = new QLabel(QQDialog);
        lb_name->setObjectName(QStringLiteral("lb_name"));
        lb_name->setGeometry(QRect(90, 20, 81, 30));
        le_feeling = new QLineEdit(QQDialog);
        le_feeling->setObjectName(QStringLiteral("le_feeling"));
        le_feeling->setGeometry(QRect(90, 50, 211, 30));
        tw_page = new QTabWidget(QQDialog);
        tw_page->setObjectName(QStringLiteral("tw_page"));
        tw_page->setGeometry(QRect(10, 90, 300, 580));
        page_message = new QWidget();
        page_message->setObjectName(QStringLiteral("page_message"));
        tw_page->addTab(page_message, QString());
        page_friend = new QWidget();
        page_friend->setObjectName(QStringLiteral("page_friend"));
        scrollArea = new QScrollArea(page_friend);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(0, 0, 291, 551));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 289, 549));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 3, 0, 3);
        widget = new QWidget(scrollAreaWidgetContents);
        widget->setObjectName(QStringLiteral("widget"));

        verticalLayout->addWidget(widget);

        verticalSpacer = new QSpacerItem(48, 523, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);
        tw_page->addTab(page_friend, QString());
        page_space = new QWidget();
        page_space->setObjectName(QStringLiteral("page_space"));
        tw_page->addTab(page_space, QString());
        pb_tool1 = new QPushButton(QQDialog);
        pb_tool1->setObjectName(QStringLiteral("pb_tool1"));
        pb_tool1->setGeometry(QRect(10, 670, 30, 30));
        pb_tool2 = new QPushButton(QQDialog);
        pb_tool2->setObjectName(QStringLiteral("pb_tool2"));
        pb_tool2->setGeometry(QRect(180, 670, 30, 30));
        pb_tool3 = new QPushButton(QQDialog);
        pb_tool3->setObjectName(QStringLiteral("pb_tool3"));
        pb_tool3->setGeometry(QRect(230, 670, 30, 30));
        pb_tool4 = new QPushButton(QQDialog);
        pb_tool4->setObjectName(QStringLiteral("pb_tool4"));
        pb_tool4->setGeometry(QRect(280, 670, 30, 30));

        retranslateUi(QQDialog);

        tw_page->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(QQDialog);
    } // setupUi

    void retranslateUi(QDialog *QQDialog)
    {
        QQDialog->setWindowTitle(QApplication::translate("QQDialog", "QQDialog", 0));
        pb_icon->setText(QString());
        lb_name->setText(QApplication::translate("QQDialog", "\346\242\201\345\230\211\345\256\234", 0));
        tw_page->setTabText(tw_page->indexOf(page_message), QApplication::translate("QQDialog", "\346\266\210\346\201\257", 0));
        tw_page->setTabText(tw_page->indexOf(page_friend), QApplication::translate("QQDialog", "\350\201\224\347\263\273\344\272\272", 0));
        tw_page->setTabText(tw_page->indexOf(page_space), QApplication::translate("QQDialog", "\347\251\272\351\227\264", 0));
        pb_tool1->setText(QString());
        pb_tool2->setText(QString());
        pb_tool3->setText(QString());
        pb_tool4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class QQDialog: public Ui_QQDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QQDIALOG_H
