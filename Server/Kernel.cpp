#include "Kernel.h"
#include"TcpServerMediator.h"
using namespace std;
#define NET_PACK_MAP(a) m_netProtocalMap[a-_DEF_PROTOCAL_BASE-1]
//调用核心处理类函数，在中介者类中，通过核心处理类的静态  // NOLINT(clang-diagnostic-invalid-utf8)
CKernel* CKernel::p_kernel = nullptr;

CKernel::CKernel(void)
{
    m_pServer= new TcpServerMediator;
	//静态成员指针在类外初始化，在构造函数里赋值this  // NOLINT(clang-diagnostic-invalid-utf8)
	p_kernel = this;
	//初始化数组，调用  // NOLINT(clang-diagnostic-invalid-utf8)
	set_protocol_map();
}

//Initialize the protocol mapping table
void CKernel::set_protocol_map()
{
	cout << "CKernel::setProto-calMp" << endl;
	//1、初始化  // NOLINT(clang-diagnostic-invalid-utf8)
	memset(m_netProtocalMap, 0, _DEF_PROTOCAL_COUNT);  // NOLINT(clang-diagnostic-invalid-utf8)
	//2、绑定协议头和处理函数  // NOLINT(clang-diagnostic-invalid-utf8)
	NET_PACK_MAP(_DEF_PACK_TCP_REGISTER_RQ)  = &CKernel::dealRegisterRq;
	NET_PACK_MAP(_DEF_PACK_TCP_LOGIN_RQ)     = &CKernel::dealLoginRq;
	NET_PACK_MAP(_DEF_PACK_TCP_CHAT_RQ)      = &CKernel::dealChatRq;
	NET_PACK_MAP(_DEF_PACK_TCP_ADDFRIEND_RQ) = &CKernel::dealAddFriendRq;
	NET_PACK_MAP(_DEF_PACK_TCP_ADDFRIEND_RS) = &CKernel::dealAddFriendRs;
	NET_PACK_MAP(_DEF_PACK_TCP_OFFLINE_RQ)   = &CKernel::dealOfflioneRq;
}

CKernel::~CKernel()
{
	closeServer();
}

//Opening the Server
bool CKernel::startServer()
{
	//Open the network,new a server mediator object, and open the network
	m_pServer = new TcpServerMediator;
	if (!m_pServer->OpenNet()){
		cout << "Failed to open the network." << endl;
		return false;
	}
	//Connecting to the database
	if (!sql.ConnectMySql("127.0.0.1", "root", "123456", "communication_schema")){
		cout << "Failed to connect to the database" << endl;
		return false;
	}
	return true;
}

//Shutting down the Server
void CKernel::closeServer()
{
	//Other resources are reclaimed and disconnected from the database
	sql.DisConnect();
	//Shut down the network
	if (m_pServer){
		m_pServer->CloseNet();
		delete m_pServer;
		m_pServer = NULL;
	}
}

//Processing received data: Print the received data first
void CKernel::dealData(long ISendIp, char* buf, int nLen)
{
	cout<< "Kernel::dealData" <<buf<< endl;
	//Take out the protocol header mapping protocol relationship
	PackType type = *(PackType*)buf;
	//The corresponding handler in the array is computed from the protocol header
	if (type >= _DEF_PROTOCAL_BASE + 1 && type <= _DEF_PROTOCAL_BASE + 1 + _DEF_PROTOCAL_COUNT) {
		//Computes the array subscript and retrieves any function Pointers present in the subscript
		pfun pf = NET_PACK_MAP(type);
		//If the pointer exists, the pointer point function is called, corresponding to the handler function
		if (pf) {
			(this->*pf)(ISendIp, buf, nLen);
		}
	}
	//处理完处理，回收空间
	delete[] buf;
}


