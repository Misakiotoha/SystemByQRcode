/*
	�ú���Ϊ��⺯��
	ʵ���ˣ�
	�Ĳ����
	ͬʱԤ����һЩ�ӿ�
	�ײ��������ʵ��
*/

/*
	��Ҫע�⣬����������ڵĺ�������Ҫ���з�װһ��ָ����ΪNULL�ĺĲĽṹ��
*/
#include "Base.h"
Th* head;
Th* real;
//��ʼ������
void init(Th* h,Th* r)	
{
	head = h;
	real = r;
}

//�ײ㺯��������һ���ĲĽṹ��ռ䲢���ض�Ӧָ�룬���ٴ�����
inline Th* Cons_get()
{
	//Th* t = (Th*)malloc(sizeof(Th));	//C���������ڴ淽ʽ
	Th* qw = new Th;	//C++�����ڴ淽ʽ�����Ӱ�ȫ���ȶ�
	qw->next = NULL;
	qw->MAX_K = 114514;	//����Ĭ��ֵ
	if (qw == NULL) {
		cout << "�ڴ�����ʧ��" << "\n";
		exit(1);	//�ж�
	}
	return qw;
}

//�ײ㺯�����õ���ǰ������βָ��
Th* get_Real()
{
	return real;
}

//�ײ㺯����ʵ����βָ�봦O(1)��������
void insert_Real(Th* p)
{
	real->next = p;	//���Ԫ����βָ��
	//cout << real->next->uesr << " " << head->next->uesr << endl;	//?����bug
	//˼���˼��룬���֪��ԭ���ˣ����ȣ�����ΪBase.h��Put_in_s.h����֮����ض����������ȡ��static������ض�������
	//���ǣ�����֮��ԭ���ظ�����Ķ�������������鲻ͬ�Ķ���������ȫ����һ���Ķ�����Ҳ����˵����ĳ�̶ֳ���
	//������������˾ֲ�������ִ����Get_in_file()���֮���޸ĵ�������������ڵ�ֵ��Ȼ����뵽��Main����
	//���л������µ�head��real�ˣ������������޸ĵ���Get_in_file()���ڵ�head��real�����ԲŻᱨ��
	
	real = p;	//debug֮���ֵģ�ֻ��Ҫ��βָ��ָ��ǰ�����Ԫ�ؼ���
	//real=p->next;		//����βָ��ָ�����һ��Ԫ��
	real->next = NULL;	//��֤���һ��Ԫ��ֵΪNULL
}

//�ײ㺯�� �Ĳ����
bool Put_in_cin(Th *p)	//����һ��Th���͵Ľṹ�壬����ֵ����Ϊ�������ͣ��������ɹ���ʧ�ܣ�������Դ�û�¼��
{
	Th* node = Cons_get();	//���õײ㺯��
	node = p;	//����ȡ���Ľṹ��ָ����������nodeָ��
	//����ɹ����õ��ĺĲĽṹ��װ��������
	if (head->next == NULL) {	//�����ʱ��ͷ�ṹ��֮��û����Ϣ
		head->next = node;
		real = head->next;	//����βָ��ָ�����һ��Ԫ��
	}
	else {	//����������ֱ��û�е����
		Th* q = head->next;	//ͷ���治��Ŷ�����ֻ��ͷ�ڵ��ڵ�ָ����
		while (q->next!=NULL) {
			q = q->next;
		}
		q->next = node;
		real = q->next;	//����βָ��ָ�����һ��Ԫ��
	}
	return true;	//��ɲ��룬����true
}



//�ײ㺯�� ������Ϣ���ļ����� ����Ԥ����ļ���ΪCons.data
bool Save(const string& filename)	//�����ļ������������ڴ浱�е�������������ļ�����
{
	
	ofstream outf(filename, std::ios::trunc);	//д�뷽ʽΪ���Ƿ�ʽ���ļ�
	//ofstream outf(filename);		//����д��
	if (!outf.is_open()) {	//�쳣���
		std::cerr << "�޷����ļ�:"<<filename<<"�Խ���д��" << std::endl;
		exit(1);	//�ж�
	}
	Th* t=head->next;
	//�쳣����
	if (t == NULL) {	//���û���κ���Ϣ����д��������
		cout << "�����ݱ���" << endl;	//
		return false;
	}
	
	while (t!=NULL) {
		outf << t->id << ","		//д��ÿһ���ṹ���е����ݣ�����֮���Զ��Ÿ�����һ���Ĳ�һ������
			<< t->name << ","
			<< t->In_date << ","
			<< t->Out_date << ","
			<< t->uesr << ","
			<<t->MAX_K<< endl;
		t = t->next;
	}
	outf.close();	//ȫ�������ر��ļ���ȡ
	return true;		//��ɱ��棬����true
}

//ΪGet_in_file����ĵײ�
//ʵ���˽��ļ��е�һ����Ϣ������һ���ĲĽṹ��
inline Th* P_S(const string& line)
{
	Th* t = Cons_get();	//ֱ�ӵ��õײ㺯��
	istringstream iss(line);
	string ids;
	std::getline(iss, ids, ',');
	t->id = ids;
	//�˴������Ż���ѭ��
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
	t->MAX_K = (ll)stoi(KC);	//ǿת����һ��
	return t;
}

//�ӿ�1
//���ļ��ж�ȡ���ݹ�������
void Get_in_file(const string& filename)	//����һ���ļ�������һ���ļ�����ȡ�ļ��ڵ����ݹ��������ṩ����ʼ���Ⱥ���ʹ��
{
	ifstream Infile(filename);
	if (!Infile.is_open()) {
		std::cerr << "�޷���ȡ�ļ�:" << filename << std::endl;
		exit(1);
	}
	Th* q;
	string line_data;	//ֵΪÿһ�е�����
	while (getline(Infile, line_data)) {	//���ж�ȡ����
		q=P_S(line_data);	//�����ŷָ��ַ����õ��ĲĽṹ��
		//���õ���ָ����ӽ�������,�������βָ����뺯��
		insert_Real(q);		//����Ľڵ��head��ʼ
	}
	Infile.close();
}


//�ӿ�2������һ��string��������һ��Th�ṹ�巵��
Th* stringToTh(const string& str)
{
	return P_S(str);
}



//�����ܿ�� �ᱻ��ε���
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