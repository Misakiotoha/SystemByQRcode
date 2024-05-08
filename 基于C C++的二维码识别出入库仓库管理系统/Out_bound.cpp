/*
�ú���Ϊ���⺯��
����⺯����Ӧ
ʵ���˳�����ع���
ͬʱԤ����һЩ�ӿ�
*/

#include "Base.h"
Th* bound_head;
Th* bound_real;

//��ʼ�����⺯��
void init_bound(Th *h,Th *r)
{
	bound_head = h;
	bound_real = r;
}

//�жϽڵ����Ƿ�Ϊ�գ���Ҫ�����ж�ͷ�ڵ�
bool isNull(Th* h)
{
	if (h->next == NULL) {
		return true;
	}
	return false;
}

//�ж�ͷ�ڵ�֮���Ƿ���Ԫ�أ����пպ���
bool headEmpty()
{
	if (bound_head->next == NULL) {
		return true;
	}
	return false;
}

//�ڴ��������쳣�ж�
inline Th* Out_get()
{
	//Th* t = (Th*)malloc(sizeof(Th));	//C���������ڴ淽ʽ
	Th* qw = new Th;	//C++�����ڴ淽ʽ�����Ӱ�ȫ���ȶ�
	qw->next = NULL;
	if (qw == NULL) {
		cout << "�ڴ�����ʧ��" << "\n";
		exit(1);	//�ж�
	}
	return qw;
}

vector<Th*> AllInfo;	//������Ҫ��Ϊȫ�ֱ�����ʹ�ã����ƺ�Ҳû����ô��Ҫ
//����һ��������ǰ������Ϣ�Ľṹ��ָ�����飬����vector���ṩ���ϲ㺯��ʹ��
vector<Th*> getAllInfo()
{
	AllInfo.clear();	//ÿ��ʹ��֮ǰҪclear��vector����������ֵ
	Th* t;
	if (isNull(bound_head)) {
		cout << "��ǰû���κ���Ϣ" << endl;
		exit(1);	//�ж�
	}
	t = bound_head;
	while (t->next != NULL) {
		t = t->next;
		AllInfo.push_back(t);	//�ṹ��ָ���������ջ����ע�������
	}
	return AllInfo;
}

//�õ��ĲĽṹ�������ͷ(��һ�����������Ϣ)
Th* getHead()
{
	return bound_head;
}

//�õ��ĲĽṹ�������β(���һ�����������Ϣ)
Th* getReal()
{
	return bound_real;
}

//����������id�ķ�ʽ����һ���Ĳ���Ϣ��ǰһ���ڵ����Ϣ(Ϊ�˷���ɾ����Ϣ)
Th* search_Info(const string& id_key)	//����һ������ֵ�Խ�ʡһ���ڴ�
{
	if (isNull(bound_head)) {
		cout << "��ǰû���κ���Ϣ" << endl;
		exit(1);	//�ж�
	}
	Th* key = bound_head;
	while (key->next->id!=id_key) {	//
		if (key->next == NULL) {
			//cout << "û���ҵ�idΪ" <<id_key<<"�ĺĲ�" << endl;
			break;
		}
		key = key->next;
	}
	return key;
}

//����(ɾ��һ��ָ���ĺĲ�) ����bool �ײ�Ϊ��������
//���ܺĲĵ�idֵ
bool Out_bound(const string& id_key)
{
	if (isNull(bound_head)) {
		cout << "��ǰû���κ���Ϣ" << endl;
		return false;
	}
	//O(1)��ʽ����
	Th* t = search_Info(id_key);	//�õ�ǰ�ýڵ�
	Th* p = t->next;		//�����ɾ���ڵ㣬һ���ͷ��ڴ�
	t->next = t->next->next;	//������ɾ���ڵ�
	delete(p);	//�ͷ��ڴ�
	return true;
}

//ɾ�����еĺĲ���Ϣ ����һ��bool ȫ��ɾ���ɹ�����true 
bool del_All()
{
	if (isNull(bound_head)) {
		cout << "��ǰû���κ���Ϣ������ɾ��" << endl;
		exit(1);	//�ж�
	}
	Th* p = bound_head;
	Th* t;
	while (p->next!=NULL) {
		//����
		if (p->next->next == NULL) {	//ֻ��һ���Ĳ�ʱ���⴦��
			t = p->next;
			p->next = NULL;
			delete(t);
			break;		//����֮��ֱ���˳�ѭ������
		}
		t = p->next;
		p->next = p->next->next;
		delete(t);
	}
	return true;
}

//һ���ӿڣ����ڸ���д���ļ��ķ�ʽ���ﵽ����ļ��д��������Ϣ
//����һ���ļ���
bool delFileAll(const string& filename)
{
	ofstream delAll(filename, std::ios::out);

	// ����ļ��Ƿ�ɹ���
	if (!delAll.is_open()) {
		cerr << "�޷����ļ�: " << filename << endl;
		exit(1);	//�ж�
	}
	delAll.seekp(0);	// ���ļ���λ�ö�λ���ļ��Ŀ�ʼ��
	
	delAll << '\0';	// ����д��һ�����ַ�������ļ�����
	
	delAll.close();	// �ر��ļ���
}

//���ݺĲ����������е�ͬ���Ĳģ������һ���ṹ�����鷵��
//ֱ������vector
vector<Th*> AllName;
vector<Th*> searchAllName(const string& nam)
{
	//���Ǳ��������ѯ���鵽��push_back��vector
	//�����˳��
	if (isNull(bound_head)) {
		cout << "��ǰû���κ���Ϣ" << endl;
		exit(1);	//�ж�
	}

	Th* p = bound_head;
	while (p->next!=NULL) {
		p = p->next;	//�Ƚ�����һ������Ϊpָ��ͷ�ڵ�
		if (p->name == nam) {
			AllName.push_back(p);	//��Ⱦͷ���vector
		}
	}
	return AllName;
}

//���ݺĲ�����û����Ҹ��û������кĲģ������һ���ṹ�����鷵��
//ֱ������vector
vector<Th*> AllUser;
vector<Th*> searchAllUser(const string& use)
{
	if (isNull(bound_head)) {
		cout << "��ǰû���κ���Ϣ" << endl;
		exit(1);	//�ж�
	}

	//�������ʵ�ֻ������
	Th* p = bound_head;
	while (p->next != NULL) {
		p = p->next;
		if (p->uesr == use) {
			AllUser.push_back(p);
		}
	}
	return AllUser;
}


//�ǽӿ�Ҳ�ǵײ�
//����һ���ṹ��ָ�룬���ṹ��ָ��ת��Ϊһ��string
string ThToString(Th *p)
{
	string Info;
	Info = p->id + "," + p->name + "," + p->In_date + "," + p->Out_date + "," + p->uesr + "," + to_string(p->MAX_K);
	return Info;
}