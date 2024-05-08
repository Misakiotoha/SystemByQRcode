#pragma once
#include "Base.h"

//��ʼ�����⺯��
void init_bound(Th* h, Th* r);

//�жϽڵ����Ƿ�Ϊ�գ���Ҫ�����ж�ͷ�ڵ�
bool isNull(Th* h);

//�ڴ��������쳣�ж�
inline Th* Out_get();

//����һ��������ǰ������Ϣ�Ľṹ��ָ�����飬����vector���ṩ���ϲ㺯��ʹ��
vector<Th*> getAllInfo();

//ɾ�����еĺĲ���Ϣ ����һ��bool ȫ��ɾ���ɹ�����true 
bool del_All();

//�õ��ĲĽṹ�������ͷ(��һ�����������Ϣ)
Th* getHead();

//�õ��ĲĽṹ�������β(���һ�����������Ϣ)
Th* getReal();

//һ���ӿڣ����ڸ���д���ļ��ķ�ʽ���ﵽ����ļ��д��������Ϣ
//����һ���ļ���
bool delFileAll(const string& filename);

//����������id�ķ�ʽ����һ���Ĳ���Ϣ��ǰһ���ڵ����Ϣ(Ϊ�˷���ɾ����Ϣ)
Th* search_Info(const string& id_key);

//����(ɾ��һ��ָ���ĺĲ�) ����bool �ײ�Ϊ��������
//���ܺĲĵ�idֵ
bool Out_bound(const string& id_key);

//���ݺĲ����������е�ͬ���Ĳģ������һ���ṹ�����鷵��
//ֱ������vector inline����
vector<Th*> searchAllName(const string& nam);

//���ݺĲ�����û����Ҹ��û������кĲģ������һ���ṹ�����鷵��
//ֱ������vector inline����
vector<Th*> searchAllUser(const string& use);

//�ж�ͷ�ڵ�֮���Ƿ���Ԫ�أ����пպ���
bool headEmpty();

//�ǽӿ�Ҳ�ǵײ�
//����һ���ṹ��ָ�룬���ṹ��ָ��ת��Ϊһ��string
string ThToString(Th* p);