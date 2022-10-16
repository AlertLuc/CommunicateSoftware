#pragma once
#include"INetMediator.h"
#include"CMySql.h"
#include"packDef.h"
#include"map"
class CKernel;
typedef void (CKernel::* PFUN)(long ISendIp, char* buf, int nLen);
class CKernel
{
public:
	CKernel(void);
	~CKernel(void);
	bool startServer();
	void closeServer();
	//Pass the data from the broker class to the core processing class to process all the data received
	void dealData(long ISendIp, char* buf, int nLen);
	void dealRegisterRq(long ISendIp, char* buf, int nLen);
	void dealLoginRq(long ISendIp, char* buf, int nLen);
	void dealChatRq(long ISendIp, char* buf, int nLen);
	void dealAddFriendRq(long ISendIp, char* buf, int nLen);
	void dealAddFriendRs(long ISendIp, char* buf, int nLen);
	void dealOfflioneRq(long ISendIp, char* buf, int nLen);
	//Initialize the protocol mapping table
	void setProtocalMp();
	void getUserFriendInfo(int userId);
	void getUserInfoById(STRU_TCP_FRIEND_INFO* info, int id);

public:
	//Static member pointer
	static CKernel* pKernel;

private:
	//Database objects and mediator objects
	INetMediator* m_pServer;
	CMySql sql;
	//Protocol mapping table data
	PFUN m_netProtocalMap[_DEF_PROTOCAL_COUNT];
	map<int, SOCKET> m_mapIdToSocket;
};

