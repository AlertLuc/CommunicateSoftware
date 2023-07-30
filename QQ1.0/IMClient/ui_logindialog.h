/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *label;
    QTabWidget *tb_page;
    QWidget *tb_login;
    QLabel *lb_tel;
    QLineEdit *le_tel;
    QPushButton *pb_clear;
    QPushButton *pb_commit;
    QLabel *lb_password;
    QLineEdit *le_password;
    QWidget *tb_register;
    QLabel *lb_name_register;
    QLabel *lb_tel_register;
    QLabel *lb_password_register;
    QLineEdit *le_name_register;
    QLineEdit *le_tel_register;
    QLineEdit *le_password_register;
    QPushButton *pb_clear_register;
    QPushButton *pb_commit_register;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QStringLiteral("LoginDialog"));
        LoginDialog->resize(600, 450);
        label = new QLabel(LoginDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 250, 450));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/register.png")));
        label->setScaledContents(true);
        tb_page = new QTabWidget(LoginDialog);
        tb_page->setObjectName(QStringLiteral("tb_page"));
        tb_page->setGeometry(QRect(250, 0, 351, 451));
        tb_page->setMinimumSize(QSize(351, 451));
        tb_page->setMaximumSize(QSize(351, 451));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        tb_page->setFont(font);
        tb_login = new QWidget();
        tb_login->setObjectName(QStringLiteral("tb_login"));
        lb_tel = new QLabel(tb_login);
        lb_tel->setObjectName(QStringLiteral("lb_tel"));
        lb_tel->setGeometry(QRect(20, 100, 91, 41));
        le_tel = new QLineEdit(tb_login);
        le_tel->setObjectName(QStringLiteral("le_tel"));
        le_tel->setGeometry(QRect(100, 110, 201, 31));
        pb_clear = new QPushButton(tb_login);
        pb_clear->setObjectName(QStringLiteral("pb_clear"));
        pb_clear->setGeometry(QRect(40, 310, 90, 40));
        pb_clear->setMinimumSize(QSize(90, 40));
        pb_clear->setMaximumSize(QSize(90, 40));
        pb_clear->setFont(font);
        pb_clear->setStyleSheet(QLatin1String("QPushButton {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #dcdfe6;\n"
"    padding: 10px;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #ecf5ff;\n"
"    color: #409eff;\n"
"}\n"
"\n"
"QPushButton:pressed, QPushButton:checked {\n"
"    border: 1px solid #3a8ee6;\n"
"    color: #409eff;\n"
"}\n"
"\n"
"#button3 {\n"
"    border-radius: 20px;\n"
"}"));
        pb_commit = new QPushButton(tb_login);
        pb_commit->setObjectName(QStringLiteral("pb_commit"));
        pb_commit->setGeometry(QRect(200, 310, 90, 40));
        pb_commit->setMinimumSize(QSize(90, 40));
        pb_commit->setMaximumSize(QSize(90, 40));
        pb_commit->setFont(font);
        pb_commit->setStyleSheet(QLatin1String("QPushButton {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #dcdfe6;\n"
"    padding: 10px;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #ecf5ff;\n"
"    color: #409eff;\n"
"}\n"
"\n"
"QPushButton:pressed, QPushButton:checked {\n"
"    border: 1px solid #3a8ee6;\n"
"    color: #409eff;\n"
"}\n"
"\n"
"#button3 {\n"
"    border-radius: 20px;\n"
"}"));
        lb_password = new QLabel(tb_login);
        lb_password->setObjectName(QStringLiteral("lb_password"));
        lb_password->setGeometry(QRect(20, 190, 111, 51));
        le_password = new QLineEdit(tb_login);
        le_password->setObjectName(QStringLiteral("le_password"));
        le_password->setGeometry(QRect(100, 200, 201, 31));
        le_password->setEchoMode(QLineEdit::Password);
        tb_page->addTab(tb_login, QString());
        tb_register = new QWidget();
        tb_register->setObjectName(QStringLiteral("tb_register"));
        lb_name_register = new QLabel(tb_register);
        lb_name_register->setObjectName(QStringLiteral("lb_name_register"));
        lb_name_register->setGeometry(QRect(20, 60, 111, 51));
        lb_tel_register = new QLabel(tb_register);
        lb_tel_register->setObjectName(QStringLiteral("lb_tel_register"));
        lb_tel_register->setGeometry(QRect(20, 160, 91, 41));
        lb_password_register = new QLabel(tb_register);
        lb_password_register->setObjectName(QStringLiteral("lb_password_register"));
        lb_password_register->setGeometry(QRect(20, 260, 101, 41));
        le_name_register = new QLineEdit(tb_register);
        le_name_register->setObjectName(QStringLiteral("le_name_register"));
        le_name_register->setGeometry(QRect(100, 70, 201, 31));
        le_tel_register = new QLineEdit(tb_register);
        le_tel_register->setObjectName(QStringLiteral("le_tel_register"));
        le_tel_register->setGeometry(QRect(100, 170, 201, 31));
        le_password_register = new QLineEdit(tb_register);
        le_password_register->setObjectName(QStringLiteral("le_password_register"));
        le_password_register->setGeometry(QRect(100, 270, 201, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        le_password_register->setFont(font1);
        le_password_register->setEchoMode(QLineEdit::Password);
        pb_clear_register = new QPushButton(tb_register);
        pb_clear_register->setObjectName(QStringLiteral("pb_clear_register"));
        pb_clear_register->setGeometry(QRect(40, 340, 90, 40));
        pb_clear_register->setMinimumSize(QSize(90, 40));
        pb_clear_register->setMaximumSize(QSize(90, 40));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setWeight(50);
        pb_clear_register->setFont(font2);
        pb_clear_register->setStyleSheet(QLatin1String("QPushButton {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #dcdfe6;\n"
"    padding: 10px;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #ecf5ff;\n"
"    color: #409eff;\n"
"}\n"
"\n"
"QPushButton:pressed, QPushButton:checked {\n"
"    border: 1px solid #3a8ee6;\n"
"    color: #409eff;\n"
"}\n"
"\n"
"#button3 {\n"
"    border-radius: 20px;\n"
"}"));
        pb_commit_register = new QPushButton(tb_register);
        pb_commit_register->setObjectName(QStringLiteral("pb_commit_register"));
        pb_commit_register->setGeometry(QRect(220, 340, 90, 40));
        pb_commit_register->setMinimumSize(QSize(90, 40));
        pb_commit_register->setMaximumSize(QSize(90, 40));
        pb_commit_register->setFont(font2);
        pb_commit_register->setStyleSheet(QLatin1String("QPushButton {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #dcdfe6;\n"
"    padding: 10px;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #ecf5ff;\n"
"    color: #409eff;\n"
"}\n"
"\n"
"QPushButton:pressed, QPushButton:checked {\n"
"    border: 1px solid #3a8ee6;\n"
"    color: #409eff;\n"
"}\n"
"\n"
"#button3 {\n"
"    border-radius: 20px;\n"
"}"));
        tb_page->addTab(tb_register, QString());

        retranslateUi(LoginDialog);

        tb_page->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Dialog", 0));
        label->setText(QString());
        lb_tel->setText(QApplication::translate("LoginDialog", "\346\211\213\346\234\272\345\217\267", 0));
#ifndef QT_NO_TOOLTIP
        le_tel->setToolTip(QApplication::translate("LoginDialog", "<html><head/><body><p>\345\277\205\351\241\273\345\205\250\351\203\250\344\270\272\346\225\260\345\255\227\357\274\21411\344\275\215</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        le_tel->setText(QApplication::translate("LoginDialog", "18026652056", 0));
        pb_clear->setText(QApplication::translate("LoginDialog", "\346\270\205\347\251\272", 0));
        pb_commit->setText(QApplication::translate("LoginDialog", "\346\217\220\344\272\244", 0));
        lb_password->setText(QApplication::translate("LoginDialog", "\345\257\206\347\240\201", 0));
        le_password->setText(QApplication::translate("LoginDialog", "123", 0));
        tb_page->setTabText(tb_page->indexOf(tb_login), QApplication::translate("LoginDialog", "\347\231\273\345\275\225", 0));
        lb_name_register->setText(QApplication::translate("LoginDialog", "\346\230\265\347\247\260", 0));
#ifndef QT_NO_TOOLTIP
        lb_tel_register->setToolTip(QApplication::translate("LoginDialog", "<html><head/><body><p>\345\205\250\351\203\250\346\230\257\346\225\260\345\255\227\357\274\21411\344\275\215</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        lb_tel_register->setText(QApplication::translate("LoginDialog", "\346\211\213\346\234\272\345\217\267", 0));
        lb_password_register->setText(QApplication::translate("LoginDialog", "\345\257\206\347\240\201", 0));
#ifndef QT_NO_TOOLTIP
        le_name_register->setToolTip(QApplication::translate("LoginDialog", "<html><head/><body><p>\344\270\215\350\203\275\346\234\211\347\211\271\346\256\212\345\255\227\347\254\246\357\274\21410\344\275\215\344\273\245\345\206\205</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        le_tel_register->setToolTip(QApplication::translate("LoginDialog", "<html><head/><body><p>\345\205\250\351\203\250\344\270\272\346\225\260\345\255\227\357\274\214\344\270\215\350\266\205\350\277\20711\344\275\215</p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        pb_clear_register->setText(QApplication::translate("LoginDialog", "\346\270\205\347\251\272", 0));
        pb_commit_register->setText(QApplication::translate("LoginDialog", "\346\217\220\344\272\244", 0));
        tb_page->setTabText(tb_page->indexOf(tb_register), QApplication::translate("LoginDialog", "\346\263\250\345\206\214", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
