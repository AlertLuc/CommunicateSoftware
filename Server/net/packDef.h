#pragma once
#include <vcruntime_string.h>
#define _DEF_UDP_PORT         (54321) 
#define _DEF_UDP_RECVBUF_LEN  (1024) 
#define _DEF_TCP_PORT         (12345) 
#define _DEF_TCP_SERVER_IP    ("192.168.0.105")

#define _DEF_NAME_SIZE      (100)
#define _DEF_MAX_SIZE       (4096)

//�����С
#define _DEF_PROTOCAL_COUNT (10)

// Э��ͷ
#define _DEF_PROTOCAL_BASE  (1000)

// ע��
#define _DEF_PACK_TCP_REGISTER_RQ     (_DEF_PROTOCAL_BASE +1) 
#define _DEF_PACK_TCP_REGISTER_RS     (_DEF_PROTOCAL_BASE +2) 

//��¼
#define _DEF_PACK_TCP_LOGIN_RQ        (_DEF_PROTOCAL_BASE +3) 
#define _DEF_PACK_TCP_LOGIN_RS        (_DEF_PROTOCAL_BASE +4) 

// ��ȡ������Ϣ
#define _DEF_PACK_TCP_FRIEND_INFO     (_DEF_PROTOCAL_BASE +5) 

// ��Ӻ���
#define _DEF_PACK_TCP_ADDFRIEND_RQ    (_DEF_PROTOCAL_BASE +6) 
#define _DEF_PACK_TCP_ADDFRIEND_RS    (_DEF_PROTOCAL_BASE +7) 

//����
#define _DEF_PACK_TCP_CHAT_RQ         (_DEF_PROTOCAL_BASE +8) 
#define _DEF_PACK_TCP_CHAT_RS         (_DEF_PROTOCAL_BASE +9) 

//����
#define _DEF_PACK_TCP_OFFLINE_RQ      (_DEF_PROTOCAL_BASE +10)

//Request the structure and return the result
//Registration Request Result
#define register_success (0)	
#define user_is_exist	 (1)	
#define name_is_used     (2)
#define parameter_error  (3)


// ����ṹ�����ؽ��
// ע��������
#define login_success	 (0)	
#define user_not_exist	 (1)	
#define password_error	 (2)	

// �û�״̬
#define status_online	 (0)	
#define status_offline	 (1)	

// ��Ӻ���������
#define add_success	     (0)	
#define no_this_user	 (1)	
#define user_refuse	     (2)	
#define user_offline	 (3)	

// ����������
#define send_success	 (0)	
#define send_fail	     (1)

//TCPЭ��ṹ
//�ض���int����
typedef int PackType;

// ע������:Э��ͷ���ǳơ��ֻ��š�����
typedef struct STRU_TCP_REGISTER_RQ
{
	STRU_TCP_REGISTER_RQ() :type(_DEF_PACK_TCP_REGISTER_RQ)
	{
		memset(name, 0, _DEF_NAME_SIZE);
		memset(tel, 0, _DEF_NAME_SIZE);
		memset(password, 0, _DEF_NAME_SIZE);
	}
	PackType type;
	char name[_DEF_NAME_SIZE];
	char tel[_DEF_NAME_SIZE];
	char password[_DEF_NAME_SIZE];
}STRU_TCP_REGISTER_RQ;

// ע��ظ�:Э��ͷ��ע����
typedef struct STRU_TCP_REGISTER_RS
{
	STRU_TCP_REGISTER_RS() :type(_DEF_PACK_TCP_REGISTER_RS), result(register_success){}
	PackType type;
	int result;
}STRU_TCP_REGISTER_RS;

// ��¼����:Э��ͷ���ֻ��š����� 
typedef struct STRU_TCP_LOGIN_RQ
{
	STRU_TCP_LOGIN_RQ() : type(_DEF_PACK_TCP_LOGIN_RQ)
	{
		memset(tel, 0, _DEF_NAME_SIZE);
		memset(password, 0, _DEF_NAME_SIZE);
	}
	PackType type;
	char tel[_DEF_NAME_SIZE];
	char password[_DEF_NAME_SIZE];
}STRU_TCP_LOGIN_RQ;

// ��¼�ظ�:Э��ͷ����¼������û�id
typedef struct STRU_TCP_LOGIN_RS
{
	STRU_TCP_LOGIN_RS() :type(_DEF_PACK_TCP_LOGIN_RS), result(login_success), userId(0){}
	PackType type;
    int result;
	int userId;
}STRU_TCP_LOGIN_RS;

// ��ȡ������Ϣ:Э��ͷ���û�id���ǳơ�ǩ����ͷ��id���û�״̬ 
typedef struct STRU_TCP_FRIEND_INFO
{
	STRU_TCP_FRIEND_INFO() :type(_DEF_PACK_TCP_FRIEND_INFO), userId(0), iconId(0), state(status_online)
	{
		memset(name, 0, _DEF_NAME_SIZE);
		memset(feeling, 0, _DEF_NAME_SIZE);
	}
	PackType type;
	int userId;
	int iconId;
	int state;
	char name[_DEF_NAME_SIZE];
	char feeling[_DEF_NAME_SIZE];
}STRU_TCP_FRIEND_INFO;

// ��Ӻ�������:Э��ͷ�������û�id�������û��ǳơ��������û��ǳ� 
typedef struct STRU_TCP_ADD_FRIEND_RQ
{
	STRU_TCP_ADD_FRIEND_RQ() :type(_DEF_PACK_TCP_ADDFRIEND_RQ), userId(0)
	{
		memset(userName, 0, _DEF_NAME_SIZE);
		memset(friendName, 0, _DEF_NAME_SIZE);
	}
	PackType type;
	int userId;
	char userName[_DEF_NAME_SIZE];
	char friendName[_DEF_NAME_SIZE];

}STRU_TCP_ADD_FRIEND_RQ;

// ��Ӻ��ѻظ�:Э��ͷ�������û�id���������û�id���������û��ǳơ�������
typedef struct STRU_TCP_ADD_FRIEND_RS
{
	STRU_TCP_ADD_FRIEND_RS() :type(_DEF_PACK_TCP_ADDFRIEND_RS), userId(0), friendId(0), result(add_success)
	{
		memset(friendName, 0, _DEF_NAME_SIZE);
	}
	PackType type;
	int userId;//user1
	int friendId;//user2
	int result;
	char friendName[_DEF_NAME_SIZE];
}STRU_TCP_ADD_FRIEND_RS;

// ��������:Э��ͷ���û�id������id���������� 
typedef struct STRU_TCP_CHAT_RQ
{
	STRU_TCP_CHAT_RQ() : type(_DEF_PACK_TCP_CHAT_RQ), userId(0), friendId(0)
	{
		memset(content, 0, _DEF_MAX_SIZE);
	}
	PackType type;
	int userId;
	int friendId;
	char content[_DEF_MAX_SIZE];
}STRU_TCP_CHAT_RQ;

// ����ظ�:Э��ͷ���û�id������id�������� 
typedef struct STRU_TCP_CHAT_RS
{
	STRU_TCP_CHAT_RS() :type(_DEF_PACK_TCP_CHAT_RS), userId(0), friendId(0), result(send_success){}
	PackType type;
	int userId;
	int friendId;
	int result;
}STRU_TCP_CHAT_RS;

// ��������:Э��ͷ���û�id
typedef struct STRU_TCP_OFFLINE_RQ
{
	STRU_TCP_OFFLINE_RQ() :type(_DEF_PACK_TCP_OFFLINE_RQ), userId(0){}
	PackType type;
	int userId;
} STRU_TCP_OFFLINE_RQ;







