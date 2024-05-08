/*
此函数为main函数
可一键启动项目
*/
#include "Base.h"
#include "Put_in_s.h"
#include "Out_bound.h"
#include "Inventory_management.h"
#include "Reports_and_Statistics.h"
#include "Data_safe.h"	
#include <opencv2/opencv.hpp>	//opencv
#include <zbar.h>	//Zbar
#include "QR_code_management.h"		//二维码识别
#include "GUI.h"
#include "SystemCore.h"
#include "User_and_Permission_Management.h"
using namespace zbar;
//全局链表头节点指针
//用户输入时构建链表使用
Th he;

//全局链表尾指针
//实现O(1)插入
//初始化的时候要设置一下
//在遍历插入的过程当中要记录下尾指针
Th* re = &he;

//测试用
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
	
	// 输出二维码图片的文件路径
	string outputPath = "E:\\C Project\\C++ Project\\By VS 2022\\基于C C++的二维码识别出入库仓库管理系统\\基于C C++的二维码识别出入库仓库管理系统\\qrcode.png";
	const char* data = "misaki";
	// 创建并保存二维码图片
	createQRCodeImage(data, outputPath);
	string value = GetQRFromImage(outputPath);
	string value2 = GetQRFromImage("E:\\C Project\\C++ Project\\By VS 2022\\基于C C++的二维码识别出入库仓库管理系统\\基于C C++的二维码识别出入库仓库管理系统\\1.png");
	cout << value << endl;

	cout << value2 << endl;

	
}   
// 定义按钮的结构体


int main()
{
	InitAll(&he,re);
	menu();
	return 0;
}