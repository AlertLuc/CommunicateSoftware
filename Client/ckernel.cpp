#include<QDebug>
#include"packDef.h"
#include "ckernel.h"
#include<QTextCodec>
#include<QMessageBox>
#include<QInputDialog>
#include"TcpClientMediator.h"
#define NetPackFunmap(a) m_netProtocalMap[a-_DEF_PROTOCAL_BASE-1]
CKernel::CKernel(QObject *parent) : QObject(parent)
{
    setProtocalMp();
    //Defines the main window dialog box and displays it
    m_mainWnd=new QQDialog;
    //Bind the user to add a friend signal and slot function
    connect(m_mainWnd,SIGNAL(SIG_AddFriend()),this,SLOT(slot_AddFriend()));
    //Bind the signal and slot functions that close the buddy list interface
    connect(m_mainWnd,SIGNAL(SIG_CloseQQ()),this,SLOT(slot_CloseQQ()));
    //Initialize the mediator class
    m_tcpClient=new TcpClientMediator;
    //Bind the signal and slot function that sends all received data
    connect(m_tcpClient,SIGNAL(SIG_ReadyData(long,char*,int)),this,SLOT(slot_ReadyData(long,char*,int)));
    //Open the network
    if(!m_tcpClient->OpenNet()){
            QMessageBox::about(m_mainWnd,"prompt","Failed to open the network.");
            exit(0);
    }
    //The login and registration window is displayed
    m_pLoginDlg=new LoginDialog;
    m_pLoginDlg->showNormal();
    //After the login and registration window is created, signals and slots for registration information and login information are processed
    //Bind the signal that sends registration information to the slot function
    connect(m_pLoginDlg,SIGNAL(SIG_RegisterCommit(QString, QString , QString)),this,SLOT(slot_RegisterCommit(QString,QString,QString)));
    //Bind the signal that prompts the login request to the slot function
    connect(m_pLoginDlg,SIGNAL(SIG_LoginCommit(QString,QString)),this,SLOT(slot_LoginCommit(QString,QString)));
    //Bind to close the signal and slot function that registers logins
    connect(m_pLoginDlg,SIGNAL(SIG_CloseLogin()),this,SLOT(slot_CloseLogin()));
}

CKernel::~CKernel()
{
    slot_CloseLogin();
}

//QString to GB2312, call the codecForName method, create an object of the type to be converted, and use this object to call the fromUnicode function
void CKernel::Utf8ToGb2312(char *gbBuf, int nLen, QString utf8)
{
    //Transcoding object
    QTextCodec* gb2312code=QTextCodec::codecForName("gb2312");
    //Using the conversion object, install unicode aka utf8 to gb2312
    QByteArray ba =gb2312code->fromUnicode(utf8);
    //Uses the converted data to the target control
    strcpy_s(gbBuf,nLen,ba.data());
}

//GB2312 to QString, create GB2312 format QTextCodec object, directly using the QTextCodec object to call to Unicode, will return a QString
QString CKernel::Gb2312ToUtf8(char *gbBuf)
{
    //Transcoding object
    QTextCodec* gb2312code=QTextCodec::codecForName("gb2312");
    //Using the conversion object, convert gb2312 to unicode aka QString
    return gb2312code->toUnicode(gbBuf);
}

//Example Set protocol mapping
void CKernel::setProtocalMp()
{
   //Initializes the array, then binds the function to the corresponding subscript
   memset(m_netProtocalMap,0,_DEF_PROTOCAL_COUNT);
   //Bind the protocol header to the handler
   NetPackFunmap(_DEF_PACK_TCP_REGISTER_RS)    = &CKernel::dealRegisterRs;
   NetPackFunmap(_DEF_PACK_TCP_LOGIN_RS)       = &CKernel::dealLoginRs;
   NetPackFunmap(_DEF_PACK_TCP_FRIEND_INFO)    = &CKernel::dealFriendInfoRq;
   NetPackFunmap(_DEF_PACK_TCP_CHAT_RQ)        = &CKernel::DealChatRq;
   NetPackFunmap(_DEF_PACK_TCP_CHAT_RS)        = &CKernel::DealChatRs;
   NetPackFunmap(_DEF_PACK_TCP_ADDFRIEND_RQ)   = &CKernel::DealAddFriendRq;
   NetPackFunmap(_DEF_PACK_TCP_ADDFRIEND_RS)   = &CKernel::DealAddFriendRs;
}

