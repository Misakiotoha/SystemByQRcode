/*
�ú���Ϊ�����Լ�ͳ�ƺ���
���ԶԿ�����Ʒ����ͳ���Լ�������ر���
*/
#include "Base.h"
#include "Inventory_management.h"
#include "Out_bound.h"
#include "Put_in_s.h"

//�Զ���ȽϺ���
inline bool compareById(const Th* a, const Th* b)
{
	return a->id < b->id;
}

//��ӡ���������
inline void PrintRep(vector<Th*> data)
{
	cout << "id" << " " << "name" << " " << "In_date" << " " << "Out_date" << " " << "user" << " " << "MAX_KC" << endl;
	for (auto k : data)
	{
		cout << k->id << " " << k->name << " " << k->In_date << " " << k->Out_date << " " << k->uesr << " " << k->MAX_K << endl;
	}
}

//��ӡ��汨�� 
void PrintAll()
{
	PrintRep(getAllInfo());	//ʹ�õײ㺯���õ���ʱ���е���Ϣ
}

//�����ӡ���� ���ݺĲ�id�����ӡ
void SortPrintAll()
{
	vector<Th*> T = getAllInfo();
	sort(T.begin(), T.end(), compareById);
	PrintRep(T);
}

//ָ���Ĳ�����ӡ���� �Զ���id���������
void PrintForName(const string& name)
{
	vector<Th*> T = getNames(name);
	sort(T.begin(), T.end(), compareById);
	PrintRep(T);
}

//ָ���Ĳ�����û���ӡ���� �Զ���id���������
void PrintForUser(const string& user)
{
	vector<Th*> T = getUsers(user);
	sort(T.begin(), T.end(), compareById);
	PrintRep(T);
}