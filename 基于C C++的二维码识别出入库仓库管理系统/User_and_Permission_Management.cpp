/*
�ú���Ϊ�û�Ȩ�޹�����
ʵ�����û���¼��Ȩ�����õȵȺ���
���������ù���Ա�����Լ����ù���Ա�˻�
���������ܷ�ʽ
����Ա�˻�����ͨ�û���ʹ�ò�ͬ���ļ������룬�Ӷ�������ӵ�е�Ȩ��
*/
#include "Base.h"

//ȫ�ֵľ�̬�������û�״̬������-1��ʾδ��¼��0��ʾ����Ա��1��ʾ��ͨ�û�
static int User_State=-1;


int getUser_State()
{
    return User_State;
}

// �˻��ļ���
const std::string ADMIN_FILE = "admin.txt";
const std::string USER_FILE = "user.txt";

// �����ܺ���
std::string XOREncrypt(const std::string& input, char key) {
    std::string output;
    for (char c : input) {
        output += (c ^ key); // ��ÿ���ַ�����������
    }
    return output;
}

// �����ܺ���
std::string XORDecrypt(const std::string& input, char key) {
    return XOREncrypt(input, key); // ���ܹ�������ܹ�����ͬ
}

//������ܺ�Ĺ���Ա���� 163
void passwd_cre()
{
    
    string passwd = "114514";
    cout << XOREncrypt(passwd, 163) << endl;;
}

//��������  163
void passwd_ans()
{
    string passwd = "������";
    cout << XORDecrypt(passwd, 163) << endl;;
}

vector <string> Users;
//��¼����
//�����˻�������������
int login(const string& user,const string& passwd)
{
    ifstream adm(ADMIN_FILE);  //�򿪹���Ա�˻��ļ�
    string line;

    ifstream user1(USER_FILE);   //����ͨ�û��˻��ļ�
    string line1;
    //���vector
    Users.clear();
    //���ж�����ջ
    while (getline(adm, line)) {
        Users.push_back(line);
    }
    if (user == Users[0] && passwd == Users[1]) {
        User_State = 0;
        return 0;       //��¼���ǹ���Ա�˻�
    }
    
    //���vector
    Users.clear();
    while (getline(user1, line)) {
        Users.push_back(line);
    }
    for (ll i = 0; i < Users.size(); i++)
    {
        if (Users[i] == user && Users[i + 1] == passwd) {
            User_State = 1;
            return 1;
            if (i == Users.size() - 1) {    //��ֹvectorԽ��
                return -1;
            }
        }
    }

    adm.close();
    user1.close();

    //��¼ʧ�ܷ���-1
    return -1;
}

//�ǳ����� ��������������л���ǰ�û�״̬
int login_out()
{
    User_State = -1;
    return -1;
}