//Processing Registration response
void CKernel::dealRegisterRs(long ISendIp, char *buf, int nLen)
{
    qDebug()<<__func__;
    //unpacking
    STRU_TCP_REGISTER_RS* rs=(STRU_TCP_REGISTER_RS*)buf;
    //Users are prompted according to the registration
    switch (rs->result) {
    case register_success:
     QMessageBox::about(m_pLoginDlg,"prompt","Registered successfully");
        break;
    case user_is_exist:
     QMessageBox::about(m_pLoginDlg,"prompt","The registration is successful. The mobile phone number has been registered");
        break;
    case name_is_used:
     QMessageBox::about(m_pLoginDlg,"prompt","The registration is successful and the nickname has been used");
        break;
    default:
        break;
    }
}

//Handling Login Replies
void CKernel::dealLoginRs(long ISendIp, char *buf, int nLen)
{
      qDebug()<<__func__;
      //unpacking
      STRU_TCP_LOGIN_RS* rs=( STRU_TCP_LOGIN_RS*)buf;
      //The login information is displayed based on the login result
      switch(rs->result){
      case parameter_error:
          QMessageBox::about(m_pLoginDlg,"prompt","Login failed because the input information is incorrect");
          break;
      case user_not_exist:
          QMessageBox::about(m_pLoginDlg,"prompt","Login failed because the user does not exist");
          break;
      case password_error:
          QMessageBox::about(m_pLoginDlg,"prompt","Login failed because the password is incorrect");
          break;
      case login_success:
      {
          m_pLoginDlg->hide();
          m_mainWnd->showNormal();
          m_id=rs->userId;
      }
          break;
      default:
          break;
      }
}

//Process friend information requests
void CKernel::dealFriendInfoRq(long ISendIp, char *buf, int nLen)
{
     qDebug()<<__func__;
    //unpacking
    STRU_TCP_FRIEND_INFO* info=(STRU_TCP_FRIEND_INFO*)buf;
    //Chinese coding format conversion
    QString nameTemp=Gb2312ToUtf8(info->name);
    QString feelingTemp=Gb2312ToUtf8(info->feeling);
    //Check to see if it's your message
    if(info->userId==m_id){
    //Update the user interface
    m_mainWnd->setInfo(nameTemp,feelingTemp,info->iconId);
    m_name = nameTemp;
    return;
    }
    //There was no previous friend in the window
    if(m_mapIdToUseritem.count(info->userId)>0){
    //A new userItem
    Useritem*item=m_mapIdToUseritem[info->userId];
    //Set the attribute of userItem
    item->setInfo(info->userId,info->iconId,info->state,nameTemp,feelingTemp);
    qDebug()<<QString("[%1]Has been launched").arg(nameTemp);
    }
    else{
        Useritem* item=new Useritem;
        item->setInfo(info->userId,info->iconId,info->state,nameTemp,feelingTemp);
    //Bind click user profile picture signal and slot function
    connect(item,SIGNAL(SIG_userItemClicked(int)),this,SLOT(slot_userItemClicked(int)));
    //Add the control to the list
    m_mainWnd->addFriend(item);
    //Put controls in a map to manage
    m_mapIdToUseritem[info->userId]=item;
    //Create a chat window with this friend and set the window information
    ChatDialog* chat=new ChatDialog;
    chat->setInfo(nameTemp,info->userId);
    //Manage Windows by putting them in a map
    m_mapIdToChatdlg[info->userId]=chat;
    //Bind a signal to send chat content and a slot function
    connect(chat,SIGNAL(SIG_sendChatMsg(QString,int)),this,SLOT(slot_sendChatMsg(QString,int)));
    }
}

//Handling Chat Replies
void CKernel::DealChatRs(long ISendIp, char *buf, int nLen)
{
    qDebug()<<__func__;
    STRU_TCP_CHAT_RS* rs=(STRU_TCP_CHAT_RS*)buf;
    //Check whether your friend's chat window exists
    if(m_mapIdToChatdlg.count(rs->friendId)>0){
        ChatDialog* chat=m_mapIdToChatdlg[rs->friendId];
        //Set the chat content to the chat window
        chat->setFriendOffline();
        chat->showNormal();
    }
}

