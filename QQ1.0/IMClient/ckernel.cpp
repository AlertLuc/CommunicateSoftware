#include "ckernel.h"
#include<QMessageBox>
#include"TcpClientMediator.h"
#include<QDebug>
#include"packDef.h"
#include <QTextCodec>
#include<QInputDialog>
#include<QList>
//计算数组下标的宏替换
#define NetPackFunmap(a) m_netProtocalMap[a-_DEF_PROTOCAL_BASE-1]
CKernel::CKernel(QObject *parent) : QObject(parent),m_id(0)
{
    setProtocalMp();
    //定义主窗口对话框，并显示
    m_mainWnd=new MyChatDialog;
    //m_mainWnd->show();

    //绑定添加好友的信号和槽函数
    connect(m_mainWnd,SIGNAL(SIG_addFriend()),
            this,SLOT(slot_addFriend()));

    //绑定关闭好友列表页面的信号和槽函数
    connect(m_mainWnd,SIGNAL(SIG_close()),
            this,SLOT(slot_close()));

    m_loginDlg=new LoginDialog;
    m_loginDlg->show();
    //绑定提交注册请求的信号和槽函数
    connect(m_loginDlg,SIGNAL(SIG_RegisterCommit(QString,QString,QString)),
            this,SLOT(slot_RegisterCommit(QString,QString,QString)));

    //绑定提示登录请求的信号和槽函数
    connect(m_loginDlg,SIGNAL(SIG_LoginCommit(QString,QString)),
            this,SLOT(slot_LoginCommit(QString,QString)));

    // 绑定处理关闭登录和注册界面的信号的槽函数
    connect(m_loginDlg,SIGNAL(SIG_close()),
            this,SLOT(slot_close()));


    //初始化中介者类
    m_tcpClient=new TcpClientMediator;

    //绑定发送所有接收到的数据的信号和槽函数
    connect(m_tcpClient,SIGNAL(SIG_ReadyData(long,char*,int)),
            this,SLOT(slot_ReadyData(long,char*,int)));

    //打开网络
    if(!m_tcpClient->OpenNet()){
            QMessageBox::about(m_mainWnd,"提示","打开网络失败");
            exit(0);
}
    //测试代码，给服务端发送hello world
//    m_tcpClient->SendData(0,"hello world",strlen("hello world")+1);
    //登陆回复
//    STRU_TCP_LOGIN_RS rs;
//    m_tcpClient->SendData(0,(char*)&rs,sizeof(rs));
//    for(int i=0;i<5;i++)
//    {
//        UserItem*item=new UserItem;
//        item->setInfo(QString ("用户%1").arg(i+1),"啥也没写",1,i,i+1);
//        m_mainWnd->addFriend(item);
//    }
//    for(int i=5;i<10;i++)
//    {
//        UserItem*item=new UserItem;
//        item->setInfo(QString ("用户%1").arg(i+1),"啥也没写",0,i,i+1);
//        m_mainWnd->addFriend(item);
//    }
}

CKernel::~CKernel()
{
    //回收资源
    //1、回收主窗口资源
    if(m_mainWnd){
        //隐藏窗口
        m_mainWnd->hide();
        delete m_mainWnd;
        m_mainWnd=NULL;
    }
    //2、回收中介者对象
    if(m_tcpClient){
        //关闭网络
        m_tcpClient->CloseNet();
        delete m_tcpClient;
        m_tcpClient=NULL;
    }
}

void CKernel::utf8ToGb2312(char *gbBuf, int nLen, QString &utf8)
{
    QTextCodec* gb2312 =QTextCodec::codecForName("gb2312");
    QByteArray ba = gb2312->fromUnicode(utf8);
    strcpy_s(gbBuf,nLen,ba.data());
}

QString CKernel::gb2312ToUtf8(char *gbBuf)
{
    QTextCodec* gb2312=QTextCodec::codecForName("gb2312");
    return gb2312->toUnicode(gbBuf);
}

void CKernel::setProtocalMp()
{
    //初始化
    memset(m_netProtocalMap,0,_DEF_PROTOCAL_COUNT);
    //绑定协议头和处理函数
   NetPackFunmap(_DEF_PACK_TCP_REGISTER_RS)    = &CKernel::dealRegisterRs;
   NetPackFunmap(_DEF_PACK_TCP_LOGIN_RS)       = &CKernel::dealLoginRs;
   NetPackFunmap(_DEF_PACK_TCP_FRIEND_INFO)    =&CKernel::dealFriendInfoRq;
   NetPackFunmap(_DEF_PACK_TCP_CHAT_RQ)        = &CKernel::dealChatRq;
   NetPackFunmap(_DEF_PACK_TCP_CHAT_RS)        = &CKernel::dealChatRs;
   NetPackFunmap(_DEF_PACK_TCP_ADDFRIEND_RQ)   = &CKernel::dealAddFriendRq;
   NetPackFunmap(_DEF_PACK_TCP_ADDFRIEND_RS)   = &CKernel::dealAddFriendRs;
   NetPackFunmap(_DEF_PACK_TCP_OFFLINE_RQ)   = &CKernel::dealOfflineRq;
}

