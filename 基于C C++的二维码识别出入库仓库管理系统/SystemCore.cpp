/*
���ֿ����ϵͳ�ĺ���
������ײ㽻�������Σ����ã���ʼ��
�������ϲ�GUI�ӿڽ��������ܲ��������õײ�
����������м�㣬��ôGUI��͵ײ�ֱ�ӽ�����ʹ��GUI��ǳ����ӣ������޸�
*/

#include "Base.h"
#include "Put_in_s.h"
#include "Out_bound.h"
#include "Inventory_management.h"
#include "Reports_and_Statistics.h"
#include "Data_safe.h"	
#include <opencv2/opencv.hpp>	//opencv
#include <zbar.h>	//Zbar
#include "QR_code_management.h"		//��ά��ʶ��



/*
��ʼ������
*/
bool InitAll(Th* h, Th* r)
{
	init(h,r);
	init_bound(h,r);
	Get_in_file("Cons.data");	//���ļ����ж�������
	setAllKC();		//�������ǰ���еĿ��ֵ

	AutoBackup("Cons.data","Cons.bak");

	return true;
}


/*
���ά��ʶ��Ľ���
*/
string Info="";
//����һ��·�����ײ㷵�ص�ʶ�������������������ͬ�ĵײ㣬�����ײ�ľ�׼�Ĳ���ͬ
//����һ��string��ֵ�����������ʹ��

//99%
bool GetQRInfoBest(const string& FileLocation)
{

	Info=GetQRFromImage(FileLocation);	//�ڲ��д���·��Ϊ�յ��쳣����
	return true;
}

//90%
bool GetQRInfo(const string& FileLocation)
{
	Info = recognizeQRCode(FileLocation);
	return true;
}

//���ɶ�ά�벿��
//����һ��const char* data����Ҫ���ɵ���Ϣ, ����һ���ļ�·���µĶ�ά��ͼƬstring outputPath
// �����ֵΪ�����ɵ��ļ�����
//����漰��һ����ά���ļ���������ʹ�����·�������ڵ�ǰĿ¼QRCODE����
//����ֵΪ�ļ�·��
//�ļ����˴���Ӧ�Ĳĵ�Ψһid
string CreateQRcode(const char* data, string Filename)
{
	string outputPath = "QRCODE\\"+Filename+".png";	//����������ļ�����
	createQRCodeImage(data, outputPath);
	return outputPath;
}



/*
�������Ľ�����Ҳ�������ͳ���
*/




/*
���Ͽ�����Ͷ�ά��ʶ��
�漰��map���ȸ߼����ݽṹ
*/



/*
�����ݱ��ݵĽ���
*/
//�ֶ����� ΪGUI�ṩ�ӿ�
bool ManualBackup(const string& BeforeName, const string& AfterName)
{
	ByUserBackup(BeforeName, AfterName);
	return true;
}


/*
���û�����Ľ���
*/

/*
�뱨���ӡ�Ľ���
*/




/*
�������ϵĽ���
�ṩ���ϲ�GUI��һ�нӿ�
*/


