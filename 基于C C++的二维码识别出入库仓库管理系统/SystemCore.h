#pragma once

#include "Base.h"

/*
��ʼ������
*/
bool InitAll(Th* h, Th* r);


/*
���ά��ʶ��Ľ���
*/
//����һ��·�����ײ㷵�ص�ʶ�������������������ͬ�ĵײ㣬�����ײ�ľ�׼�Ĳ���ͬ
//����һ��string��ֵ�����������ʹ��

//99%
bool GetQRInfoBest(const string& FileLocation);

//90%
bool GetQRInfo(const string& FileLocation);


//���ɶ�ά�벿��
//����һ��const char* data����Ҫ���ɵ���Ϣ, ����һ���ļ�·���µĶ�ά��ͼƬstring outputPath
// �����ֵΪ�����ɵ��ļ�����
//����漰��һ����ά���ļ���������ʹ�����·�������ڵ�ǰĿ¼QRCODE����
//����ֵΪ�ļ�·��
//�ļ����˴���Ӧ�Ĳĵ�Ψһid
string CreateQRcode(const char* data, string Filename);