//处理注册回复
void CKernel::dealRegisterRs(long ISendIp, char *buf, int nLen)
{
    qDebug()<<__func__;
    //拆包
    STRU_TCP_REGISTER_RS*rs=(STRU_TCP_REGISTER_RS*)buf;
    //根据注册结果显示提示信息
    switch(rs->result){
    case parameter_error:
        QMessageBox::about(m_loginDlg,"提示","注册失败，输入的信息有误");
        break;
    case user_is_exist:
        QMessageBox::about(m_loginDlg,"提示","注册失败，用户已存在");
          break;
    case register_success:
        QMessageBox::about(m_loginDlg,"提示","注册成功");
          break;
    default:
        break;
    }
}

//处理登录回复
void CKernel::dealLoginRs(long ISendIp, char *buf, int nLen)
{
    qDebug()<<__func__;
    //拆包
    STRU_TCP_LOGIN_RS* rs=( STRU_TCP_LOGIN_RS*)buf;
    //根据登录结果提示登录信息
    switch(rs->result){
    case parameter_error:
        QMessageBox::about(m_loginDlg,"提示","登录失败，输入信息错误");
        break;
    case user_not_exist:
        QMessageBox::about(m_loginDlg,"提示","登录失败，用户不存在");
        break;
    case password_error:
        QMessageBox::about(m_loginDlg,"提示","登录失败，密码错误");
        break;
    case login_success:
        //QMessageBox::about(m_loginDlg,"提示","登陆成功");
        {
        //1、隐藏登陆界面
        m_loginDlg->hide();
        //2、显示好友列表界面
        m_mainWnd->showNormal();
        //3、保存用户id
        m_id=rs->userId;
    }
        break;
    default:
        break;
    }
}

//处理好友信息请求
void CKernel::dealFriendInfoRq(long ISendIp, char *buf, int nLen)
{
    //1、拆包
    STRU_TCP_FRIEND_INFO* info=(STRU_TCP_FRIEND_INFO*)buf;
    //1.1、中文编码格式转换
    QString nameTemp=gb2312ToUtf8(info->name);
    QString feelingTemp=gb2312ToUtf8(info->feeling);
    //2、查看是不是自己的信息
    if(info->userId==m_id){
    //2.1、更新用户界面
    m_mainWnd->setInfo(nameTemp,feelingTemp,info->iconId);
    //2.2、保存自己的信息
     m_name==nameTemp;
    //2.2、直接返回
    return;
    }
    //3、窗口上之前没有这个好友
    if(m_mapIdToUserItem.find(info->userId)==m_mapIdToUserItem.end()){
    //3.1、new一个userItem
    UserItem*item=new UserItem;
    //3.2、设置userItem的属性
    item->setInfo(nameTemp,feelingTemp,info->state,info->iconId,info->userId);
    //3.3、把userItem添加到列表上
    m_mainWnd->addFriend(item);

    //3.4、绑定点击用户头像信号和槽函数
    connect(item,SIGNAL(SIG_userItemClicked(int)),
            this,SLOT(slot_userItemClicked(int)));

    //3.5、保存new出来的userItem
    m_mapIdToUserItem[info->userId]=item;
    //3.6、new聊天窗口对象
    ChatDialog* chatDlg=new ChatDialog;
    //3.7、设置聊天窗口对象
    chatDlg->setInfo(nameTemp,info->userId);

    //3.8、绑定发送聊天内容信号和槽函数
    connect(chatDlg,SIGNAL(SIG_sendChatMsg(int,QString)),
            this,SLOT(slot_sendChatMsg(int,QString)));

    //3.9、聊天窗口保存在map中管理
    m_mapIdToChatdlg[info->userId]=chatDlg;
    }
    else{
    //4、窗口上已经有这个好友了
    //4.1、取出这个好友的userItem
        UserItem* item=m_mapIdToUserItem[info->userId];
    //4.2、以前是下线状态，现在变成上线状态，可以提示好友上线，可以弹窗，也可以打印日志
    if(item && 0 == item->m_state && 1 == info->state){
        qDebug()<<QString("您的好友【%1】已上线").arg(nameTemp);
    }
    //4.3、更新好友信息
    item->setInfo(nameTemp,feelingTemp,info->state,info->iconId,info->userId);
    }
}

 //处理聊天请求