//Processing Chat Requests
void CKernel::DealChatRq(long ISendIp, char *buf, int nLen)
{
     qDebug()<<__func__;
     //unpacking
     STRU_TCP_CHAT_RQ* rq=(STRU_TCP_CHAT_RQ*)buf;
     //Check whether your friend's chat window exists
     if(m_mapIdToChatdlg.count(rq->userId)>0){
         ChatDialog* chat=m_mapIdToChatdlg[rq->userId];
         //Set the chat content to the chat window
         chat->setChatMsg(rq->content);
         chat->showNormal();
     }
}

//Process all data received
void CKernel::slot_ReadyData(long ISendIp, char *buf, int nLen)
{
    qDebug()<<__func__<<":"<<buf;
    //Take out protocol header
    int nType = *(int*)buf;
    //The corresponding handler in the array is computed from the protocol header
    if(nType >= _DEF_PROTOCAL_BASE+1 && nType <= _DEF_PROTOCAL_BASE + _DEF_PROTOCAL_COUNT){
        //Computes the array subscript and retrieves any function Pointers present in the subscript
        PFUN pf=NetPackFunmap(nType);
        //If the pointer exists, call the pointer to the function
        if(pf){(this->*pf)(ISendIp,buf,nLen);}
    }
    //Recycling space
    delete[] buf;
}

//Process registration information and convert it to a standard string
void CKernel::slot_RegisterCommit(QString name, QString tel, QString password)
{
     qDebug()<<__func__;
     //Load the data into the structure
     STRU_TCP_REGISTER_RQ rq;
     //Packet, code conversion
     Utf8ToGb2312(rq.name,sizeof(rq.name),name);
     //strcpy(rq.name,name.toStdString().c_str());
     strcpy(rq.tel,tel.toStdString().c_str());
     strcpy(rq.password,password.toStdString().c_str());
     //Send the structure to the server
     m_tcpClient->SendData(0,(char*)&rq,sizeof(rq));
}

//Process the login information and convert it to a standard string
void CKernel::slot_LoginCommit(QString tel,QString password)
{
    qDebug()<<__func__;
    //Put data into the structure, encapsulation
    STRU_TCP_LOGIN_RQ rq;
    strcpy(rq.tel,tel.toStdString().c_str());
    strcpy(rq.password,password.toStdString().c_str());
    //Send the structure to the server
    m_tcpClient->SendData(0,(char*)&rq,sizeof(rq));
}

//Handles the signal of clicking on a friend's profile picture
void CKernel::slot_userItemClicked(int userId)
{
    qDebug()<<__func__;
    if(m_mapIdToChatdlg.count(userId)>0){
        ChatDialog* chat=m_mapIdToChatdlg[userId];
        chat->showNormal();
    }
}

//Handle the chat content to be sent
void CKernel::slot_sendChatMsg(QString content,int id)
{
     qDebug()<<__func__;
     //packaging
     STRU_TCP_CHAT_RQ rq;
     rq.userId=m_id;
     rq.friendId=id;
     //Send to the server
     strcpy(rq.content,content.toStdString().c_str());
     m_tcpClient->SendData(0,(char*)&rq,sizeof(rq));
}

//Process requests added by users
void CKernel::slot_AddFriend()
{
     qDebug()<<__func__;
     //A pop-up window lets the user enter the nickname they want to add as a friend
      QString strName=QInputDialog::getText(m_mainWnd,"Add buddy","Please enter your friend's name：");
     //Verify the validity of the input nickname
      if(strName.isEmpty()||strName.length()>10){
          QMessageBox::about(m_mainWnd,"prompt","The entered nickname is invalid");
          return;
      }
     //Verify that it is not your own nickname
      if(m_name==strName){
          QMessageBox::about(m_mainWnd,"prompt","Cannot add yourself as a friend");
          return;
      }
     //Verify that you are already friends
      for(auto ite=m_mapIdToUseritem.begin();ite!=m_mapIdToUseritem.end();ite++){
          Useritem* item=*ite;
      if(item->m_name==strName){
          QMessageBox::about(m_mainWnd,"prompt","Is already a friend, not allowed to add");
          return;
      }
   }
     //Send a friend request to the server
      STRU_TCP_ADD_FRIEND_RQ rq;
      rq.userId=m_id;
      strcpy(rq.userName,m_name.toStdString().c_str());
      Utf8ToGb2312(rq.friendName,sizeof(rq.friendName),strName);
      m_tcpClient->SendData(0,(char*)&rq,sizeof(rq));
}

