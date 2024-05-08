/*
	该函数为入库函数
	实现了：
	耗材入库
	同时预留了一些接口
	底层采用链表实现
*/

/*
	需要注意，调用这个库内的函数，需要自行封装一个指针域为NULL的耗材结构体
*/
#include "Base.h"
Th* head;
Th* real;
//初始化函数
void init(Th* h,Th* r)	
{
	head = h;
	real = r;
}

//底层函数，申请一个耗材结构体空间并返回对应指针，减少代码量
inline Th* Cons_get()
{
	//Th* t = (Th*)malloc(sizeof(Th));	//C语言申请内存方式
	Th* qw = new Th;	//C++申请内存方式，更加安全和稳定
	qw->next = NULL;
	qw->MAX_K = 114514;	//设置默认值
	if (qw == NULL) {
		cout << "内存申请失败" << "\n";
		exit(1);	//中断
	}
	return qw;
}

//底层函数，得到当前函数的尾指针
Th* get_Real()
{
	return real;
}

//底层函数，实现在尾指针处O(1)插入数据
void insert_Real(Th* p)
{
	real->next = p;	//添加元素至尾指针
	//cout << real->next->uesr << " " << head->next->uesr << endl;	//?抽象bug
	//思考了几秒，大概知道原因了，首先，我因为Base.h和Put_in_s.h两个之间的重定义问题而采取了static来解决重定义问题
	//但是，这样之后，原来重复定义的东西，变成了两组不同的东西，是完全并不一样的东西，也就是说，在某种程度下
	//它们两个变成了局部变量，执行完Get_in_file()这个之后，修改的是这个函数域内的值，然后进入到了Main当中
	//又切换到了新的head和real了，所以真正被修改的是Get_in_file()域内的head和real，所以才会报错
	
	real = p;	//debug之后发现的，只需要让尾指针指向当前插入的元素即可
	//real=p->next;		//更新尾指针指向最后一个元素
	real->next = NULL;	//保证最后一个元素值为NULL
}

//底层函数 耗材入库
bool Put_in_cin(Th *p)	//接受一个Th类型的结构体，返回值类型为布尔类型，返回入库成功与失败，数据来源用户录入
{
	Th* node = Cons_get();	//调用底层函数
	node = p;	//将获取到的结构体指针给予申请的node指针
	//申请成功将得到的耗材结构体装入链表当中
	if (head->next == NULL) {	//如果此时的头结构体之后没有信息
		head->next = node;
		real = head->next;	//更新尾指针指向最后一个元素
	}
	else {	//如果有则遍历直到没有的情况
		Th* q = head->next;	//头里面不存放东西，只用头节点内的指针域
		while (q->next!=NULL) {
			q = q->next;
		}
		q->next = node;
		real = q->next;	//更新尾指针指向最后一个元素
	}
	return true;	//完成插入，返回true
}



//底层函数 保存信息到文件当中 这里预设的文件名为Cons.data
bool Save(const string& filename)	//接受文件名，将现在内存当中的整个链表存入文件当中
{
	
	ofstream outf(filename, std::ios::trunc);	//写入方式为覆盖方式打开文件
	//ofstream outf(filename);		//覆盖写入
	if (!outf.is_open()) {	//异常检测
		std::cerr << "无法打开文件:"<<filename<<"以进行写入" << std::endl;
		exit(1);	//中断
	}
	Th* t=head->next;
	//异常处理
	if (t == NULL) {	//如果没有任何信息可以写到链表当中
		cout << "无内容保存" << endl;	//
		return false;
	}
	
	while (t!=NULL) {
		outf << t->id << ","		//写入每一个结构体中的数据，数据之间以逗号隔开，一个耗材一行数据
			<< t->name << ","
			<< t->In_date << ","
			<< t->Out_date << ","
			<< t->uesr << ","
			<<t->MAX_K<< endl;
		t = t->next;
	}
	outf.close();	//全部存入后关闭文件读取
	return true;		//完成保存，返回true
}

//为Get_in_file服务的底层
//实现了将文件中的一行信息解析成一个耗材结构体
inline Th* P_S(const string& line)
{
	Th* t = Cons_get();	//直接调用底层函数
	istringstream iss(line);
	string ids;
	std::getline(iss, ids, ',');
	t->id = ids;
	//此处可以优化成循环
	string names;
	std::getline(iss, names, ',');
	t->name = names;

	string In_dates;
	std::getline(iss, In_dates, ',');
	t->In_date = In_dates;

	string Out_dates;
	std::getline(iss, Out_dates, ',');
	t->Out_date = Out_dates;

	string uesrs;
	std::getline(iss, uesrs, ',');
	t->uesr = uesrs;

	string KC;
	std::getline(iss, KC, '\n');
	t->MAX_K = (ll)stoi(KC);	//强转对齐一下
	return t;
}

//接口1
//从文件中读取数据构成链表
void Get_in_file(const string& filename)	//接受一个文件名，打开一个文件，读取文件内的内容构造链表，提供给初始化等函数使用
{
	ifstream Infile(filename);
	if (!Infile.is_open()) {
		std::cerr << "无法读取文件:" << filename << std::endl;
		exit(1);
	}
	Th* q;
	string line_data;	//值为每一行的数据
	while (getline(Infile, line_data)) {	//按行读取数据
		q=P_S(line_data);	//按逗号分割字符串得到耗材结构体
		//将得到的指针添加进链表当中,这里调用尾指针插入函数
		insert_Real(q);		//插入的节点从head开始
	}
	Infile.close();
}


//接口2，接受一个string，分析成一个Th结构体返回
Th* stringToTh(const string& str)
{
	return P_S(str);
}



//计算总库存 会被多次调用
ll getALLKC()
{
	Th* p = head;
	ll KC=0;
	while (p->next != NULL) {
		KC++;
		p = p->next;
	}
	return KC;
}