void CKernel::dealChatRq(long ISendIp, char *buf, int nLen)
{
     qDebug()<<__func__;
     //1、拆包
     STRU_TCP_CHAT_RQ*rq=(STRU_TCP_CHAT_RQ*)buf;
     //2、查看聊天窗口是否存在
     if(m_mapIdToChatdlg.find(rq->userId)!=m_mapIdToChatdlg.end()){
          //3、如果聊天窗口存在，就显示，并且设置聊天窗口到窗口
         ChatDialog* chatDlg=m_mapIdToChatdlg[rq->userId];
         chatDlg->setChatContent(rq->content);
         chatDlg->showNormal();
     }
}

//处理聊天回复
void CKernel::dealChatRs(long ISendIp, char *buf, int nLen)
{
     qDebug()<<__func__;
     //1、拆包
      STRU_TCP_CHAT_RS* rq=(STRU_TCP_CHAT_RS*)buf;
     //2、设置用户不在线
     if(m_mapIdToChatdlg.find(rq->friendId)!=m_mapIdToChatdlg.end()){
         ChatDialog* ChatDlg=m_mapIdToChatdlg[rq->friendId];
         ChatDlg->setUserOffline();
         ChatDlg->showNormal();
     }
}

//处理添加好友请求
void CKernel::dealAddFriendRq(long ISendIp, char *buf, int nLen)
{
     qDebug()<<__func__;
     //1、拆包
     STRU_TCP_ADD_FRIEND_RQ*rq=(STRU_TCP_ADD_FRIEND_RQ*)buf;
     STRU_TCP_ADD_FRIEND_RS rs;
     //2、弹出提示框，询问是否添加好友
     QString str=QString("用户[%1]请求添加你为好友，是否同意？").arg(rq->userName);
     if(QMessageBox::Yes==QMessageBox::question(m_mainWnd,"添加好友",str)){
         rs.result=add_success;
     }
     else{
         rs.result=user_refuse;
     }
     rs.friendId=m_id;
     rs.userId=rq->userId;
     strcpy(rs.friendName,m_name.toStdString().c_str());
     m_tcpClient->SendData(0,(char*)&rs,sizeof(rs));
}

 //处理添加好友回复
void CKernel::dealAddFriendRs(long ISendIp, char *buf, int nLen)
{
     qDebug()<<__func__;
     //1、拆包
     STRU_TCP_ADD_FRIEND_RS*rs=( STRU_TCP_ADD_FRIEND_RS*)buf;
     //1.1、用户名转码
     QString strName=gb2312ToUtf8(rs->friendName);
     //2、根据结果提示信息
     switch(rs->result){
     case no_this_user :
         QMessageBox::about(m_mainWnd,"提示",QString("[%1]用户不存在，添加好友失败").arg(strName));
         break;
     case user_offline:
          QMessageBox::about(m_mainWnd,"提示",QString("[%1]用户不在线，添加好友失败").arg(strName));
         break;
     case user_refuse:
          QMessageBox::about(m_mainWnd,"提示",QString("[%1]用户拒绝添加，添加好友失败").arg(rs->friendName));
         break;
     case add_success:
          QMessageBox::about(m_mainWnd,"提示",QString("添加好友[%1]成功").arg(rs->friendName));
         break;
     default:
         break;
     }
}

 //处理下线请求
void CKernel::dealOfflineRq(long ISendIp, char *buf, int nLen)
{
    qDebug()<<__func__;
    //1、拆包
    STRU_TCP_OFFLINE_RQ*rq=( STRU_TCP_OFFLINE_RQ*)buf;
    //2、取出下线好友的id获取到线下好友的useritrm
    if(m_mapIdToUserItem.count(rq->userId)>0) {
          //3、把下线好友的头像置灰
        UserItem*item=m_mapIdToUserItem[rq->userId];
        item->setOffline();
    }
}

//处理接收到的所有数据
void CKernel::slot_ReadyData(long ISendIp, char *buf, int nLen)
{
    qDebug()<<__func__<<":"<<buf;
    //1、取出协议头
    int nType=*(int*)buf;
    //2、根据协议头计算出数组中对应的处理函数
    if(nType>=_DEF_PROTOCAL_BASE+1 && nType<=_DEF_PROTOCAL_BASE+_DEF_PROTOCAL_COUNT){
        //计算出数组下标，取出下标中存在的函数指针
        PFUN pf=NetPackFunmap(nType);
        //如果指针存在，调用指针指向函数
        if(pf){
            (this->*pf)(ISendIp,buf,nLen);
        }
    }
    //处理完处理，回收空间
    delete[] buf;
}

