/*
该函数为出库函数
与入库函数对应
实现了出库相关功能
同时预留了一些接口
*/

#include "Base.h"
Th* bound_head;
Th* bound_real;

//初始化出库函数
void init_bound(Th *h,Th *r)
{
	bound_head = h;
	bound_real = r;
}

//判断节点后继是否为空，主要拿来判断头节点
bool isNull(Th* h)
{
	if (h->next == NULL) {
		return true;
	}
	return false;
}

//判断头节点之后是否有元素，即判空函数
bool headEmpty()
{
	if (bound_head->next == NULL) {
		return true;
	}
	return false;
}

//内存申请且异常判断
inline Th* Out_get()
{
	//Th* t = (Th*)malloc(sizeof(Th));	//C语言申请内存方式
	Th* qw = new Th;	//C++申请内存方式，更加安全和稳定
	qw->next = NULL;
	if (qw == NULL) {
		cout << "内存申请失败" << "\n";
		exit(1);	//中断
	}
	return qw;
}

vector<Th*> AllInfo;	//可能需要作为全局变量来使用，但似乎也没有那么必要
//返回一个包含当前所有信息的结构体指针数组，基于vector，提供给上层函数使用
vector<Th*> getAllInfo()
{
	AllInfo.clear();	//每次使用之前要clear掉vector，否则会积累值
	Th* t;
	if (isNull(bound_head)) {
		cout << "当前没有任何信息" << endl;
		exit(1);	//中断
	}
	t = bound_head;
	while (t->next != NULL) {
		t = t->next;
		AllInfo.push_back(t);	//结构体指针存入向量栈区，注意解引用
	}
	return AllInfo;
}

//得到耗材结构体链表的头(第一个被插入的信息)
Th* getHead()
{
	return bound_head;
}

//得到耗材结构体链表的尾(最后一个被插入的信息)
Th* getReal()
{
	return bound_real;
}

//搜索，按照id的方式查找一个耗材信息的前一个节点的信息(为了方便删除信息)
Th* search_Info(const string& id_key)	//接受一个引用值以节省一点内存
{
	if (isNull(bound_head)) {
		cout << "当前没有任何信息" << endl;
		exit(1);	//中断
	}
	Th* key = bound_head;
	while (key->next->id!=id_key) {	//
		if (key->next == NULL) {
			//cout << "没有找到id为" <<id_key<<"的耗材" << endl;
			break;
		}
		key = key->next;
	}
	return key;
}

//出库(删除一个指定的耗材) 返回bool 底层为搜索函数
//接受耗材的id值
bool Out_bound(const string& id_key)
{
	if (isNull(bound_head)) {
		cout << "当前没有任何信息" << endl;
		return false;
	}
	//O(1)方式出库
	Th* t = search_Info(id_key);	//得到前置节点
	Th* p = t->next;		//保存待删除节点，一会释放内存
	t->next = t->next->next;	//孤立待删除节点
	delete(p);	//释放内存
	return true;
}

//删除所有的耗材信息 返回一个bool 全部删除成功返回true 
bool del_All()
{
	if (isNull(bound_head)) {
		cout << "当前没有任何信息，无需删除" << endl;
		exit(1);	//中断
	}
	Th* p = bound_head;
	Th* t;
	while (p->next!=NULL) {
		//特判
		if (p->next->next == NULL) {	//只有一个耗材时特殊处理
			t = p->next;
			p->next = NULL;
			delete(t);
			break;		//结束之后直接退出循环即可
		}
		t = p->next;
		p->next = p->next->next;
		delete(t);
	}
	return true;
}

//一个接口，基于覆盖写入文件的方式，达到清空文件中存的数据信息
//接受一个文件名
bool delFileAll(const string& filename)
{
	ofstream delAll(filename, std::ios::out);

	// 检查文件是否成功打开
	if (!delAll.is_open()) {
		cerr << "无法打开文件: " << filename << endl;
		exit(1);	//中断
	}
	delAll.seekp(0);	// 将文件流位置定位到文件的开始处
	
	delAll << '\0';	// 覆盖写入一个空字符，清空文件内容
	
	delAll.close();	// 关闭文件流
}

//根据耗材名查找所有的同名耗材，存放在一个结构体数组返回
//直接套用vector
vector<Th*> AllName;
vector<Th*> searchAllName(const string& nam)
{
	//还是遍历链表查询，查到就push_back进vector
	//按入库顺序
	if (isNull(bound_head)) {
		cout << "当前没有任何信息" << endl;
		exit(1);	//中断
	}

	Th* p = bound_head;
	while (p->next!=NULL) {
		p = p->next;	//先进行这一步，因为p指向头节点
		if (p->name == nam) {
			AllName.push_back(p);	//相等就放入vector
		}
	}
	return AllName;
}

//根据耗材入库用户查找该用户的所有耗材，存放在一个结构体数组返回
//直接套用vector
vector<Th*> AllUser;
vector<Th*> searchAllUser(const string& use)
{
	if (isNull(bound_head)) {
		cout << "当前没有任何信息" << endl;
		exit(1);	//中断
	}

	//和上面的实现基本差不多
	Th* p = bound_head;
	while (p->next != NULL) {
		p = p->next;
		if (p->uesr == use) {
			AllUser.push_back(p);
		}
	}
	return AllUser;
}


//是接口也是底层
//接受一个结构体指针，将结构体指针转换为一个string
string ThToString(Th *p)
{
	string Info;
	Info = p->id + "," + p->name + "," + p->In_date + "," + p->Out_date + "," + p->uesr + "," + to_string(p->MAX_K);
	return Info;
}