#pragma once
#include "Base.h"

//�Զ����ݺ��� ÿ����������һ������
//����ֵΪbool�����Զ����ݳɹ��򷵻�bool
//���������ļ�����ǰ�������Ҫ���ݵ��ļ�����һ���Ǳ����ļ���
bool AutoBackup(const string& BeforeName, const string& AfterName);

//�ֶ����� �û����о����Ƿ񱸷�
//��AutoBackup���������ڣ�AutoBackup�ᱻ����init()��ʼ����������
bool ByUserBackup(const string& BeforeName, const string& AfterName);