//处理注册请求信号
void CKernel::slot_RegisterCommit(QString name, QString tel, QString password)
{
     qDebug()<<__func__;
     //1、数据格式转换
     //std::string nameStr=name.toStdString();
     std::string telStr=tel.toStdString();
     std::string passwordStr=password.toStdString();
     //2、封包
     STRU_TCP_REGISTER_RQ rq;
     utf8ToGb2312(rq.name,sizeof(rq.name),name);
     //strcpy(rq.name,nameStr.c_str());
     strcpy(rq.tel,telStr.c_str());
     strcpy(rq.password,passwordStr.c_str());
     //3、把数据发给服务器
     m_tcpClient->SendData(0,(char*)&rq,sizeof(rq));
}

//处理登录请求信号
void CKernel::slot_LoginCommit(QString tel, QString password)
{
     qDebug()<<__func__;
     //1、数据格式转换
     std::string telStr=tel.toStdString();
     std::string passwordStr=password.toStdString();
     //2、封包
     STRU_TCP_LOGIN_RQ rq;
     strcpy(rq.tel,telStr.c_str());
     strcpy(rq.password,passwordStr.c_str());
     //3、把数据发给服务器
      m_tcpClient->SendData(0,(char*)&rq,sizeof(rq));
}

  //处理聊天信息信号
void CKernel::slot_sendChatMsg(int id, QString content)
{
    qDebug()<<__func__;
    //1、封包
      STRU_TCP_CHAT_RQ rq;
      rq.userId=m_id;
      rq.friendId=id;
      strcpy(rq.content,content.toStdString().c_str());
    //2、把数据发给服务器
      m_tcpClient->SendData(0,(char*)&rq,sizeof(rq));
}

//处理用户点击好友头像的信号
void CKernel::slot_userItemClicked(int id)
{
     qDebug()<<__func__;
    //查看与好友的聊天窗口是否存在，存在就显示出来
    if(m_mapIdToChatdlg.find(id)!=m_mapIdToChatdlg.end()){
        ChatDialog* chatDlg=m_mapIdToChatdlg[id];
        chatDlg->showNormal();
    }
}

//处理添加好友信号
void CKernel::slot_addFriend()
{
     qDebug()<<__func__;
     //1、弹出一个添加好友的对话框
     QString strName=QInputDialog::getText(m_mainWnd,"添加好友","请输入好友的名字：");
     //2、校验用户输入数据是否合法
     if(strName.isEmpty()||strName.length()>10){
         QMessageBox::about(m_mainWnd,"提示","输入昵称不合法");
         return;
     }
     //3、判断是不是自己，不能添加自己为好友
     if(m_name==strName){
         QMessageBox::about(m_mainWnd,"提示","不能添加自己为好友");
         return;
     }
     //4、判断是不是已经为好友了,如果是好友，提示不能添加
     for(auto ite=m_mapIdToUserItem.begin();ite!=m_mapIdToUserItem.end();ite++){
         UserItem* item=*ite;
     if(item->m_name==strName){
         QMessageBox::about(m_mainWnd,"提示","已经是好友了，不允许再添加");
         return;
     }
     }
     //5、发送添加请求给服务端
     STRU_TCP_ADD_FRIEND_RQ rq;
     rq.userId=m_id;
     strcpy(rq.userName,m_name.toStdString().c_str());
     utf8ToGb2312(rq.friendName,sizeof(rq.friendName),strName);
     m_tcpClient->SendData(0,(char*)&rq,sizeof(rq));
}

  //处理关闭登录和注册页面的信号
void CKernel::slot_close()
{
      qDebug()<<__func__;
      //回收资源
      //1、登录和注册界面指针
      if(m_loginDlg){
          m_loginDlg->hide();
          delete m_tcpClient;
          m_tcpClient=NULL;
      }
      //2、中介者类指针
      if(m_tcpClient){
          m_tcpClient->CloseNet();
          delete m_tcpClient;
          m_tcpClient=NULL;
      }
      //3、好友列表窗口
      if(m_mainWnd) {
          m_mainWnd->hide();
          delete m_mainWnd;
          m_mainWnd=NULL;
      }
      //4、聊天窗口指针
      for(auto ite=m_mapIdToChatdlg.begin();ite!=m_mapIdToChatdlg.end();){
          ChatDialog *chat= *ite;
          if(chat) {
              chat->hide();
              delete chat;
              chat=NULL;
          }
      ite = m_mapIdToChatdlg.erase(ite);
      }
      //5、退出应用程序
      exit(0);
}

//处理关闭好友列表页面的信号
void CKernel::slot_offline()
{
      qDebug()<<__func__;
    //1、给服务端发送线下请求
    STRU_TCP_OFFLINE_RQ rq;
    rq.userId=m_id;
    m_tcpClient->SendData(0,(char*)&rq,sizeof(rq));
    //2、回收资源
    slot_close();
}


