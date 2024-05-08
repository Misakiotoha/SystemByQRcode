/*
�˺���Ϊmain����
��һ��������Ŀ
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
#include "GUI.h"
#include "SystemCore.h"
#include "User_and_Permission_Management.h"
using namespace zbar;
//ȫ������ͷ�ڵ�ָ��
//�û�����ʱ��������ʹ��
Th he;

//ȫ������βָ��
//ʵ��O(1)����
//��ʼ����ʱ��Ҫ����һ��
//�ڱ�������Ĺ��̵���Ҫ��¼��βָ��
Th* re = &he;

//������
void test()
{
	
	cout << he.next->next->uesr << endl;

	vector<Th*> t = searchAllUser("Wasabi");
	for (auto k : t) {
		cout << k->id << endl;
	}

	map<string, ll> s = getNameToValue();
	for (auto x : s)
	{
		cout << x.first << x.second << endl;
	}
	map<string, ll> sb = getNameToMax();
	for (auto z : sb)
	{
		cout << z.first << z.second << endl;
	}
	SortPrintAll();
	cout << endl;
	PrintAll();
	cout << endl;
	PrintForName("test");
	cout << endl;
	PrintForUser("Misaki");
	ByUserBackup("Cons.data", "Cons.bak");

	//

	/*Mat img = imread("mm.jpg");
	namedWindow("1");
	imshow("1", img);
	waitKey(6000);
	destroyAllWindows();*/

	//
	
	// �����ά��ͼƬ���ļ�·��
	string outputPath = "E:\\C Project\\C++ Project\\By VS 2022\\����C C++�Ķ�ά��ʶ������ֿ����ϵͳ\\����C C++�Ķ�ά��ʶ������ֿ����ϵͳ\\qrcode.png";
	const char* data = "misaki";
	// �����������ά��ͼƬ
	createQRCodeImage(data, outputPath);
	string value = GetQRFromImage(outputPath);
	string value2 = GetQRFromImage("E:\\C Project\\C++ Project\\By VS 2022\\����C C++�Ķ�ά��ʶ������ֿ����ϵͳ\\����C C++�Ķ�ά��ʶ������ֿ����ϵͳ\\1.png");
	cout << value << endl;

	cout << value2 << endl;

	
}   
// ���尴ť�Ľṹ��


int main()
{
	InitAll(&he,re);
	menu();
	return 0;
}