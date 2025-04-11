#include"usermodel.hpp"
#include"db.h"
#include<iostream>
using namespace std;

bool UserModel::insert(User &user)
{
    //组装sql语句
    char sql[1024]={0};
    sprintf(sql,"INSERT INTO user(name,password,state) VALUES('%s','%s','%s')",
        user.getName().c_str(),user.getPwd().c_str(),user.getState().c_str());
    MySQL mysql;
    if(mysql.connect())
    {
        if(mysql.update(sql))
        {
            //获取插入成功的用户数据生成的主键id
            user.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }   

    return false;
}
//根据用户号查询用户信息
User UserModel::query(int id)
{
    char sql[1024]={0};
    sprintf(sql,"SELECT * FROM user WHERE id = %d",id);
    MySQL mysql;
    if(mysql.connect())
    {
        MYSQL_RES* res=mysql.query(sql);
        if(res!=nullptr)
        {
            MYSQL_ROW row=mysql_fetch_row(res);
            if(row!=nullptr)
            {
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setPwd(row[2]);
                user.setState(row[3]);
                mysql_free_result(res);
                return user;
            }

        }
    }   
    return User();
}

bool UserModel::updateState(User user)
{
    char sql[1024]={0};
    sprintf(sql,"UPDATE user SET state='%s' WHERE id=%d",user.getState().c_str(),user.getId());
    MySQL mysql;
    if(mysql.connect())
    {
        if(mysql.update(sql))
        {
            return true;
        }
    }   

    return false;
}


void UserModel::resetState()
{
    char sql[1024]="UPDATE user SET state='offline' WHERE state=online";

    MySQL mysql;
    if(mysql.connect())
    {
        mysql.update(sql);
    }   
}
