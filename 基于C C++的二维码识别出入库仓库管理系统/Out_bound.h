#pragma once
#include "Base.h"

//初始化出库函数
void init_bound(Th* h, Th* r);

//判断节点后继是否为空，主要拿来判断头节点
bool isNull(Th* h);

//内存申请且异常判断
inline Th* Out_get();

//返回一个包含当前所有信息的结构体指针数组，基于vector，提供给上层函数使用
vector<Th*> getAllInfo();

//删除所有的耗材信息 返回一个bool 全部删除成功返回true 
bool del_All();

//得到耗材结构体链表的头(第一个被插入的信息)
Th* getHead();

//得到耗材结构体链表的尾(最后一个被插入的信息)
Th* getReal();

//一个接口，基于覆盖写入文件的方式，达到清空文件中存的数据信息
//接受一个文件名
bool delFileAll(const string& filename);

//搜索，按照id的方式查找一个耗材信息的前一个节点的信息(为了方便删除信息)
Th* search_Info(const string& id_key);

//出库(删除一个指定的耗材) 返回bool 底层为搜索函数
//接受耗材的id值
bool Out_bound(const string& id_key);

//根据耗材名查找所有的同名耗材，存放在一个结构体数组返回
//直接套用vector inline加速
vector<Th*> searchAllName(const string& nam);

//根据耗材入库用户查找该用户的所有耗材，存放在一个结构体数组返回
//直接套用vector inline加速
vector<Th*> searchAllUser(const string& use);

//判断头节点之后是否有元素，即判空函数
bool headEmpty();

//是接口也是底层
//接受一个结构体指针，将结构体指针转换为一个string
string ThToString(Th* p);