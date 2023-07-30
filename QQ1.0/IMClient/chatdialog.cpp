#include "chatdialog.h"
#include "ui_chatdialog.h"
#include<QTime>
#include "mainwindow.h"
#include<QToolButton>
#include<QDebug>
#include<QColorDialog>
#include<QFileDialog>
#include<QMessageBox>
ChatDialog::ChatDialog(QWidget *parent):QDialog(parent),ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
    //设置图标
    setWindowIcon(QPixmap(":/images/7.png"));


    //字体
    connect(ui->fontCbx,&QFontComboBox::currentFontChanged,[=](const QFont &font)
    {
        ui->te_chat->setCurrentFont(font);
        ui->te_chat->setFocus();
    });

    //字号

    void(QComboBox::*cbxsingal)(const QString &text)=&QComboBox::currentIndexChanged;
    connect(ui->sizeCbx,cbxsingal,[=](const QString &text)
    {
        ui->te_chat->setFontPointSize(text.toDouble());
        ui->te_chat->setFocus();
    });

    //加粗
    connect(ui->pb_tool1,&QToolButton::clicked,[=](bool isCheck)
    {
        if(isCheck){

            ui->te_chat->setFontWeight(QFont::Bold);
        }
    else{
             ui->te_chat->setFontWeight(QFont::Normal);
    }
    });

    //斜体
    connect(ui->pb_tool13,&QToolButton::clicked,[=](bool check)
    {
             ui->te_chat->setFontItalic(check);
    });

    //下划线
    connect(ui->pb_tool2,&QToolButton::clicked,[=](bool check)
    {

             ui->te_chat->setFontUnderline(check);
    });

    //字体颜色
    connect(ui->pb_tool3,&QToolButton::clicked,[=](){
       QColor color=QColorDialog::getColor(Qt::red);
       ui->te_chat->setTextColor(color);

    });

    //清空聊天记录
    connect(ui->pb_tool4,&QToolButton::clicked,[=](){
        ui->tb_chat->clear();
    });


    //保存聊天记录
    connect(ui->pb_tool5,&QToolButton::clicked,[=](){
        if(ui->tb_chat->document()->isEmpty())
        {
            QMessageBox::warning(this,"警告","路径或内容不能为空");
            return;
        }
        else{
        QString path=QFileDialog::getSaveFileName(this,"保存记录","聊天记录","(*.txt)");

            QFile file(path);
            //打开模式加换行
            file.open(QIODevice::WriteOnly|QIODevice::Text);
            QTextStream stream(&file);
            stream<<ui->tb_chat->toPlainText();
            file.close();
        }
    });
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::setInfo(QString name,int id)
{
    m_id=id;
    m_name=name;
    setWindowTitle(QString("与【%1】的聊天窗口").arg(m_name));
}

//设置聊天内容
void ChatDialog::setChatContent(QString content)
{
    //把内容显示到浏览器窗口，格式"[我] 时间 （换行）内容 "
    ui->tb_chat->append(QString("[%1] %2").arg(m_name).arg(QTime::currentTime().toString("hh:mm:ss")));
    ui->tb_chat->append(content);
}

//设置用户不存在
void ChatDialog::setUserOffline()
{
     ui->tb_chat->append(QString("[%1] %2 该用户不在线").arg(QTime::currentTime().toString("hh:mm:ss")).arg(m_name));
}

void ChatDialog::on_pb_send_clicked()
{
    //1、先获取输入内容，校验输入内容是否合法
    QString content =ui->te_chat->toPlainText();//获取文本
    if(content.isEmpty()){
        return;
    }
    //2、清空编辑窗口的内容
    content=ui->te_chat->toHtml();//获取带格式的文本
    ui->te_chat->clear();
    //3、把内容显示到浏览器窗口，格式"[我] 时间 （换行）内容 "
    ui->tb_chat->append(QString("[我] %1").arg(QTime::currentTime().toString("hh:mm:ss")));
    ui->tb_chat->append(content);
    //4、把聊天内容、ip地址发给kernel
    Q_EMIT SIG_sendChatMsg(m_id,content);
}

//点击截图
void ChatDialog::on_pb_tool9_clicked()
{
    MainWindow*w=new MainWindow;
    w->show();
}

//发送文件
void ChatDialog::on_pb_tool7_clicked()
{

}