void CKernel::slot_CloseLogin()
{
    qDebug()<<__func__;
    //recycling
    //Login and registration interface pointer
    if(m_pLoginDlg){
       m_pLoginDlg->hide();
       delete m_tcpClient;
       m_tcpClient=NULL;
    }
    //Mediator class pointer
    if(m_tcpClient){
       m_tcpClient->CloseNet();
       delete m_tcpClient;
       m_tcpClient=NULL;
    }
    //Friends List window
    if(m_mainWnd) {
       m_mainWnd->hide();
       delete m_mainWnd;
       m_mainWnd=NULL;
    }
    //Chat window pointer
    for(auto ite=m_mapIdToChatdlg.begin();ite!=m_mapIdToChatdlg.end();){
        ChatDialog *chat= *ite;
        if(chat) {
           chat->hide();
           delete chat;
           chat=NULL;
        }
     ite = m_mapIdToChatdlg.erase(ite);
  }
     //Exit the application
     exit(0);
}

//Handle adding friend requests
void CKernel::DealAddFriendRq(long ISendIp, char *buf, int nLen)
{
    qDebug()<<__func__;
    //unpacking
    STRU_TCP_ADD_FRIEND_RQ*rq = (STRU_TCP_ADD_FRIEND_RQ*)buf;
    STRU_TCP_ADD_FRIEND_RS rs;
    //A prompt window is displayed asking the user to agree or refuse to add a friend
    QString str = QString("【%1】Request to add you as a friend, do you agree or disagree？").arg(rq->userName);
    if(QMessageBox::Yes==QMessageBox::question(m_mainWnd,"提示",str)){
        rs.result = add_success;
    }else{
        rs.result = user_refuse;
    }
    //Send a reply to the server
    rs.friendId = m_id;
    rs.userId   = rq->userId;
    strcpy(rs.friendName,m_name.toStdString().c_str());
    m_tcpClient->SendData(0,(char*)&rs,sizeof(rs));
}

//Handle adding a friend reply
void CKernel::DealAddFriendRs(long ISendIp, char *buf, int nLen)
{
     qDebug()<<__func__;
     STRU_TCP_ADD_FRIEND_RS* rs = (STRU_TCP_ADD_FRIEND_RS*)buf;
     //1.1、User name transcoding
     QString friendName = Gb2312ToUtf8(rs->friendName);
     //2、According to the result information
     switch(rs->result){
     case no_this_user :
         QMessageBox::about(m_mainWnd,"prompt",QString("[%1]Failed to add a friend because the user does not exist").arg(friendName));
         break;
     case user_offline:
          QMessageBox::about(m_mainWnd,"prompt",QString("[%1]The user is offline and fails to add friends").arg(friendName));
         break;
     case user_refuse:
          QMessageBox::about(m_mainWnd,"prompt",QString("[%1]The user refuses to add a friend").arg(rs->friendName));
         break;
     case add_success:
          QMessageBox::about(m_mainWnd,"prompt",QString("[%1]Add a success").arg(rs->friendName));
         break;
     default:
         break;
     }
}

void CKernel::slot_CloseQQ()
{
    qDebug()<<__func__;
    STRU_TCP_OFFLINE_RQ rq;
    rq.userId = m_id;
    m_tcpClient->SendData(0,(char*)&rq,sizeof(rq));
    slot_CloseLogin();
}

void CKernel::DealOfflineRq(long ISendIp, char *buf, int nLen)
{
     qDebug()<<__func__;
     //unpacking
     STRU_TCP_OFFLINE_RQ* rq = (STRU_TCP_OFFLINE_RQ*)buf;
     //Obtain the id of the offline friend and obtain the useritrm of the offline friend
     if(m_mapIdToUseritem.count(rq->userId) > 0) {
           //Delete the profile picture of your offline friend
         Useritem* item = m_mapIdToUseritem[rq->userId];
         item->setoffline();
     }
}
