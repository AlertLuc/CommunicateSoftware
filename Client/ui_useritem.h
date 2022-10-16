/********************************************************************************
** Form generated from reading UI file 'useritem.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERITEM_H
#define UI_USERITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Useritem
{
public:
    QPushButton *pushButton;
    QLabel *lb_name;
    QLabel *lb_feeling;

    void setupUi(QWidget *Useritem)
    {
        if (Useritem->objectName().isEmpty())
            Useritem->setObjectName(QStringLiteral("Useritem"));
        Useritem->resize(270, 60);
        Useritem->setMinimumSize(QSize(270, 60));
        Useritem->setMaximumSize(QSize(270, 60));
        pushButton = new QPushButton(Useritem);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 10, 47, 47));
        QIcon icon;
        icon.addFile(QStringLiteral(":/tx/24.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(45, 45));
        pushButton->setFlat(true);
        lb_name = new QLabel(Useritem);
        lb_name->setObjectName(QStringLiteral("lb_name"));
        lb_name->setGeometry(QRect(81, 10, 81, 20));
        lb_feeling = new QLabel(Useritem);
        lb_feeling->setObjectName(QStringLiteral("lb_feeling"));
        lb_feeling->setGeometry(QRect(80, 36, 171, 20));

        retranslateUi(Useritem);

        QMetaObject::connectSlotsByName(Useritem);
    } // setupUi

    void retranslateUi(QWidget *Useritem)
    {
        Useritem->setWindowTitle(QApplication::translate("Useritem", "Form", 0));
        pushButton->setText(QString());
        lb_name->setText(QApplication::translate("Useritem", "\347\224\250\346\210\267\345\220\215", 0));
        lb_feeling->setText(QApplication::translate("Useritem", "\345\225\245\344\271\237\346\262\241\345\206\231", 0));
    } // retranslateUi

};

namespace Ui {
    class Useritem: public Ui_Useritem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERITEM_H
