/*
�ú���Ϊ��������
ʵ���˲��ң�����ȹ���
ͬʱԤ����һЩ�ӿ�
��Ҫ��ȥ���õĵײ�ĳ�������Ѿ�ʵ�ֵĹ���
����ֻ��Ϊ�˷����ϲ�ͳһ����
*/
#include "Base.h"
#include "Out_bound.h"
#include "Put_in_s.h"


//���Ԥ��ֵ������ͨ���ӿ������趨
ll MAX_KC = 0;

//�����ֵ
ll ALL_KC = 114514;

//����һ��long long��ֵ�����ÿ����Ԥ��ֵ���ɹ�����true
bool setKC(ll k)
{
	MAX_KC = k;
	return true;
}

//���Һ��������԰�id(ֻ����Ψһ��ָ��),ԭ���Ƿ��ص���ǰһ���ڵ��ָ�룬������ĳ��˷���ָ����ָ��
Th* getId(const string& ids)
{
	Th* p = search_Info(ids);
	if (p->next == NULL) {
		//û�ҵ������
		exit(1);
	}
	//�ҵ������
	p = p->next;
	return p;
}

//���Һ��������԰��Ĳ�����(��������ͬ��������ָ��)
vector<Th*> getNames(const string& nam)
{
	return searchAllName(nam);
}

//���Һ��������԰��Ĳ�����û�(��������ͬ�û���������ָ��)
vector<Th*> getUsers(const string& use)
{
	return searchAllUser(use);
}

//���㵱ǰ�����ֵ	����ڳ�ʼ����������
void setAllKC()
{
	ALL_KC = getALLKC();
}

//�õ���ǰ�Ŀ����ֵ
ll getAllKC()
{
	return ALL_KC;
}

//������ǰ���������õ�һ����ֵ�Եı�ֵΪ�Ĳ����ֶ�����
//�ᱻ��ε���
//���ɱ���Ҳ������������
map<string, ll> NameToValue;
map<string, ll> getNameToValue()
{
	if (headEmpty()) {	//���û��Ԫ�أ�������
		cout << "û���κ�����" << endl;
		exit(1);
	}
	NameToValue.clear();
	//�����������
	//ʹ���²㺯��getAllInfo�����һ����Ŵ�ʱ��������Ϣ��vector��ע��ֻ�Ǵ�ʱ��
	vector<Th*> T = getAllInfo();
	//�������vector��ѹ��map����
	for (auto k : T)	//auto��C++���У��Զ�ʶ������T������
	{
		NameToValue[k->name]++;
	}
	return NameToValue;
}

//ֱ���������
map<string, ll> NameToMax;
//��������õ�һ����ֵ�Եı�ֵΪ�Ĳ����ֶ����������Ҳ����Ԥ��ֵ��
map<string, ll> getNameToMax()
{
	if (headEmpty()) {	//���û��Ԫ�أ�������
		cout << "û���κ�����" << endl;
		exit(1);
	}
	NameToMax.clear();
	//�����������
	//ʹ���²㺯��getAllInfo�����һ����Ŵ�ʱ��������Ϣ��vector��ע��ֻ�Ǵ�ʱ��
	vector<Th*> T = getAllInfo();
	for (auto k : T)	//auto��C++���У��Զ�ʶ������T������
	{
		NameToMax[k->name] = k->MAX_K;		//���Ŷ�ȡ��������ͬ������Ԥ��ֵ��ͬ����Ϊ�����������õģ������������ֵ
	}
	return NameToMax;
}

map<string, ll> exceededWarnings;
// Ԥ��ֵɸѡ����
map<string, ll> getExceededWarningMap() 
{
	exceededWarnings.clear();
	NameToMax.clear();
	NameToValue.clear();

	// ��ȡ��ǰ���кĲĵ�ʹ�����
	NameToValue = getNameToValue();
	// ��ȡ��ǰ���кĲĵ�Ԥ��ֵ
	NameToMax = getNameToMax();

	// �����Ĳ�ʹ����� 
	for (const auto& pair : NameToValue) {
		string name = pair.first;
		ll Ovalue = pair.second;

		// ����Ƿ���ڶ�Ӧ��Ԥ��ֵ
		if (NameToMax.find(name) != NameToMax.end()) {
			ll k = NameToMax[name];

			// �����ǰ��������Ԥ��ֵ�����¼ΪԤ���¼�
			if (Ovalue > k) {
				exceededWarnings[name] = k;
			}
		}
	}

	return exceededWarnings;
}

// ��ȡ��������ֵ�ĺĲļ��䳬����������map
map<string, ll> getExceededWarningMapx() 
{
	exceededWarnings.clear();
	map<string, ll> nameToValue;
	nameToValue.clear();
	// ��ȡ���кĲĵ����ƺ�����
	nameToValue = getNameToValue();
	// ��ȡ���кĲĵ����ƺ�Ԥ��ֵ
	map<string, ll> nameToMax;
	nameToMax.clear();
	nameToMax = getNameToMax();

	// �������кĲ�
	for (const auto& entry : nameToValue) {
		string name = entry.first;
		ll ov = entry.second;

		// ���ҺĲĵ�Ԥ��ֵ
		auto maxIt = nameToMax.find(name);
		if (maxIt != nameToMax.end()) {
			ll k = maxIt->second;

			// �����ǰ��������Ԥ��ֵ�����㳬��������
			if (ov > k) {
				ll bv = ov - k;
				exceededWarnings[name] = bv;
			}
		}
	}

	return exceededWarnings;
}


//����Ԥ����Ĭ������Ϊÿһ���Ĳ�5��Ϊ����
// ����Ԥ������
map<string, ll> getRestockWarning() 
{
	map<string, ll> NameToValue = getNameToValue(); // ��ȡ��ǰ�Ĳ�������ӳ��
	map<string, ll> NameToMax = getNameToMax(); // ��ȡ�Ĳ����������ӳ��
	map<string, ll> restockNeeded; // ��Ҫ������ӳ��

	ll restockThreshold = 5; // ��������Ԥ��ֵ

	for (const auto& valuePair : NameToValue) {
		string name = valuePair.first;
		ll currentCount = valuePair.second;

		// ��� NameToMax ���Ƿ���ڶ�Ӧ����Ŀ
		auto maxIt = NameToMax.find(name);
		if (maxIt != NameToMax.end()) {
			ll maxCount = maxIt->second;

			// �����ǰ����С�� restockThreshold�������ȱ�ٵ�����
			if (currentCount < restockThreshold) {
				ll shortage = restockThreshold - currentCount; // ȱ�ٵ�����
				restockNeeded[name] = shortage;
			}
		}
		else {
			// ��� NameToMax �в����ڸúĲģ��򲻽���Ԥ�������߸�����Ҫ����
			restockNeeded[name] = currentCount; // ����ѡ�񽫵�ǰ������Ϊȱ�ٵ�����
		}
	}

	return restockNeeded;
}