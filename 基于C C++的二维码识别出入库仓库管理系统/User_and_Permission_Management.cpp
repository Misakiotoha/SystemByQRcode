/*
该函数为用户权限管理函数
实现了用户登录，权限设置等等函数
可自行设置管理员密码以及设置管理员账户
采用异或加密方式
管理员账户和普通用户所使用不同的文件来载入，从而区别所拥有的权限
*/
#include "Base.h"

//全局的静态变量，用户状态变量，-1表示未登录，0表示管理员，1表示普通用户
static int User_State=-1;


int getUser_State()
{
    return User_State;
}

// 账户文件名
const std::string ADMIN_FILE = "admin.txt";
const std::string USER_FILE = "user.txt";

// 异或加密函数
std::string XOREncrypt(const std::string& input, char key) {
    std::string output;
    for (char c : input) {
        output += (c ^ key); // 对每个字符进行异或操作
    }
    return output;
}

// 异或解密函数
std::string XORDecrypt(const std::string& input, char key) {
    return XOREncrypt(input, key); // 解密过程与加密过程相同
}

//构造加密后的管理员密码 163
void passwd_cre()
{
    
    string passwd = "114514";
    cout << XOREncrypt(passwd, 163) << endl;;
}

//解密密码  163
void passwd_ans()
{
    string passwd = "拻棖挆";
    cout << XORDecrypt(passwd, 163) << endl;;
}

vector <string> Users;
//登录界面
//接受账户密码两个变量
int login(const string& user,const string& passwd)
{
    ifstream adm(ADMIN_FILE);  //打开管理员账户文件
    string line;

    ifstream user1(USER_FILE);   //打开普通用户账户文件
    string line1;
    //清空vector
    Users.clear();
    //按行读入入栈
    while (getline(adm, line)) {
        Users.push_back(line);
    }
    if (user == Users[0] && passwd == Users[1]) {
        User_State = 0;
        return 0;       //登录的是管理员账户
    }
    
    //清空vector
    Users.clear();
    while (getline(user1, line)) {
        Users.push_back(line);
    }
    for (ll i = 0; i < Users.size(); i++)
    {
        if (Users[i] == user && Users[i + 1] == passwd) {
            User_State = 1;
            return 1;
            if (i == Users.size() - 1) {    //防止vector越界
                return -1;
            }
        }
    }

    adm.close();
    user1.close();

    //登录失败返回-1
    return -1;
}

//登出函数 调用这个函数则切换当前用户状态
int login_out()
{
    User_State = -1;
    return -1;
}