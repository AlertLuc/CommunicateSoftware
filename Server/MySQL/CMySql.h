#pragma once
#include <mysql.h>
#include<sstream>
#include<string>
#pragma comment(lib,"libmysql.lib")
#include <list>
using namespace std;
class CMySql
{
public:
    CMySql(void);
    ~CMySql(void);
public:                    //ip,Username, password, database, port number
    bool  ConnectMySql(char *host,char *user,char *pass,char *db,short nport = 3306);
    void  DisConnect();
    bool  SelectMySql(char* szSql,int nColumn,list<string>& lstStr);
    //Get the tables in the database
    bool GetTables(char* szSql,list<string>& lstStr);
    //Update: Delete, insert, modify
    bool  UpdateMySql(char* szSql);
private:
    MYSQL *m_sock;   
    MYSQL_RES *m_results{};   
    MYSQL_ROW m_record{};    
};

