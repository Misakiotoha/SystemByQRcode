#pragma once


int getUser_State();


//登录界面
//接受账户密码两个变量
int login(const string& user, const string& passwd);



void passwd_cre();

void passwd_ans();

//登出函数
int login_out();