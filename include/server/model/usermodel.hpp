#ifndef USERMODEL_H
#define USERMODEL_H
#include"user.hpp"

class UserModel{
    public:
    bool insert(User &user);
    //g根据用户号码查询用户消息
    User query(int id);
    //更新用户的状态信息
    bool updateState(User user);

    //重置状态信息
    void resetState();

};
#endif 