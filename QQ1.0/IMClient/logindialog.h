#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include <QDialog>
#include<QCloseEvent>
namespace Ui
{
class LoginDialog;
}
class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    //重写关闭事件
    void closeEvent(QCloseEvent *event);
private slots:
    void on_pb_clear_register_clicked();
    void on_pb_commit_register_clicked();
    void on_pb_clear_clicked();
    void on_pb_commit_clicked();
signals:
    void SIG_RegisterCommit(QString name,QString tel,QString password);
    void SIG_LoginCommit(QString tel,QString password);
    //关闭登录和注册页面的信号
    void SIG_close();
private:
    Ui::LoginDialog *ui;
};
#endif // LOGINDIALOG_H
