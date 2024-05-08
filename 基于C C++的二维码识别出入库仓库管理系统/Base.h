#pragma once
/*
��ͷ�ļ����ں궨��һЩ�����Լ��ṹ�壬��������
�Լ�����ͷ�ļ��ĵ���
*/
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include "malloc.h"
#include <string>	//C++���п⣬�ڰ����˶�String���͵�ʵ��
#include <vector>	//��̬����⺯��C++����
#include <algorithm>	//STL��
#include <map>
//C++�ļ����������
#include <fstream>  
#include <sstream>
#include <stdint.h>
//OpenCVͷ�ļ�
//#include "opencv2/opencv.hpp"
#include <graphics.h>
#include <conio.h>	//�������Ƿ�������

#include <commdlg.h>    //windows API cmd

using namespace std;	//C++���У����ֿռ�
//using namespace cv;	//opencv���ֿռ�
typedef long long ll;

//�ṹ�嶨�壬������Ϣ���Դ���QR�뵱��
typedef struct th {
	string name;		//�Ĳ���

	string id;			//�Ĳ�Ψһid

	string In_date;		//�������
	string Out_date;	//��������

	string uesr;		//���һ��ʹ���ߣ�Ϊ�û���Ȩ�޹���Ԥ��
	ll MAX_K;			//ÿһ���Ĳĵ���󾯽�ֵ��Ĭ��ֵ114514��֧���Զ�������
	th* next;			//ָ����ָ�������ͣ��γ���ʽ�ṹ
}Th;




// ���������Ľṹ��
struct InputField {
    int x, y, width;
    string text;
    // ���ڻ��������
    void draw() {
        setfillcolor(LIGHTGRAY);
        fillrectangle(x, y, x + width, y + 20);
        settextcolor(BLACK);
        settextstyle(16, 0, _T("Arial"));
        outtextxy(x + 5, y + 5, (LPCTSTR)text.c_str());
    }
    // ���ڻ�ȡ�û�������ı�
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



// GUI���水ť�Ľṹ�嶨��
struct Button {
    int x, y, width, height;
    string text;
    bool MouseLeft;

    void draw() {
        setfillcolor(LIGHTGRAY);
        fillrectangle(x, y, x + width, y + height);
        settextcolor(BLACK);
        settextstyle(16, 0, _T("Arial")); // ����������ʽ
        outtextxy(x + (width - text.length() * 8) / 2, y + (height - 16) / 2, (LPCTSTR)text.c_str());
    }
    //���ð�ť
    void setBounds(int x_, int y_, int width_, int height_) {
        x = x_;
        y = y_;
        width = width_;
        height = height_;
    }

    bool isClicked(int mx, int my) {
        return mx >= x && mx <= x + width && my >= y && my <= y + height;
    }

    // �������¼����������ļ�ѡ��Ի���
    string handleClick() {
        OPENFILENAME ofn; // �����ļ�ѡ��Ի���Ľṹ�����
        char szFile[260] = ""; // �洢�ļ����Ļ�����
        string selectedImagePath; // ���ڴ洢ѡ�е��ļ�·��

        // ��ʼ���ļ�ѡ��Ի���Ľṹ��
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = NULL; // ӵ�д˶Ի���Ĵ��ڵľ��
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = "PNG Files (*.png)\0*.png\0All Files (*.*)\0*.*\0"; // �����ļ�ѡ��Ի���Ĺ�����
        ofn.nFilterIndex = 1; // Ĭ�Ϲ�����
        ofn.lpstrFile[0] = '\0'; // ȷ���ļ���������Ϊ��
        ofn.lpstrTitle = "ѡ��һ��PNG��ά���ļ�"; // �Ի������
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

        // ��ʾ�ļ�ѡ��Ի���
        if (GetOpenFileName(&ofn)) {
            // ����û�ѡ�����ļ������ļ�·���洢��selectedImagePath
            selectedImagePath = szFile;
            return selectedImagePath;
        }
        else {  //û��ѡ��ͷ��ؿ��ַ���
            return "";
        }
    }

    // �����ȡ��������ĺ���
    InputField getInputField(int x, int y, int width) {
        InputField field;
        field.x = x;
        field.y = y;
        field.width = width;
        field.text = "";
        return field;
    }

    string TextInputClick() {
        // �������������߼�
        string itemId;
        string itemName;
        string Indate;
        string Outdate="";
        string userName;
        string JJZ;

        // ��ȡϵͳ���ڣ�ֱ�ӵ���ϵͳ����
        SYSTEMTIME st;
        GetSystemTime(&st);
        stringstream dateStream;
        dateStream << (st.wYear ) << "-" << (st.wMonth ) << "-" << st.wDay;
        Indate = dateStream.str();

        // ��ʾ������ʾ����ȡ�û�����
        settextcolor(RED);
        outtextxy(300, 300, (LPCTSTR)"�����������ƷID:");
        itemId = getInputField(300, 320, 200).getInput();
        outtextxy(450, 300, (LPCTSTR)itemId.c_str());

        outtextxy(300, 350, (LPCTSTR)"�����������Ʒ����:");
        itemName = getInputField(300, 370, 200).getInput();
        outtextxy(470, 350, (LPCTSTR)itemName.c_str());

        outtextxy(300, 400, (LPCTSTR)"�������:");
        // ֱ����ʾ���ڣ������û�����
        outtextxy(300, 420, (LPCTSTR)Indate.c_str());
        
        outtextxy(300, 450, (LPCTSTR)"����������û���:");
        userName = getInputField(300, 470, 200).getInput();
        outtextxy(470, 450, (LPCTSTR)userName.c_str());

        outtextxy(300, 480, (LPCTSTR)"�����������Ʒ����ֵ:");
        JJZ=getInputField(300, 500, 200).getInput();
        outtextxy(470, 480, (LPCTSTR)JJZ.c_str());


        // ����������ݱ��浽�ַ�����
        string result = itemId + "," + itemName + "," + Indate + "," + Outdate+","+userName + "," + JJZ;
        return result;
    }
};


