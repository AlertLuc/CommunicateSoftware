#include "useritem.h"
#include "ui_useritem.h"
#include<QDebug>
#include<QBitmap>
#include"packDef.h"
Useritem::Useritem(QWidget *parent) : QWidget(parent),ui(new Ui::Useritem)
{
    ui->setupUi(this);
}

Useritem::~Useritem()
{
    delete ui;
}

//Set friend information
//Set variables, set nicknames and signatures, reference header resources, determine user status, user online, user offline, redraw immediately
void Useritem::setInfo(int id, int iconId, int state, QString name, QString feeling)
{
    //Save Friend Information
    m_id=id;
    m_iconId=iconId;
    m_state=state;
    m_name=name;
    m_feeling=feeling;
    //Set the nickname and signature to the control
    ui->lb_name->setText(m_name);
    ui->lb_feeling->setText(m_feeling);
    //Show the profile picture according to your friend's status and spell out the path of the profile picture file
    QString path = QString(":/tx/%1.png").arg(m_iconId);
    if(m_state == status_online){
        //Online, shown in color
        ui->pushButton->setIcon(QIcon(path));
    }else{
        //If it is not online, it is shown in gray
        QBitmap bmp;
        bmp.load(path);
        ui->pushButton->setIcon(bmp);
    }
    //redraw
    this->repaint();
}

//Click on the picture
void Useritem::on_pushButton_clicked()
{
    qDebug()<<__func__;
    //Send the click signal to kernel
    Q_EMIT SIG_userItemClicked(m_id);
}

//Buy grey head
void Useritem::setoffline()
{
    QString path=QString(":/tx/%1.png").arg(m_iconId);
    QBitmap bmp;
    bmp.load(path);
    ui->pushButton->setIcon(bmp);
    //Redraw the control
    this->repaint();
}
