#pragma once
#include"INetMediator.h"
#include"CMySql.h"
#include"packDef.h"
#include"map"
class CKernel;
typedef void (CKernel::* pfun)(long ISendIp, char* buf, int nLen);
class CKernel
{
public:
	CKernel(void);
	~CKernel(void);
	//打开服务器
	bool startServer();
	//关闭服务器
	void closeServer();
	//把数据从中介者类传递到核心处理类
	//处理所有接收到的数据
	void dealData(long ISendIp, char* buf, int nLen);
	//处理注册请求
	void dealRegisterRq(long ISendIp, char* buf, int nLen);
	//处理登录请求
	void dealLoginRq(long ISendIp, char* buf, int nLen);
	void dealChatRq(long ISendIp, char* buf, int nLen);
	void dealAddFriendRq(long ISendIp, char* buf, int nLen);
	void dealAddFriendRs(long ISendIp, char* buf, int nLen);
	void dealOfflioneRq(long ISendIp, char* buf, int nLen);
	//初始化协议映射表
	void set_protocol_map();
	void getUserFriendInfo(int userId);
	void getUserInfoById(STRU_TCP_FRIEND_INFO* info, int id);

public:
	//静态成员指针
	static CKernel* p_kernel;

private:
	//数据库对象和中介者对象
	INetMediator* m_pServer;
	CMySql sql;
	//协议映射表数据，协议头->函数地址
	pfun m_netProtocalMap[_DEF_PROTOCAL_COUNT]{};
	map<int, SOCKET> m_mapIdToSocket;
};

