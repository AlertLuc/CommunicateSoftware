#pragma once
#include <vcruntime_string.h>
#define _DEF_UDP_PORT         (54321) 
#define _DEF_UDP_RECVBUF_LEN  (1024) 
#define _DEF_TCP_PORT         (12345) 
#define _DEF_TCP_SERVER_IP    ("192.168.0.105")

#define _DEF_NAME_SIZE      (100)
#define _DEF_MAX_SIZE       (4096)

//数组大小
#define _DEF_PROTOCAL_COUNT (10)

// 协议头
#define _DEF_PROTOCAL_BASE  (1000)

// 注册
#define _DEF_PACK_TCP_REGISTER_RQ     (_DEF_PROTOCAL_BASE +1) 
#define _DEF_PACK_TCP_REGISTER_RS     (_DEF_PROTOCAL_BASE +2) 

//登录
#define _DEF_PACK_TCP_LOGIN_RQ        (_DEF_PROTOCAL_BASE +3) 
#define _DEF_PACK_TCP_LOGIN_RS        (_DEF_PROTOCAL_BASE +4) 

// 获取好友信息
#define _DEF_PACK_TCP_FRIEND_INFO     (_DEF_PROTOCAL_BASE +5) 

// 添加好友
#define _DEF_PACK_TCP_ADDFRIEND_RQ    (_DEF_PROTOCAL_BASE +6) 
#define _DEF_PACK_TCP_ADDFRIEND_RS    (_DEF_PROTOCAL_BASE +7) 

//聊天
#define _DEF_PACK_TCP_CHAT_RQ         (_DEF_PROTOCAL_BASE +8) 
#define _DEF_PACK_TCP_CHAT_RS         (_DEF_PROTOCAL_BASE +9) 

//下线
#define _DEF_PACK_TCP_OFFLINE_RQ      (_DEF_PROTOCAL_BASE +10)

//Request the structure and return the result
//Registration Request Result
#define register_success (0)	
#define user_is_exist	 (1)	
#define name_is_used     (2)
#define parameter_error  (3)


// 请求结构，返回结果
// 注册请求结果
#define login_success	 (0)	
#define user_not_exist	 (1)	
#define password_error	 (2)	

// 用户状态
#define status_online	 (0)	
#define status_offline	 (1)	

// 添加好友请求结果
#define add_success	     (0)	
#define no_this_user	 (1)	
#define user_refuse	     (2)	
#define user_offline	 (3)	

// 聊天请求结果
#define send_success	 (0)	
#define send_fail	     (1)

//TCP协议结构
//重定义int类型
typedef int PackType;

// 注册请求:协议头、昵称、手机号、密码
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

// 注册回复:协议头、注册结果
typedef struct STRU_TCP_REGISTER_RS
{
	STRU_TCP_REGISTER_RS() :type(_DEF_PACK_TCP_REGISTER_RS), result(register_success){}
	PackType type;
	int result;
}STRU_TCP_REGISTER_RS;

// 登录请求:协议头、手机号、密码 
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

// 登录回复:协议头、登录结果、用户id
typedef struct STRU_TCP_LOGIN_RS
{
	STRU_TCP_LOGIN_RS() :type(_DEF_PACK_TCP_LOGIN_RS), result(login_success), userId(0){}
	PackType type;
    int result;
	int userId;
}STRU_TCP_LOGIN_RS;

// 获取好友信息:协议头、用户id、昵称、签名、头像id、用户状态 
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

// 添加好友请求:协议头、请求用户id、请求用户昵称、被请求用户昵称 
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

// 添加好友回复:协议头、请求用户id、被请求用户id、被请求用户昵称、请求结果
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

// 聊天请求:协议头、用户id、好友id、聊天内容 
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

// 聊天回复:协议头、用户id、好友id、请求结果 
typedef struct STRU_TCP_CHAT_RS
{
	STRU_TCP_CHAT_RS() :type(_DEF_PACK_TCP_CHAT_RS), userId(0), friendId(0), result(send_success){}
	PackType type;
	int userId;
	int friendId;
	int result;
}STRU_TCP_CHAT_RS;

// 下线请求:协议头、用户id
typedef struct STRU_TCP_OFFLINE_RQ
{
	STRU_TCP_OFFLINE_RQ() :type(_DEF_PACK_TCP_OFFLINE_RQ), userId(0){}
	PackType type;
	int userId;
} STRU_TCP_OFFLINE_RQ;







