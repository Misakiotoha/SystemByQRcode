#pragma once
#include "Base.h"

//����һ��long long��ֵ�����ÿ����Ԥ��ֵ���ɹ�����true
bool setKC(ll k);

//���Һ��������԰�id(ֻ����Ψһ��ָ��),ԭ���Ƿ��ص���ǰһ���ڵ��ָ�룬������ĳ��˷���ָ����ָ��
Th* getId(const string& ids);

//���Һ��������԰��Ĳ�����(��������ͬ��������ָ��)
vector<Th*> getNames(const string& nam);

//���Һ��������԰��Ĳ�����û�(��������ͬ�û���������ָ��)
vector<Th*> getUsers(const string& use);

//���㵱ǰ�����ֵ	����ڳ�ʼ����������
void setAllKC();

//�õ���ǰ�Ŀ����ֵ
ll getAllKC();

//������ǰ���������õ�һ����ֵ�Եı�ֵΪ��Ʒ���ֶ�����
//�ᱻ��ε���
//���ɱ���Ҳ������������
map<string, ll> getNameToValue();

//��������õ�һ����ֵ�Եı�ֵΪ�Ĳ����ֶ����������Ҳ����Ԥ��ֵ��
map<string, ll> getNameToMax();

//�õ�Ԥ��ֵ��ֵ��
map<string, ll> getExceededWarningMap();

//�õ����Գ�������ֵ����
map<string, ll> getExceededWarningMapx();

//����Ԥ����Ĭ������Ϊÿһ���Ĳ�5��Ϊ����
// ����Ԥ������
map<string, ll> getRestockWarning();