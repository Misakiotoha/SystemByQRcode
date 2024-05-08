/*
�ú���Ϊ���ݰ�ȫ����
ʵ�������ݵ��Զ����ֶ�����
���ݵ������ļ�Ĭ����Ϊ"Cons.bak"
*/
#include "Base.h"
#include "Inventory_management.h"
#include "Out_bound.h"
#include "Put_in_s.h"

//�Զ����ݺ��� ÿ����������һ������
//����ֵΪbool�����Զ����ݳɹ��򷵻�bool
//���������ļ�����ǰ�������Ҫ���ݵ��ļ�����һ���Ǳ����ļ���
bool AutoBackup(const string& BeforeName,const string& AfterName)
{
    std::ifstream source;      // �����ļ��������ڶ�ȡԭʼ�ļ�
    std::ofstream backup;      // ����ļ���������д�뱸���ļ�

    // ��ԭʼ�ļ�
    source.open(BeforeName, std::ios::binary);
    if (!source.is_open()) {
        std::cerr << "�޷���ԭʼ�ļ�: " << BeforeName << std::endl;
        return false;
    }

    // �򿪱����ļ�
    backup.open(AfterName, std::ios::binary);
    if (!backup.is_open()) {
        std::cerr << "�޷����������ļ�: " << AfterName << std::endl;
        source.close(); // �ر�ԭʼ�ļ�
        return false;
    }

    // ��ȡԭʼ�ļ����ݲ�д�뱸���ļ�
    backup << source.rdbuf(); // ʹ�� rdbuf() ��ȡԴ�ļ����������ݲ�д�뱸���ļ�

    // �ر��ļ���
    source.close();
    backup.close();
    return false;
}


//�ֶ����� �û����о����Ƿ񱸷�
//��������������ڣ�����Ļᱻ����init()��ʼ����������
bool ByUserBackup(const string& BeforeName, const string& AfterName)
{
    std::ifstream source;      // �����ļ��������ڶ�ȡԭʼ�ļ�
    std::ofstream backup;      // ����ļ���������д�뱸���ļ�

    // ��ԭʼ�ļ�
    source.open(BeforeName, std::ios::binary);
    if (!source.is_open()) {
        std::cerr << "�޷���ԭʼ�ļ�: " << BeforeName << std::endl;
        return false;
    }

    // �򿪱����ļ�
    backup.open(AfterName, std::ios::binary);
    if (!backup.is_open()) {
        std::cerr << "�޷����������ļ�: " << AfterName << std::endl;
        source.close(); // �ر�ԭʼ�ļ�
        return false;
    }

    // ��ȡԭʼ�ļ����ݲ�д�뱸���ļ�
    backup << source.rdbuf(); // ʹ�� rdbuf() ��ȡԴ�ļ����������ݲ�д�뱸���ļ�

    // �ر��ļ���
    source.close();
    backup.close();
    return true;
}