void CKernel::dealRegisterRq(long ISendIp, char* buf, int nLen)
{
	cout << "CKernel::dealRegisterRq" << endl;
	STRU_TCP_REGISTER_RQ* rq = (STRU_TCP_REGISTER_RQ*)buf;
	cout << "tel:" << rq->tel << endl;
	cout << "name:" << rq->name << endl;
	cout << "password:" << rq->password <<endl;

	list<string>listRest;
	char sqlBuf[1024] = "";
	sprintf(sqlBuf, "select tel from t_user where tel = '%s';", rq->tel);
	if (!sql.SelectMySql(sqlBuf, 1, listRest)) {
		cout << "The user socket does not exist，sql:" << sqlBuf << endl;
		return;
	}

	STRU_TCP_REGISTER_RS rs;
	if (listRest.size() > 0) {
		rs.result = user_is_exist;
	}
	else {
		sprintf(sqlBuf, "select name from t_user where name = '%s';", rq->name);
		if (!sql.SelectMySql(sqlBuf, 1, listRest)) {
			cout << "The user socket does not exist" << sqlBuf << endl;
			return;
		}

		if (listRest.size() > 0) {

			rs.result = user_is_exist;
		}
		else {
			sprintf(sqlBuf, "insert into t_user (tel,password,name,icon,feeling) values ('%s','%s','%s',1,'123');", rq->tel, rq->password, rq->name);
			if (!sql.UpdateMySql(sqlBuf)) {
				cout << "The user socket does not exist" << sqlBuf << endl;
				return;
			}
			rs.result = register_success;
		}
	}
	
	m_pServer->SendData(ISendIp, (char*)&rs, sizeof(rs));
}


void CKernel::dealLoginRq(long ISendIp, char* buf, int nLen)
{
	cout << "CKernel::dealLoginRq" << endl;
	STRU_TCP_LOGIN_RQ* rq = (STRU_TCP_LOGIN_RQ*)buf;
	cout << "tel:" << rq->tel << endl;
	cout << "password:" << rq->password << endl;

	STRU_TCP_LOGIN_RS rs;

	list<string>listRest;
	char sqlBuf[1024] = "";
	sprintf(sqlBuf, "select id,password from t_user where tel = '%s';", rq->tel);
	if (!sql.SelectMySql(sqlBuf, 2, listRest)) {
		cout << "The user socket does not exist，sql:" << sqlBuf << endl;
		return;
	}
	if (0 == listRest.size()) {
		rs.result = user_not_exist;
	}
	else {
        int userId = atoi(listRest.front().c_str());
		listRest.pop_front();
        string password = listRest.front();
		listRest.pop_front();

		if (strcmp(rq->password, password.c_str()) != 0) {
			rs.result = password_error;
		}
		else {
			rs.result = login_success;
			rs.userId = userId;

			m_pServer->SendData(ISendIp, (char*)&rs, sizeof(rs));

			m_mapIdToSocket[userId] = ISendIp;

			getUserFriendInfo(userId);
			return;
		}
	}

	m_pServer->SendData(ISendIp, (char*)&rs, sizeof(rs));
}

void CKernel::getUserFriendInfo(int userId)
{
	STRU_TCP_FRIEND_INFO userInfo;

	getUserInfoById(&userInfo, userId);

	if (m_mapIdToSocket.find(userId) == m_mapIdToSocket.end())
	{
		cout << "The user socket does not exist" << endl;
		return;
	}
	m_pServer->SendData(m_mapIdToSocket[userId], (char*)&userInfo, sizeof(userInfo));

	list<string> listRest;
	char sqlBuf[1024] = "";
	sprintf(sqlBuf, "select idB from t_friend where idA = '%d';", userId);
	if (!sql.SelectMySql(sqlBuf, 1, listRest)) {
		cout << "Failed to query the database.，sql:" << sqlBuf << endl;
		return;
	}

	int friendId = 0;

	STRU_TCP_FRIEND_INFO friendInfo;

	while (listRest.size() > 0) {
		friendId = atoi(listRest.front().c_str());
		listRest.pop_front();
		getUserInfoById(&friendInfo, friendId);
		m_pServer->SendData(m_mapIdToSocket[userId], (char*)&friendInfo, sizeof(friendInfo));
	}
	if (m_mapIdToSocket.find(friendId) != m_mapIdToSocket.end()) {
		m_pServer->SendData(m_mapIdToSocket[friendId], (char*)&userInfo, sizeof(userInfo));
	}
}

void CKernel::getUserInfoById(STRU_TCP_FRIEND_INFO* info, int id)
{
    info->userId = id;
	list<string> listRest;
	char sqlBuf[1024] = "";
	sprintf(sqlBuf, "select name, feeling, icon from t_user where id = '%d';", id);
	if (!sql.SelectMySql(sqlBuf, 3, listRest)) {
		cout << "Failed to query the database.，sql:" << sqlBuf << endl;
		return;
	}
	if (listRest.size() > 0) {
		strcpy(info->name, listRest.front().c_str());
		listRest.pop_front();

		strcpy(info->feeling, listRest.front().c_str());
		listRest.pop_front();

		info->iconId = atoi(listRest.front().c_str());
		listRest.pop_front();
	}

	if (m_mapIdToSocket.count(id) > 0) {
		info->state = status_online;
	}
	else {
		info->state = status_offline;
	}
}

