#pragma once

//��ʼ������ ����һ��ͷ�ڵ����ú�βָ��
void init(Th* h, Th* r);

//�ײ㺯��������һ���ĲĽṹ��ռ䲢���ض�Ӧָ�룬���ٴ�����
//��Ϊֻ�ں����ڲ����ã�����ʹ��inline����һ����ڴ�������
inline Th* Cons_get();

//�ӿ�1
//���ļ��ж�ȡ���ݹ�������
void Get_in_file(const string& filename);

//�ײ㺯�����õ���ǰ������βָ��
Th* get_Real();

//�ײ㺯����ʵ����βָ�봦O(1)��������
void insert_Real(Th* p);

//�ײ㺯�� �Ĳ����
bool Put_in_cin(Th* p);

//�ײ㺯�� ������Ϣ���ļ����� ����Ԥ����ļ���ΪCons.data
bool Save(const string& filename);

//ΪGet_in_file����ĵײ�
//ʵ���˽��ļ��е�һ����Ϣ������һ���ĲĽṹ��
inline Th* P_S(const string& line);

//�ӿ�2������һ��string��������һ��Th�ṹ�巵��
Th* stringToTh(const string& str);

//�����ܿ�� �ᱻ��ε��ã���inline����
//
ll getALLKC();