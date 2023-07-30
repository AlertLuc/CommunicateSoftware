#ifndef CHATDIALOG_H
#define CHATDIALOG_H
#include <QDialog>
#include<QString>
#include<QString>
namespace Ui
{
class ChatDialog;
}
class ChatDialog : public QDialog
{
    Q_OBJECT
signals:
    //发送聊天数据给kernel
    void SIG_sendChatMsg(int id,QString content);
public:
    explicit ChatDialog(QWidget *parent = 0);
    ~ChatDialog();
    //设置聊天窗口信息
    void setInfo(QString name,int id);
    //设置聊天内容
    void setChatContent(QString content);
    //设置用户不在线
    void setUserOffline();
private slots:
    void on_pb_send_clicked();
    void on_pb_tool9_clicked();

    void on_pb_tool7_clicked();

private:
    Ui::ChatDialog *ui;
    int m_id;
    QString m_name;
};
#endif // CHATDIALOG_H
