#pragma once
#include "Base.h"

//自定义比较函数
inline bool compareById(const Th* a, const Th* b);

//打印报表基函数
inline void PrintRep(vector<Th*> data);

//打印库存报表 
void PrintAll();

//排序打印报表 根据耗材id排序打印
void SortPrintAll();

//指定耗材名打印报表 自动按id来排序输出
void PrintForName(const string& name);

//指定耗材入库用户打印报表 自动按id来排序输出
void PrintForUser(const string& user);