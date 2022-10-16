//#include "stdafx.h"
#include "CMySql.h"
CMySql::CMySql(void)
{
    //Connect to the mysql server
    //mysql_close, this object is released
    m_sock = new MYSQL;
    mysql_init(m_sock);  
    mysql_set_character_set(m_sock, "gb2312"); 
}

CMySql::~CMySql(void)
{
    if(m_sock) {
        delete m_sock;
        m_sock = nullptr;
    }
}

void CMySql::DisConnect()
{
    mysql_close(m_sock);
}

bool CMySql::ConnectMySql(char *host, char *user, char *pass, char *db, short nport)
{
    if (!mysql_real_connect(m_sock, host, user, pass, db, nport, NULL, CLIENT_MULTI_STATEMENTS)) {
        //Connection error
        return false;
    }
    return true;
}

 bool  CMySql::GetTables(char* szSql, list<string>& lstStr)
 {
    if(mysql_query(m_sock, szSql)) {
        return false;
    }

    m_results = mysql_store_result(m_sock);
    if(NULL == m_results) {
        return false;
    }
    while ((m_record = mysql_fetch_row(m_results))) {
        lstStr.push_back(m_record[0]);
    }
    return true;
 }

bool CMySql::SelectMySql(char* szSql, int nColumn, list<string>& lstStr)
{
    //mysql_query() send and execute SQL statements to MySQL
    if(mysql_query(m_sock, szSql)) {
        return false;
    }
    m_results = mysql_store_result(m_sock);
    if(NULL == m_results)return false;
    //Iterate over the next row in the table, pulling out the contents into the m_record result set
    while ((m_record = mysql_fetch_row(m_results))) {
        
        for(int i = 0; i < nColumn; i++) {
            if(!m_record[i]) {
                lstStr.push_back("");
            } 
            else {
                lstStr.push_back(m_record[i]);
            }
        }
    }
    return true;
}

 bool  CMySql::UpdateMySql(char* szSql)
 {
    if(!szSql) {
        return false;
    }
    if(mysql_query(m_sock, szSql)) {
        return false;
    }
    return true;
 }


