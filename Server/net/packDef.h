#pragma once
#include <vcruntime_string.h>
#define _DEF_UDP_PORT         (54321) 
#define _DEF_UDP_RECVBUF_LEN  (1024) 
#define _DEF_TCP_PORT         (12345) 
#define _DEF_TCP_SERVER_IP    ("172.27.48.1")

#define _DEF_NAME_SIZE      (100)
#define _DEF_MAX_SIZE       (4096)

//The array size
#define _DEF_PROTOCAL_COUNT (10)

//Head agreement
#define _DEF_PROTOCAL_BASE  (1000)

//registered 
#define _DEF_PACK_TCP_REGISTER_RQ     (_DEF_PROTOCAL_BASE +1) 
#define _DEF_PACK_TCP_REGISTER_RS     (_DEF_PROTOCAL_BASE +2) 

//login
#define _DEF_PACK_TCP_LOGIN_RQ        (_DEF_PROTOCAL_BASE +3) 
#define _DEF_PACK_TCP_LOGIN_RS        (_DEF_PROTOCAL_BASE +4) 

//Get Friends Information
#define _DEF_PACK_TCP_FRIEND_INFO     (_DEF_PROTOCAL_BASE +5) 

//Add buddy
#define _DEF_PACK_TCP_ADDFRIEND_RQ    (_DEF_PROTOCAL_BASE +6) 
#define _DEF_PACK_TCP_ADDFRIEND_RS    (_DEF_PROTOCAL_BASE +7) 

//chat
#define _DEF_PACK_TCP_CHAT_RQ         (_DEF_PROTOCAL_BASE +8) 
#define _DEF_PACK_TCP_CHAT_RS         (_DEF_PROTOCAL_BASE +9) 

//offline
#define _DEF_PACK_TCP_OFFLINE_RQ      (_DEF_PROTOCAL_BASE +10)

//Request the structure and return the result
//Registration Request Result
#define register_success (0)	
#define user_is_exist	 (1)	
#define name_is_used     (2)
#define parameter_error  (3)

//Login Request Result
#define login_success	 (0)	
#define user_not_exist	 (1)	
#define password_error	 (2)	

//User state
#define status_online	 (0)	
#define status_offline	 (1)	

//Result of adding a friend request
#define add_success	     (0)	
#define no_this_user	 (1)	
#define user_refuse	     (2)	
#define user_offline	 (3)	

//Chat Request Result
#define send_success	 (0)	
#define send_fail	     (1)

//TCP Protocol Structure
//Redefine the int type
typedef int PackType;

//Registration request: protocol header, nickname, phone number, password
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

//Registration Reply: Protocol header, registration result
typedef struct STRU_TCP_REGISTER_RS
{
	STRU_TCP_REGISTER_RS() :type(_DEF_PACK_TCP_REGISTER_RS), result(register_success){}
	PackType type;
	int result;
}STRU_TCP_REGISTER_RS;

//Login request: protocol header, mobile number, password
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

//Login reply: Protocol header, login result, user id
typedef struct STRU_TCP_LOGIN_RS
{
	STRU_TCP_LOGIN_RS() :type(_DEF_PACK_TCP_LOGIN_RS), result(login_success), userId(0){}
	PackType type;
    int result;
	int userId;
}STRU_TCP_LOGIN_RS;

//Get friend information: protocol header, user id, nickname, signature, profile picture id, user status
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

//Add friend request: protocol header, requested user id, requested user nickname, requested user nickname
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

//Add friend reply: Protocol header, requested user id, Requested user id, Requested user nickname, request result
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

// Chat request: Protocol header, user id, friend id, chat content
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

//Chat reply: Protocol header, user id, friend id, request result
typedef struct STRU_TCP_CHAT_RS
{
	STRU_TCP_CHAT_RS() :type(_DEF_PACK_TCP_CHAT_RS), userId(0), friendId(0), result(send_success){}
	PackType type;
	int userId;
	int friendId;
	int result;
}STRU_TCP_CHAT_RS;

// Offline request: protocol header, user id
typedef struct STRU_TCP_OFFLINE_RQ
{
	STRU_TCP_OFFLINE_RQ() :type(_DEF_PACK_TCP_OFFLINE_RQ), userId(0){}
	PackType type;
	int userId;
} STRU_TCP_OFFLINE_RQ;







