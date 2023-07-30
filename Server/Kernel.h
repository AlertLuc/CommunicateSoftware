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
	//�򿪷�����
	bool startServer();
	//�رշ�����
	void closeServer();
	//�����ݴ��н����ഫ�ݵ����Ĵ�����
	//�������н��յ�������
	void dealData(long ISendIp, char* buf, int nLen);
	//����ע������
	void dealRegisterRq(long ISendIp, char* buf, int nLen);
	//�����¼����
	void dealLoginRq(long ISendIp, char* buf, int nLen);
	void dealChatRq(long ISendIp, char* buf, int nLen);
	void dealAddFriendRq(long ISendIp, char* buf, int nLen);
	void dealAddFriendRs(long ISendIp, char* buf, int nLen);
	void dealOfflioneRq(long ISendIp, char* buf, int nLen);
	//��ʼ��Э��ӳ���
	void set_protocol_map();
	void getUserFriendInfo(int userId);
	void getUserInfoById(STRU_TCP_FRIEND_INFO* info, int id);

public:
	//��̬��Աָ��
	static CKernel* p_kernel;

private:
	//���ݿ������н��߶���
	INetMediator* m_pServer;
	CMySql sql;
	//Э��ӳ������ݣ�Э��ͷ->������ַ
	pfun m_netProtocalMap[_DEF_PROTOCAL_COUNT]{};
	map<int, SOCKET> m_mapIdToSocket;
};

