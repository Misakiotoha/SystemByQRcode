/*
该函数为报表以及统计函数
可以对库存的物品进行统计以及生成相关报告
*/
#include "Base.h"
#include "Inventory_management.h"
#include "Out_bound.h"
#include "Put_in_s.h"

//自定义比较函数
inline bool compareById(const Th* a, const Th* b)
{
	return a->id < b->id;
}

//打印报表基函数
inline void PrintRep(vector<Th*> data)
{
	cout << "id" << " " << "name" << " " << "In_date" << " " << "Out_date" << " " << "user" << " " << "MAX_KC" << endl;
	for (auto k : data)
	{
		cout << k->id << " " << k->name << " " << k->In_date << " " << k->Out_date << " " << k->uesr << " " << k->MAX_K << endl;
	}
}

//打印库存报表 
void PrintAll()
{
	PrintRep(getAllInfo());	//使用底层函数得到此时所有的信息
}

//排序打印报表 根据耗材id排序打印
void SortPrintAll()
{
	vector<Th*> T = getAllInfo();
	sort(T.begin(), T.end(), compareById);
	PrintRep(T);
}

//指定耗材名打印报表 自动按id来排序输出
void PrintForName(const string& name)
{
	vector<Th*> T = getNames(name);
	sort(T.begin(), T.end(), compareById);
	PrintRep(T);
}

//指定耗材入库用户打印报表 自动按id来排序输出
void PrintForUser(const string& user)
{
	vector<Th*> T = getUsers(user);
	sort(T.begin(), T.end(), compareById);
	PrintRep(T);
}