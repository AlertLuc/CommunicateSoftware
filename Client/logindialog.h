#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include <QWidget>
#include <QCloseEvent>
namespace Ui {
class LoginDialog;
}

class LoginDialog : public QWidget
{
    Q_OBJECT
signals:
    //Send the registration information to the kernel
    void SIG_RegisterCommit(QString name, QString tel, QString password);
    //The login information was sent to the kernel
    void SIG_LoginCommit( QString tel, QString password);
    //The login and registration page is closed
    void SIG_CloseLogin();
public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    //Override the close event
    void closeEvent(QCloseEvent* event);
private slots:
    void on_pb_clear_clicked();
    void on_pb_commit_clicked();
    void on_pb_clear_register_clicked();
    void on_pb_commit_register_clicked();
private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
