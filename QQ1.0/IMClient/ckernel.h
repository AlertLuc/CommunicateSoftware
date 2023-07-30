#ifndef CKERNEL_H
#define CKERNEL_H
#include"packDef.h"
#include <QObject>
#include"mychatdialog.h"
#include"INetMediator.h"
#include"logindialog.h"
#include"QMap"
#include"useritem.h"
#include"chatdialog.h"
//定义函数指针
class CKernel;
typedef void (CKernel::*PFUN)(long ISendIp, char* buf, int nLen);
class CKernel : public QObject
{
    Q_OBJECT
public:
    explicit CKernel(QObject *parent = 0);
    ~CKernel();
    //utf8(QString)->gb2312(char*)
    static void utf8ToGb2312(char* gbBuf,int nLen,QString &utf8);
    //gb2312->utf8
    static QString gb2312ToUtf8(char*gbBuf);
    //初始化协议映射表
    void setProtocalMp();
    //处理注册回复
    void dealRegisterRs(long ISendIp, char* buf, int nLen);
    //处理登录回复
    void dealLoginRs(long ISendIp, char* buf, int nLen);
    //处理好友信息请求
    void dealFriendInfoRq(long ISendIp, char* buf, int nLen);
    //处理聊天请求
    void dealChatRq(long ISendIp, char* buf, int nLen);
    //处理聊天回复
    void dealChatRs(long ISendIp, char* buf, int nLen);
    //处理添加好友请求
    void dealAddFriendRq(long ISendIp, char* buf, int nLen);
    //处理添加好友回复
     void dealAddFriendRs(long ISendIp, char* buf, int nLen);
     //处理下线请求
     void dealOfflineRq(long ISendIp, char* buf, int nLen);
signals:

public slots:
    // 处理接收到的所有数据
    void slot_ReadyData(long ISendIp, char* buf, int nLen);
    //处理注册请求信号
    void slot_RegisterCommit(QString name,QString tel,QString password);
    //处理登录请求信号
    void slot_LoginCommit(QString tel,QString password);
    //处理聊天信息信号
    void slot_sendChatMsg(int id,QString content);
    //处理用户点击好友头像的信号
    void slot_userItemClicked(int id);
    //处理添加好友信号
    void slot_addFriend();
    //处理关闭登录和注册页面的信号
    void slot_close();
    //处理关闭好友列表页面的信号
    void slot_offline();
private:
    int m_id;
    QString m_name;
    MyChatDialog* m_mainWnd;
    INetMediator* m_tcpClient;
    LoginDialog* m_loginDlg;
    //协议映射表数据，协议头->函数地址
    PFUN m_netProtocalMap[_DEF_PROTOCAL_COUNT];
    //保存id和userItem的映射关系
    QMap<int,UserItem*> m_mapIdToUserItem;
    //保存id和聊天窗口的映射联系
    QMap<int,ChatDialog*>m_mapIdToChatdlg;
};
#endif // CKERNEL_H
