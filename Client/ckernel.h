#ifndef CKERNEL_H
#define CKERNEL_H
#include<QMap>
#include"packDef.h"
#include <QObject>
#include"qqdialog.h"
#include"useritem.h"
#include"chatdialog.h"
#include"logindialog.h"
#include"INetMediator.h"
//Defining function Pointers
class CKernel;
typedef void (CKernel::*PFUN)(long ISendIp, char* buf, int nLen);
class CKernel : public QObject
{
    Q_OBJECT
public:
    explicit CKernel(QObject *parent = 0);
    ~CKernel();
    //QString(uft8)->char*(gb312)
    static void Utf8ToGb2312(char* gbBuf,int nLen,QString uft8);
    //char* gb2312->QString uft8
    static QString Gb2312ToUtf8(char* gbBuf);
    //RegisterRs
    void dealRegisterRs(long ISendIp, char* buf, int nLen);
    //LoginRs
    void dealLoginRs(long ISendIp, char* buf, int nLen);
    //FriendInfoRq
    void dealFriendInfoRq(long ISendIp, char* buf, int nLen);
    //ChatRs
    void DealChatRs(long ISendIp, char* buf, int nLen);
    //ChatRq
    void DealChatRq(long ISendIp, char* buf, int nLen);
    //AddFriendRq
    void DealAddFriendRq(long ISendIp, char* buf, int nLen);
    //AddFriendRs
    void DealAddFriendRs(long ISendIp, char* buf, int nLen);
    //OfflineRq
    void DealOfflineRq(long ISendIp, char *buf, int nLen);
public slots:
    //Process all data received
    void slot_ReadyData(long ISendIp, char* buf, int nLen);
    //Processing Registration information
    void slot_RegisterCommit(QString name, QString tel, QString password);
    //Processing Login Information
    void slot_LoginCommit(QString tel,QString password);
    //Handles the signal of clicking on a friend's profile picture
    void slot_userItemClicked(int userId);
    //Handle the chat content to be sent
    void slot_sendChatMsg(QString content,int id);
    //Handle user requests to add friends
    void slot_AddFriend();
    //Signal to close the processing interface
    void slot_CloseLogin();
    //Handles the signal to close the friend list interface
    void slot_CloseQQ();
private:
    int m_id;
    //Current user nickname
    QString m_name;
    //Define a window pointer
    LoginDialog* m_pLoginDlg;
    QQDialog* m_mainWnd;
    INetMediator* m_tcpClient;
    //Initializes protocol mapping table, private function
    void setProtocalMp();
    //Protocol mapping table data
    PFUN m_netProtocalMap[_DEF_PROTOCAL_COUNT];
    //Save the mapping between id and userItem
    QMap<int,Useritem*> m_mapIdToUseritem;
    //Save the id and the corresponding user's chat window
    QMap<int, ChatDialog*>m_mapIdToChatdlg;
};
#endif // CKERNEL_H
