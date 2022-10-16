/********************************************************************************
** Form generated from reading UI file 'chatdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATDIALOG_H
#define UI_CHATDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_ChatDialog
{
public:
    QTextEdit *te_chat;
    QPushButton *pb_send;
    QGroupBox *groupBox;
    QPushButton *pb_tool1;
    QPushButton *pb_tool2;
    QPushButton *pb_tool3;
    QTextBrowser *tb_chat;

    void setupUi(QDialog *ChatDialog)
    {
        if (ChatDialog->objectName().isEmpty())
            ChatDialog->setObjectName(QStringLiteral("ChatDialog"));
        ChatDialog->resize(753, 489);
        ChatDialog->setMinimumSize(QSize(753, 489));
        ChatDialog->setMaximumSize(QSize(753, 489));
        te_chat = new QTextEdit(ChatDialog);
        te_chat->setObjectName(QStringLiteral("te_chat"));
        te_chat->setGeometry(QRect(30, 330, 691, 111));
        pb_send = new QPushButton(ChatDialog);
        pb_send->setObjectName(QStringLiteral("pb_send"));
        pb_send->setGeometry(QRect(630, 450, 93, 28));
        groupBox = new QGroupBox(ChatDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 290, 691, 30));
        groupBox->setMinimumSize(QSize(100, 30));
        groupBox->setMaximumSize(QSize(1000, 30));
        pb_tool1 = new QPushButton(groupBox);
        pb_tool1->setObjectName(QStringLiteral("pb_tool1"));
        pb_tool1->setGeometry(QRect(0, 0, 30, 30));
        pb_tool1->setMinimumSize(QSize(30, 30));
        pb_tool1->setMaximumSize(QSize(30, 30));
        pb_tool2 = new QPushButton(groupBox);
        pb_tool2->setObjectName(QStringLiteral("pb_tool2"));
        pb_tool2->setGeometry(QRect(30, 0, 30, 30));
        pb_tool2->setMinimumSize(QSize(30, 30));
        pb_tool2->setMaximumSize(QSize(30, 30));
        pb_tool3 = new QPushButton(groupBox);
        pb_tool3->setObjectName(QStringLiteral("pb_tool3"));
        pb_tool3->setGeometry(QRect(60, 0, 30, 30));
        pb_tool3->setMinimumSize(QSize(30, 30));
        pb_tool3->setMaximumSize(QSize(30, 30));
        tb_chat = new QTextBrowser(ChatDialog);
        tb_chat->setObjectName(QStringLiteral("tb_chat"));
        tb_chat->setGeometry(QRect(30, 10, 691, 271));

        retranslateUi(ChatDialog);

        QMetaObject::connectSlotsByName(ChatDialog);
    } // setupUi

    void retranslateUi(QDialog *ChatDialog)
    {
        ChatDialog->setWindowTitle(QApplication::translate("ChatDialog", "Dialog", 0));
        pb_send->setText(QApplication::translate("ChatDialog", "\345\217\221\351\200\201", 0));
        groupBox->setTitle(QString());
        pb_tool1->setText(QString());
        pb_tool2->setText(QString());
        pb_tool3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ChatDialog: public Ui_ChatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATDIALOG_H
