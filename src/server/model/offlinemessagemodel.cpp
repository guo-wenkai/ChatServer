#include"offlinemessagemodel.hpp"
#include"db.h"
//存储用户离线消息
void  OfflineMsgModel::insert(int userid,string msg)
{
    char sql[1024]={0};
    sprintf(sql,"INSERT INTO offlinemessage VALUES('%d','%s')",userid,msg.c_str());
    MySQL mysql;
    if(mysql.connect())
    {
        if(mysql.update(sql))
        {
            mysql.update(sql);
        }
    }   
}
//删除用户的离线消息
void OfflineMsgModel::remove(int userid)
{
    char sql[1024]={0};
    sprintf(sql,"DELETE FROM offlinemessage WHERE userid=%d",userid);
    MySQL mysql;
    if(mysql.connect())
    {
        if(mysql.update(sql))
        {
            mysql.update(sql);
        }
    }   
}
//查询用户的离线消息
vector<string> OfflineMsgModel::query(int userid)
{
    char sql[1024]={0};
    sprintf(sql,"SELECT * FROM offlinemessage WHERE userid = %d",userid);
    vector<string> vec;
    MySQL mysql;
    if(mysql.connect())
    {
        MYSQL_RES* res=mysql.query(sql);
        if(res!=nullptr)
        {
            MYSQL_ROW row;
            while((row=mysql_fetch_row(res))!=nullptr)
            {
                vec.push_back(row[0]);
            }
            mysql_free_result(res);
        }
    }   
    return vec;
}