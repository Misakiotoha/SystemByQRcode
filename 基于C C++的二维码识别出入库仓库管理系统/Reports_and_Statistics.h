#pragma once
#include "Base.h"

//�Զ���ȽϺ���
inline bool compareById(const Th* a, const Th* b);

//��ӡ���������
inline void PrintRep(vector<Th*> data);

//��ӡ��汨�� 
void PrintAll();

//�����ӡ���� ���ݺĲ�id�����ӡ
void SortPrintAll();

//ָ���Ĳ�����ӡ���� �Զ���id���������
void PrintForName(const string& name);

//ָ���Ĳ�����û���ӡ���� �Զ���id���������
void PrintForUser(const string& user);