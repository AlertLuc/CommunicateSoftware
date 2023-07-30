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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatDialog
{
public:
    QPushButton *pb_send;
    QTableWidget *tableWidget;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout;
    QTextBrowser *tb_chat;
    QWidget *widget;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QFontComboBox *fontCbx;
    QComboBox *sizeCbx;
    QPushButton *pb_tool1;
    QPushButton *pb_tool2;
    QPushButton *pb_tool13;
    QPushButton *pb_tool3;
    QPushButton *pb_tool4;
    QPushButton *pb_tool10;
    QPushButton *pb_tool14;
    QPushButton *pb_tool5;
    QPushButton *pb_tool7;
    QTextEdit *te_chat;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pb_tool8;
    QPushButton *pb_tool9;
    QPushButton *pb_tool16;
    QPushButton *pb_tool11;
    QPushButton *pb_tool12;
    QPushButton *pb_tool17;
    QPushButton *pb_tool15;
    QPushButton *pb_tool6;

    void setupUi(QDialog *ChatDialog)
    {
        if (ChatDialog->objectName().isEmpty())
            ChatDialog->setObjectName(QStringLiteral("ChatDialog"));
        ChatDialog->resize(920, 500);
        ChatDialog->setMinimumSize(QSize(920, 500));
        ChatDialog->setMaximumSize(QSize(920, 500));
        pb_send = new QPushButton(ChatDialog);
        pb_send->setObjectName(QStringLiteral("pb_send"));
        pb_send->setGeometry(QRect(610, 460, 93, 28));
        pb_send->setMinimumSize(QSize(93, 28));
        pb_send->setMaximumSize(QSize(93, 28));
        pb_send->setStyleSheet(QStringLiteral(""));
        tableWidget = new QTableWidget(ChatDialog);
        if (tableWidget->columnCount() < 1)
            tableWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(710, 10, 200, 477));
        tableWidget->setMinimumSize(QSize(200, 477));
        tableWidget->setMaximumSize(QSize(200, 477));
        frame_2 = new QFrame(ChatDialog);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(0, 0, 713, 471));
        frame_2->setFrameShape(QFrame::NoFrame);
        verticalLayout = new QVBoxLayout(frame_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tb_chat = new QTextBrowser(frame_2);
        tb_chat->setObjectName(QStringLiteral("tb_chat"));
        tb_chat->setMinimumSize(QSize(691, 291));
        tb_chat->setMaximumSize(QSize(691, 291));
        tb_chat->setStyleSheet(QStringLiteral("background-image: url(:/images/10.jpg);"));

        verticalLayout->addWidget(tb_chat);

        widget = new QWidget(frame_2);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(691, 30));
        widget->setMaximumSize(QSize(691, 30));
        layoutWidget = new QWidget(widget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 691, 32));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        fontCbx = new QFontComboBox(layoutWidget);
        fontCbx->setObjectName(QStringLiteral("fontCbx"));
        fontCbx->setMinimumSize(QSize(260, 30));
        fontCbx->setMaximumSize(QSize(279, 30));

        horizontalLayout->addWidget(fontCbx);

        sizeCbx = new QComboBox(layoutWidget);
        sizeCbx->setObjectName(QStringLiteral("sizeCbx"));
        sizeCbx->setMinimumSize(QSize(87, 30));
        sizeCbx->setMaximumSize(QSize(87, 30));

        horizontalLayout->addWidget(sizeCbx);

        pb_tool1 = new QPushButton(layoutWidget);
        pb_tool1->setObjectName(QStringLiteral("pb_tool1"));
        pb_tool1->setMinimumSize(QSize(30, 30));
        pb_tool1->setMaximumSize(QSize(30, 30));
        pb_tool1->setStyleSheet(QStringLiteral(""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/bold.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_tool1->setIcon(icon);
        pb_tool1->setIconSize(QSize(26, 26));
        pb_tool1->setCheckable(true);
        pb_tool1->setChecked(false);
        pb_tool1->setFlat(true);

        horizontalLayout->addWidget(pb_tool1);

        pb_tool2 = new QPushButton(layoutWidget);
        pb_tool2->setObjectName(QStringLiteral("pb_tool2"));
        pb_tool2->setMinimumSize(QSize(30, 30));
        pb_tool2->setMaximumSize(QSize(30, 30));
        pb_tool2->setStyleSheet(QStringLiteral(""));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/under.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_tool2->setIcon(icon1);
        pb_tool2->setIconSize(QSize(26, 26));
        pb_tool2->setCheckable(true);
        pb_tool2->setChecked(false);
        pb_tool2->setFlat(true);

        horizontalLayout->addWidget(pb_tool2);

        pb_tool13 = new QPushButton(layoutWidget);
        pb_tool13->setObjectName(QStringLiteral("pb_tool13"));
        pb_tool13->setMinimumSize(QSize(30, 30));
        pb_tool13->setMaximumSize(QSize(30, 30));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/textitalic.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_tool13->setIcon(icon2);
        pb_tool13->setIconSize(QSize(26, 26));
        pb_tool13->setFlat(true);

        horizontalLayout->addWidget(pb_tool13);

        pb_tool3 = new QPushButton(layoutWidget);
        pb_tool3->setObjectName(QStringLiteral("pb_tool3"));
        pb_tool3->setMinimumSize(QSize(30, 30));
        pb_tool3->setMaximumSize(QSize(30, 30));
        pb_tool3->setStyleSheet(QStringLiteral(""));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/color.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_tool3->setIcon(icon3);
        pb_tool3->setIconSize(QSize(30, 30));
        pb_tool3->setCheckable(false);
        pb_tool3->setChecked(false);
        pb_tool3->setFlat(true);

        horizontalLayout->addWidget(pb_tool3);

        pb_tool4 = new QPushButton(layoutWidget);
        pb_tool4->setObjectName(QStringLiteral("pb_tool4"));
        pb_tool4->setMinimumSize(QSize(30, 30));
        pb_tool4->setMaximumSize(QSize(30, 30));
        pb_tool4->setStyleSheet(QStringLiteral(""));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_tool4->setIcon(icon4);
        pb_tool4->setIconSize(QSize(26, 26));
        pb_tool4->setCheckable(false);
        pb_tool4->setChecked(false);
        pb_tool4->setFlat(true);

        horizontalLayout->addWidget(pb_tool4);

        pb_tool10 = new QPushButton(layoutWidget);
        pb_tool10->setObjectName(QStringLiteral("pb_tool10"));
        pb_tool10->setMinimumSize(QSize(30, 30));
        pb_tool10->setMaximumSize(QSize(30, 30));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/88.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_tool10->setIcon(icon5);
        pb_tool10->setIconSize(QSize(26, 26));
        pb_tool10->setFlat(true);

        horizontalLayout->addWidget(pb_tool10);

        pb_tool14 = new QPushButton(layoutWidget);
        pb_tool14->setObjectName(QStringLiteral("pb_tool14"));
        pb_tool14->setMinimumSize(QSize(30, 30));
        pb_tool14->setMaximumSize(QSize(30, 30));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/images/77.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_tool14->setIcon(icon6);
        pb_tool14->setIconSize(QSize(30, 30));
        pb_tool14->setFlat(true);

        horizontalLayout->addWidget(pb_tool14);

        pb_tool5 = new QPushButton(layoutWidget);
        pb_tool5->setObjectName(QStringLiteral("pb_tool5"));
        pb_tool5->setMinimumSize(QSize(30, 30));
        pb_tool5->setMaximumSize(QSize(30, 30));
        pb_tool5->setStyleSheet(QStringLiteral(""));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_tool5->setIcon(icon7);
        pb_tool5->setIconSize(QSize(26, 26));
        pb_tool5->setCheckable(false);
        pb_tool5->setChecked(false);
        pb_tool5->setFlat(true);

        horizontalLayout->addWidget(pb_tool5);

        pb_tool7 = new QPushButton(layoutWidget);
        pb_tool7->setObjectName(QStringLiteral("pb_tool7"));
        pb_tool7->setMinimumSize(QSize(30, 30));
        pb_tool7->setMaximumSize(QSize(30, 30));
        pb_tool7->setStyleSheet(QStringLiteral(""));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/images/share.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_tool7->setIcon(icon8);
        pb_tool7->setIconSize(QSize(35, 35));
        pb_tool7->setCheckable(false);
        pb_tool7->setChecked(false);
        pb_tool7->setFlat(true);

        horizontalLayout->addWidget(pb_tool7);


        verticalLayout->addWidget(widget);

        te_chat = new QTextEdit(frame_2);
        te_chat->setObjectName(QStringLiteral("te_chat"));
        te_chat->setMinimumSize(QSize(691, 111));
        te_chat->setMaximumSize(QSize(691, 111));

        verticalLayout->addWidget(te_chat);

        layoutWidget1 = new QWidget(ChatDialog);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 460, 311, 32));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pb_tool8 = new QPushButton(layoutWidget1);
        pb_tool8->setObjectName(QStringLiteral("pb_tool8"));
        pb_tool8->setMinimumSize(QSize(30, 30));
        pb_tool8->setMaximumSize(QSize(30, 30));
        pb_tool8->setStyleSheet(QStringLiteral(""));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/images/5.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_tool8->setIcon(icon9);
        pb_tool8->setIconSize(QSize(26, 26));
        pb_tool8->setCheckable(false);
        pb_tool8->setChecked(false);
        pb_tool8->setFlat(true);

        horizontalLayout_2->addWidget(pb_tool8);

        pb_tool9 = new QPushButton(layoutWidget1);
        pb_tool9->setObjectName(QStringLiteral("pb_tool9"));
        pb_tool9->setMinimumSize(QSize(30, 30));
        pb_tool9->setMaximumSize(QSize(30, 30));
        pb_tool9->setStyleSheet(QStringLiteral(""));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/images/editcut.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_tool9->setIcon(icon10);
        pb_tool9->setIconSize(QSize(26, 26));
        pb_tool9->setCheckable(false);
        pb_tool9->setChecked(false);
        pb_tool9->setFlat(true);

        horizontalLayout_2->addWidget(pb_tool9);

        pb_tool16 = new QPushButton(layoutWidget1);
        pb_tool16->setObjectName(QStringLiteral("pb_tool16"));
        pb_tool16->setMinimumSize(QSize(30, 30));
        pb_tool16->setMaximumSize(QSize(30, 30));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/images/67.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_tool16->setIcon(icon11);
        pb_tool16->setIconSize(QSize(30, 30));
        pb_tool16->setFlat(true);

        horizontalLayout_2->addWidget(pb_tool16);

        pb_tool11 = new QPushButton(layoutWidget1);
        pb_tool11->setObjectName(QStringLiteral("pb_tool11"));
        pb_tool11->setMinimumSize(QSize(30, 30));
        pb_tool11->setMaximumSize(QSize(30, 30));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/images/29.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_tool11->setIcon(icon12);
        pb_tool11->setIconSize(QSize(26, 26));
        pb_tool11->setFlat(true);

        horizontalLayout_2->addWidget(pb_tool11);

        pb_tool12 = new QPushButton(layoutWidget1);
        pb_tool12->setObjectName(QStringLiteral("pb_tool12"));
        pb_tool12->setMinimumSize(QSize(30, 0));
        pb_tool12->setMaximumSize(QSize(30, 30));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/images/36.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_tool12->setIcon(icon13);
        pb_tool12->setIconSize(QSize(26, 26));
        pb_tool12->setFlat(true);

        horizontalLayout_2->addWidget(pb_tool12);

        pb_tool17 = new QPushButton(layoutWidget1);
        pb_tool17->setObjectName(QStringLiteral("pb_tool17"));
        pb_tool17->setMinimumSize(QSize(30, 30));
        pb_tool17->setMaximumSize(QSize(30, 30));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/images/22.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_tool17->setIcon(icon14);
        pb_tool17->setIconSize(QSize(26, 26));
        pb_tool17->setFlat(true);

        horizontalLayout_2->addWidget(pb_tool17);

        pb_tool15 = new QPushButton(layoutWidget1);
        pb_tool15->setObjectName(QStringLiteral("pb_tool15"));
        pb_tool15->setMinimumSize(QSize(30, 30));
        pb_tool15->setMaximumSize(QSize(30, 30));
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/images/103.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_tool15->setIcon(icon15);
        pb_tool15->setIconSize(QSize(30, 30));
        pb_tool15->setFlat(true);

        horizontalLayout_2->addWidget(pb_tool15);

        pb_tool6 = new QPushButton(layoutWidget1);
        pb_tool6->setObjectName(QStringLiteral("pb_tool6"));
        pb_tool6->setMinimumSize(QSize(30, 30));
        pb_tool6->setMaximumSize(QSize(30, 30));
        pb_tool6->setStyleSheet(QStringLiteral(""));
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/images/file.ico"), QSize(), QIcon::Normal, QIcon::Off);
        pb_tool6->setIcon(icon16);
        pb_tool6->setIconSize(QSize(26, 26));
        pb_tool6->setCheckable(false);
        pb_tool6->setChecked(false);
        pb_tool6->setFlat(true);

        horizontalLayout_2->addWidget(pb_tool6);


        retranslateUi(ChatDialog);

        QMetaObject::connectSlotsByName(ChatDialog);
    } // setupUi

    void retranslateUi(QDialog *ChatDialog)
    {
        ChatDialog->setWindowTitle(QApplication::translate("ChatDialog", "Dialog", 0));
        pb_send->setText(QApplication::translate("ChatDialog", "\345\217\221\351\200\201", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("ChatDialog", "\347\224\250\346\210\267\345\220\215", 0));
        sizeCbx->clear();
        sizeCbx->insertItems(0, QStringList()
         << QApplication::translate("ChatDialog", "8", 0)
         << QApplication::translate("ChatDialog", "9", 0)
         << QApplication::translate("ChatDialog", "10", 0)
         << QApplication::translate("ChatDialog", "11", 0)
         << QApplication::translate("ChatDialog", "12", 0)
         << QApplication::translate("ChatDialog", "13", 0)
         << QApplication::translate("ChatDialog", "14", 0)
         << QApplication::translate("ChatDialog", "15", 0)
         << QApplication::translate("ChatDialog", "16", 0)
         << QApplication::translate("ChatDialog", "17", 0)
         << QApplication::translate("ChatDialog", "18", 0)
         << QApplication::translate("ChatDialog", "19", 0)
         << QApplication::translate("ChatDialog", "20", 0)
         << QApplication::translate("ChatDialog", "21", 0)
         << QApplication::translate("ChatDialog", "7", 0)
         << QApplication::translate("ChatDialog", "6", 0)
         << QApplication::translate("ChatDialog", "5", 0)
         << QApplication::translate("ChatDialog", "4", 0)
         << QApplication::translate("ChatDialog", "3", 0)
         << QApplication::translate("ChatDialog", "2", 0)
        );
        pb_tool1->setText(QString());
        pb_tool2->setText(QString());
        pb_tool13->setText(QString());
        pb_tool3->setText(QString());
        pb_tool4->setText(QString());
        pb_tool10->setText(QString());
        pb_tool14->setText(QString());
        pb_tool5->setText(QString());
        pb_tool7->setText(QString());
        pb_tool8->setText(QString());
        pb_tool9->setText(QString());
        pb_tool16->setText(QString());
        pb_tool11->setText(QString());
        pb_tool12->setText(QString());
        pb_tool17->setText(QString());
        pb_tool15->setText(QString());
        pb_tool6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ChatDialog: public Ui_ChatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATDIALOG_H
