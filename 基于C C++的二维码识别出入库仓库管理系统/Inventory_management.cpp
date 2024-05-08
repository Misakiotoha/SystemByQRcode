/*
该函数为库存管理函数
实现了查找，排序等功能
同时预留了一些接口
主要是去调用的底层的出库入库已经实现的功能
这里只是为了方便上层统一调用
*/
#include "Base.h"
#include "Out_bound.h"
#include "Put_in_s.h"


//库存预警值，可以通过接口自行设定
ll MAX_KC = 0;

//库存总值
ll ALL_KC = 114514;

//接受一个long long的值，设置库存总预警值，成功返回true
bool setKC(ll k)
{
	MAX_KC = k;
	return true;
}

//查找函数，可以按id(只返回唯一的指针),原来是返回的是前一个节点的指针，在这里改成了返回指定的指针
Th* getId(const string& ids)
{
	Th* p = search_Info(ids);
	if (p->next == NULL) {
		//没找到的情况
		exit(1);
	}
	//找到的情况
	p = p->next;
	return p;
}

//查找函数，可以按耗材名字(返回所有同名的数组指针)
vector<Th*> getNames(const string& nam)
{
	return searchAllName(nam);
}

//查找函数，可以按耗材入库用户(返回所有同用户名的数组指针)
vector<Th*> getUsers(const string& use)
{
	return searchAllUser(use);
}

//计算当前库存总值	会放在初始化函数当中
void setAllKC()
{
	ALL_KC = getALLKC();
}

//得到当前的库存总值
ll getAllKC()
{
	return ALL_KC;
}

//遍历当前的链表来得到一个键值对的表，值为耗材名字对数量
//会被多次调用
//生成报表也会调用这个函数
map<string, ll> NameToValue;
map<string, ll> getNameToValue()
{
	if (headEmpty()) {	//如果没有元素，则不生成
		cout << "没有任何数据" << endl;
		exit(1);
	}
	NameToValue.clear();
	//如果有则生成
	//使用下层函数getAllInfo来获得一个存放此时刻所有信息的vector，注意只是此时刻
	vector<Th*> T = getAllInfo();
	//遍历这个vector，压入map当中
	for (auto k : T)	//auto，C++特有，自动识别后面的T的类型
	{
		NameToValue[k->name]++;
	}
	return NameToValue;
}

//直接用上面的
map<string, ll> NameToMax;
//遍历链表得到一个键值对的表，值为耗材名字对最大容量，也就是预警值了
map<string, ll> getNameToMax()
{
	if (headEmpty()) {	//如果没有元素，则不生成
		cout << "没有任何数据" << endl;
		exit(1);
	}
	NameToMax.clear();
	//如果有则生成
	//使用下层函数getAllInfo来获得一个存放此时刻所有信息的vector，注意只是此时刻
	vector<Th*> T = getAllInfo();
	for (auto k : T)	//auto，C++特有，自动识别后面的T的类型
	{
		NameToMax[k->name] = k->MAX_K;		//随着读取，名字相同，但是预警值不同，认为是主动被设置的，进而更新这个值
	}
	return NameToMax;
}

map<string, ll> exceededWarnings;
// 预警值筛选函数
map<string, ll> getExceededWarningMap() 
{
	exceededWarnings.clear();
	NameToMax.clear();
	NameToValue.clear();

	// 获取当前所有耗材的使用情况
	NameToValue = getNameToValue();
	// 获取当前所有耗材的预警值
	NameToMax = getNameToMax();

	// 遍历耗材使用情况 
	for (const auto& pair : NameToValue) {
		string name = pair.first;
		ll Ovalue = pair.second;

		// 检查是否存在对应的预警值
		if (NameToMax.find(name) != NameToMax.end()) {
			ll k = NameToMax[name];

			// 如果当前数量超过预警值，则记录为预警事件
			if (Ovalue > k) {
				exceededWarnings[name] = k;
			}
		}
	}

	return exceededWarnings;
}

// 获取超过警戒值的耗材及其超过的数量的map
map<string, ll> getExceededWarningMapx() 
{
	exceededWarnings.clear();
	map<string, ll> nameToValue;
	nameToValue.clear();
	// 获取所有耗材的名称和数量
	nameToValue = getNameToValue();
	// 获取所有耗材的名称和预警值
	map<string, ll> nameToMax;
	nameToMax.clear();
	nameToMax = getNameToMax();

	// 遍历所有耗材
	for (const auto& entry : nameToValue) {
		string name = entry.first;
		ll ov = entry.second;

		// 查找耗材的预警值
		auto maxIt = nameToMax.find(name);
		if (maxIt != nameToMax.end()) {
			ll k = maxIt->second;

			// 如果当前数量超过预警值，计算超过的数量
			if (ov > k) {
				ll bv = ov - k;
				exceededWarnings[name] = bv;
			}
		}
	}

	return exceededWarnings;
}


//下限预警，默认设置为每一个耗材5个为下限
// 下限预警函数
map<string, ll> getRestockWarning() 
{
	map<string, ll> NameToValue = getNameToValue(); // 获取当前耗材数量的映射
	map<string, ll> NameToMax = getNameToMax(); // 获取耗材最大容量的映射
	map<string, ll> restockNeeded; // 需要补货的映射

	ll restockThreshold = 5; // 设置下限预警值

	for (const auto& valuePair : NameToValue) {
		string name = valuePair.first;
		ll currentCount = valuePair.second;

		// 检查 NameToMax 中是否存在对应的条目
		auto maxIt = NameToMax.find(name);
		if (maxIt != NameToMax.end()) {
			ll maxCount = maxIt->second;

			// 如果当前数量小于 restockThreshold，则计算缺少的数量
			if (currentCount < restockThreshold) {
				ll shortage = restockThreshold - currentCount; // 缺少的数量
				restockNeeded[name] = shortage;
			}
		}
		else {
			// 如果 NameToMax 中不存在该耗材，则不进行预警，或者根据需要处理
			restockNeeded[name] = currentCount; // 可以选择将当前数量作为缺少的数量
		}
	}

	return restockNeeded;
}