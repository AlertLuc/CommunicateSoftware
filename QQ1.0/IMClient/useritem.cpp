#include "useritem.h"
#include "ui_useritem.h"
#include<QDebug>
#include<QBitmap>
UserItem::UserItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserItem)
{
    ui->setupUi(this);
}

UserItem::~UserItem()
{
    delete ui;
}

//设置好友信息
void UserItem::setInfo(QString name, QString feeling, int state, int icon, int id)
{
    //1、保存好友信息
    m_name = name;
    m_feeling=feeling;
    m_state=state;
    m_icon=icon;
    m_id=id;
    //2、把好友信息显示到界面上
    ui->lb_name->setText(m_name);
    ui->lb_feeling->setText(m_feeling);
    //设置好友头像，根据状态判断，显示彩色还是灰色的头像
    QString iconPath=QString(":/tx/%1.png").arg(m_icon);
    qDebug()<<"iconPath:"<<iconPath;
    if(m_state) {
        //在线，显示彩色头像
       ui->pb_icon->setIcon(QIcon(iconPath));
    }
    else{
        //不在线，显示灰色头像
        QBitmap bmp;
        bmp.load(iconPath);
        ui->pb_icon->setIcon(bmp);
        }
    //3、重绘
    this->repaint();
}

 //把头像置灰
void UserItem::setOffline()
{
    QString iconPath=QString(":/tx/%1.png").arg(m_icon);
    qDebug()<<"iconPath:"<<iconPath;
        QBitmap bmp;
        bmp.load(iconPath);
        ui->pb_icon->setIcon(bmp);
    //3、重绘
    this->repaint();
}

void UserItem::on_pb_icon_clicked()
{
    //发送点击信号给kernel
    Q_EMIT SIG_userItemClicked(m_id);
}
