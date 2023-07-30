/********************************************************************************
** Form generated from reading UI file 'game.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_H
#define UI_GAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_game
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pb_xq;
    QPushButton *pb_hb;
    QPushButton *pb_fly;
    QPushButton *pushButton_4;

    void setupUi(QDialog *game)
    {
        if (game->objectName().isEmpty())
            game->setObjectName(QStringLiteral("game"));
        game->resize(651, 442);
        widget = new QWidget(game);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 20, 335, 91));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pb_xq = new QPushButton(widget);
        pb_xq->setObjectName(QStringLiteral("pb_xq"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/xq.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_xq->setIcon(icon);
        pb_xq->setIconSize(QSize(60, 60));
        pb_xq->setFlat(true);

        horizontalLayout->addWidget(pb_xq);

        pb_hb = new QPushButton(widget);
        pb_hb->setObjectName(QStringLiteral("pb_hb"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/g1.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_hb->setIcon(icon1);
        pb_hb->setIconSize(QSize(60, 60));
        pb_hb->setFlat(true);

        horizontalLayout->addWidget(pb_hb);

        pb_fly = new QPushButton(widget);
        pb_fly->setObjectName(QStringLiteral("pb_fly"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/g2.png"), QSize(), QIcon::Normal, QIcon::Off);
        pb_fly->setIcon(icon2);
        pb_fly->setIconSize(QSize(80, 80));
        pb_fly->setFlat(true);

        horizontalLayout->addWidget(pb_fly);

        pushButton_4 = new QPushButton(widget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/g3.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_4->setIcon(icon3);
        pushButton_4->setIconSize(QSize(60, 60));
        pushButton_4->setFlat(true);

        horizontalLayout->addWidget(pushButton_4);


        retranslateUi(game);

        QMetaObject::connectSlotsByName(game);
    } // setupUi

    void retranslateUi(QDialog *game)
    {
        game->setWindowTitle(QApplication::translate("game", "Dialog", 0));
        pb_xq->setText(QString());
        pb_hb->setText(QString());
        pb_fly->setText(QString());
        pushButton_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class game: public Ui_game {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_H
