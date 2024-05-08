#pragma once

//初始化函数 接受一个头节点引用和尾指针
void init(Th* h, Th* r);

//底层函数，申请一个耗材结构体空间并返回对应指针，减少代码量
//因为只在函数内部调用，所以使用inline牺牲一点点内存来加速
inline Th* Cons_get();

//接口1
//从文件中读取数据构成链表
void Get_in_file(const string& filename);

//底层函数，得到当前函数的尾指针
Th* get_Real();

//底层函数，实现在尾指针处O(1)插入数据
void insert_Real(Th* p);

//底层函数 耗材入库
bool Put_in_cin(Th* p);

//底层函数 保存信息到文件当中 这里预设的文件名为Cons.data
bool Save(const string& filename);

//为Get_in_file服务的底层
//实现了将文件中的一行信息解析成一个耗材结构体
inline Th* P_S(const string& line);

//接口2，接受一个string，分析成一个Th结构体返回
Th* stringToTh(const string& str);

//计算总库存 会被多次调用，用inline加速
//
ll getALLKC();