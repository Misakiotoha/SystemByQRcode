#pragma once
/*
该头文件用于宏定义一些常量以及结构体，函数声明
以及其他头文件的导入
*/
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include "malloc.h"
#include <string>	//C++特有库，内包含了对String类型的实现
#include <vector>	//动态数组库函数C++特有
#include <algorithm>	//STL库
#include <map>
//C++文件输入输出流
#include <fstream>  
#include <sstream>
#include <stdint.h>
//OpenCV头文件
//#include "opencv2/opencv.hpp"
#include <graphics.h>
#include <conio.h>	//检测键盘是否有输入

#include <commdlg.h>    //windows API cmd

using namespace std;	//C++特有，名字空间
//using namespace cv;	//opencv名字空间
typedef long long ll;

//结构体定义，所有信息可以存入QR码当中
typedef struct th {
	string name;		//耗材名

	string id;			//耗材唯一id

	string In_date;		//入库日期
	string Out_date;	//出库日期

	string uesr;		//最后一次使用者，为用户与权限管理预留
	ll MAX_K;			//每一个耗材的最大警戒值，默认值114514，支持自定义设置
	th* next;			//指针域，指向本身类型，形成链式结构
}Th;




// 定义输入框的结构体
struct InputField {
    int x, y, width;
    string text;
    // 用于绘制输入框
    void draw() {
        setfillcolor(LIGHTGRAY);
        fillrectangle(x, y, x + width, y + 20);
        settextcolor(BLACK);
        settextstyle(16, 0, _T("Arial"));
        outtextxy(x + 5, y + 5, (LPCTSTR)text.c_str());
    }
    // 用于获取用户输入的文本
    string getInput() {
        string input = "";
        int key = 0;
        while ((key = getch()) != 13) { // 13 is the Enter key
            if (key == 8 && input.length() > 0) { // 8 is the Backspace key
                input.pop_back();
                continue;
            }
            if (key >= 32 && key <= 126) { // 32 to 126 are printable characters
                input += (char)key;
            }
        }
        return input;
    }
};



// GUI界面按钮的结构体定义
struct Button {
    int x, y, width, height;
    string text;
    bool MouseLeft;

    void draw() {
        setfillcolor(LIGHTGRAY);
        fillrectangle(x, y, x + width, y + height);
        settextcolor(BLACK);
        settextstyle(16, 0, _T("Arial")); // 设置字体样式
        outtextxy(x + (width - text.length() * 8) / 2, y + (height - 16) / 2, (LPCTSTR)text.c_str());
    }
    //设置按钮
    void setBounds(int x_, int y_, int width_, int height_) {
        x = x_;
        y = y_;
        width = width_;
        height = height_;
    }

    bool isClicked(int mx, int my) {
        return mx >= x && mx <= x + width && my >= y && my <= y + height;
    }

    // 处理点击事件，并弹出文件选择对话框
    string handleClick() {
        OPENFILENAME ofn; // 定义文件选择对话框的结构体变量
        char szFile[260] = ""; // 存储文件名的缓冲区
        string selectedImagePath; // 用于存储选中的文件路径

        // 初始化文件选择对话框的结构体
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = NULL; // 拥有此对话框的窗口的句柄
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = "PNG Files (*.png)\0*.png\0All Files (*.*)\0*.*\0"; // 设置文件选择对话框的过滤器
        ofn.nFilterIndex = 1; // 默认过滤器
        ofn.lpstrFile[0] = '\0'; // 确保文件名缓冲区为空
        ofn.lpstrTitle = "选择一个PNG二维码文件"; // 对话框标题
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

        // 显示文件选择对话框
        if (GetOpenFileName(&ofn)) {
            // 如果用户选择了文件，将文件路径存储到selectedImagePath
            selectedImagePath = szFile;
            return selectedImagePath;
        }
        else {  //没有选择就返回空字符串
            return "";
        }
    }

    // 定义获取输入框对象的函数
    InputField getInputField(int x, int y, int width) {
        InputField field;
        field.x = x;
        field.y = y;
        field.width = width;
        field.text = "";
        return field;
    }

    string TextInputClick() {
        // 弹出输入界面的逻辑
        string itemId;
        string itemName;
        string Indate;
        string Outdate="";
        string userName;
        string JJZ;

        // 获取系统日期，直接调用系统函数
        SYSTEMTIME st;
        GetSystemTime(&st);
        stringstream dateStream;
        dateStream << (st.wYear ) << "-" << (st.wMonth ) << "-" << st.wDay;
        Indate = dateStream.str();

        // 显示输入提示并获取用户输入
        settextcolor(RED);
        outtextxy(300, 300, (LPCTSTR)"请输入入库物品ID:");
        itemId = getInputField(300, 320, 200).getInput();
        outtextxy(450, 300, (LPCTSTR)itemId.c_str());

        outtextxy(300, 350, (LPCTSTR)"请输入入库物品名称:");
        itemName = getInputField(300, 370, 200).getInput();
        outtextxy(470, 350, (LPCTSTR)itemName.c_str());

        outtextxy(300, 400, (LPCTSTR)"入库日期:");
        // 直接显示日期，无需用户输入
        outtextxy(300, 420, (LPCTSTR)Indate.c_str());
        
        outtextxy(300, 450, (LPCTSTR)"请输入入库用户名:");
        userName = getInputField(300, 470, 200).getInput();
        outtextxy(470, 450, (LPCTSTR)userName.c_str());

        outtextxy(300, 480, (LPCTSTR)"请输入入库物品警戒值:");
        JJZ=getInputField(300, 500, 200).getInput();
        outtextxy(470, 480, (LPCTSTR)JJZ.c_str());


        // 将输入的数据保存到字符串中
        string result = itemId + "," + itemName + "," + Indate + "," + Outdate+","+userName + "," + JJZ;
        return result;
    }
};


