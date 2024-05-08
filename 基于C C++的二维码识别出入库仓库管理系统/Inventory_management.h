#pragma once
#include "Base.h"

//接受一个long long的值，设置库存总预警值，成功返回true
bool setKC(ll k);

//查找函数，可以按id(只返回唯一的指针),原来是返回的是前一个节点的指针，在这里改成了返回指定的指针
Th* getId(const string& ids);

//查找函数，可以按耗材名字(返回所有同名的数组指针)
vector<Th*> getNames(const string& nam);

//查找函数，可以按耗材入库用户(返回所有同用户名的数组指针)
vector<Th*> getUsers(const string& use);

//计算当前库存总值	会放在初始化函数当中
void setAllKC();

//得到当前的库存总值
ll getAllKC();

//遍历当前的链表来得到一个键值对的表，值为商品名字对数量
//会被多次调用
//生成报表也会调用这个函数
map<string, ll> getNameToValue();

//遍历链表得到一个键值对的表，值为耗材名字对最大容量，也就是预警值了
map<string, ll> getNameToMax();

//得到预警值名值对
map<string, ll> getExceededWarningMap();

//得到名对超出警戒值多少
map<string, ll> getExceededWarningMapx();

//下限预警，默认设置为每一个耗材5个为下限
// 下限预警函数
map<string, ll> getRestockWarning();