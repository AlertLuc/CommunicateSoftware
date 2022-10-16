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
    //Send chat data to kernel
    void SIG_sendChatMsg(QString content,int id);
public:
    explicit ChatDialog(QWidget *parent = 0);
    ~ChatDialog();
    //Set the chat window information
    void setInfo(QString name,int id);
    //Setting the Chat Content
    void setChatMsg(QString content);
    //Set chat friends not to be online
    void setFriendOffline();
private slots:
    void on_pb_send_clicked();
private:
    int m_id;
    QString m_name;
    Ui::ChatDialog *ui;
};
#endif // CHATDIALOG_H
