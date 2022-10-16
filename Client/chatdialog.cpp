#include "chatdialog.h"
#include "ui_chatdialog.h"
#include<QTime>
ChatDialog::ChatDialog(QWidget *parent):QDialog(parent),ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::setInfo(QString name,int id)
{
    //Saves the user id and nickname corresponding to the current chat window
    m_id = id;
    m_name = name;
    setWindowTitle(QString("【%1】chat window").arg(m_name));
}

//Setting the Chat Content
void ChatDialog::setChatMsg(QString content)
{
    //Displays the content to the window
    ui->tb_chat->append(QString("[%1] %2").arg(m_name).arg(QTime::currentTime().toString("hh:mm:ss")));
    ui->tb_chat->append(content);
}

//Set chat friends not to be online
void ChatDialog::setFriendOffline()
{
    ui->tb_chat->append(QString("【%1】 %2 The user is not online").arg(m_name) .arg(QTime::currentTime().toString("hh:mm:ss")));
}

void ChatDialog::on_pb_send_clicked()
{
    //Obtain the input content and verify whether the input content is valid
    QString content =ui->te_chat->toPlainText();//Get the text
    if(content.isEmpty()){
        return;
    }
    //Clear the edit window
    content=ui->te_chat->toHtml();//Gets formatted text
    ui->te_chat->clear();
    //Displays the content to the browser window
    ui->tb_chat->append(QString("[me] %1").arg(QTime::currentTime().toString("hh:mm:ss")));
    ui->tb_chat->append(content);
    //Send the chat content and ip address to kernel
    Q_EMIT SIG_sendChatMsg(content,m_id);
}