void CKernel ::dealChatRq(long ISendIp, char* buf, int nLen)
{
	cout << "CKernel::dealChatRq" << endl;
	STRU_TCP_CHAT_RQ* rq = (STRU_TCP_CHAT_RQ*)buf;

	if (m_mapIdToSocket.count(rq->friendId) > 0) {
		m_pServer->SendData(m_mapIdToSocket[rq->friendId], buf, nLen);
	}
	else {
		STRU_TCP_CHAT_RS rs;
		rs.friendId = rq->friendId;
		rs.userId = rq->userId;
		rs.result = send_fail;
		m_pServer->SendData(ISendIp, (char*)&rs, sizeof(rs));
	}
}

void CKernel::dealAddFriendRq(long ISendIp, char* buf, int nLen)
{
	cout << "dealAddFrienfRq" << endl;
	STRU_TCP_ADD_FRIEND_RQ* rq = (STRU_TCP_ADD_FRIEND_RQ*)buf;
	list<string>resultList;
	char sqlBuf[1024] = " ";
	sprintf(sqlBuf, "select id from t_user where name = '%s';", rq->friendName);
	if (!sql.SelectMySql(sqlBuf, 1, resultList)) {
		cout << "Failed to query the database." << endl;
		return;
	}
	STRU_TCP_ADD_FRIEND_RS rs;
	int friendId = 0;
	if (0 == resultList.size()) {
		rs.result = no_this_user;
		strcpy(rs.friendName, rq->friendName);
		rs.userId = rq->userId;
		m_pServer->SendData(ISendIp, (char*)&rs, sizeof(rs));
	}
	else {
		friendId = atoi(resultList.front().c_str());
		resultList.pop_front();
		if (m_mapIdToSocket.count(friendId) == 0) {
			rs.friendId = friendId;
			strcpy(rs.friendName, rq->friendName);
			rs.userId = rq->userId;
			rs.result = user_offline;
			m_pServer->SendData(ISendIp, (char*)&rs, sizeof(rs));
		}
		else {
			m_pServer->SendData(m_mapIdToSocket[friendId], buf, nLen);
		}
	}
}

void CKernel::dealAddFriendRs(long ISendIp, char* buf, int nLen)
{
	cout << "dealAddFrienfRs" << endl;
	STRU_TCP_ADD_FRIEND_RS* rs = (STRU_TCP_ADD_FRIEND_RS*)buf;
	if (add_success == rs->result) {
		//The transaction
		char sqlBuf[1024] = "";
		sprintf(sqlBuf, "insert into t_friend values('%d','%d')", rs->friendId, rs->userId);
		if (!sql.UpdateMySql(sqlBuf)) {
			cout << "Failed to update database" << sqlBuf << endl;
		}
		sprintf(sqlBuf, "insert into t_friend values('%d','%d')", rs->userId, rs->friendId);
		if (!sql.UpdateMySql(sqlBuf)) {
			cout << "Failed to update database" << sqlBuf << endl;
		}
		//Update your Friend List
		getUserFriendInfo(rs->userId);
	}
	//Send the result to the client
	if (m_mapIdToSocket.count(rs->friendId) > 0) {
		m_pServer->SendData(m_mapIdToSocket[rs->friendId], buf, nLen);
	}
}

void  CKernel::dealOfflioneRq(long ISendIp, char* buf, int nLen)
{
	cout << "dealOfflioneRq" << endl;
	//unpacking
	auto* rq = reinterpret_cast<STRU_TCP_OFFLINE_RQ*>(buf);
	//Query the user's friend list based on the user id
	list<string>resultList;
	char sqlBuf[1024] = " ";
	sprintf(sqlBuf, "select idB from t_friend where idA = '%d';", rq->userId);
	if (!sql.SelectMySql(sqlBuf, 1, resultList)) {
		cout << "Failed to query the database." << endl;
	}
	int friendId = 0;
	//Iterate over the query results
	while (!resultList.empty()) {
		//Get the socket of each friend
		friendId = atoi(resultList.front().c_str());
		resultList.pop_front();
		//The socket of each friend was obtained based on the friend id. Procedure
		if (m_mapIdToSocket.count(friendId) > 0) {
			//Forward the offline notification to each of your friends
			m_pServer->SendData(m_mapIdToSocket[friendId], buf, nLen);
		}
	}
	//Delete the user's socket from the map
	if (m_mapIdToSocket.count(rq->userId) > 0) {
		closesocket(m_mapIdToSocket[rq->userId]);
		m_mapIdToSocket.erase(rq->userId);
	}
}

