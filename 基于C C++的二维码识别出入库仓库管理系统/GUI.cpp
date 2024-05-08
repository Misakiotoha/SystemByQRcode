/*
这个cpp里面放的是GUI界面，全都是调用的底层函数
GUI基于EasyX
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
#include "User_and_Permission_Management.h"

void Put_in_GUI();
void Out_GUI();
void Inventory_GUI();
void User_GUI();
void Reports_GUI();
void Data_GUI();
bool HandlePaginationButtons(int& currentPage, const int pageSize, const int mouseX, const int mouseY, bool islf);
void PrintData(const vector<Th*>& data, int& currentPage, const int pageSize);
vector<Th*> GetDataFromFunctionn(const string& name);

string InputString();
//供全局一键使用，舍弃了initgraph的第三个参数
void initWindow(int w, int h)
{
	// 初始化图形界面
	initgraph(w, h); // 初始化一个全屏界面
	setbkcolor(WHITE);
	cleardevice();
	// 加载背景图片  
	IMAGE img;
	loadimage(&img, _T("background.jpg")); 

	// 将图片设置为背景  
	putimage(0, 0, &img); // 在 (0,0) 位置显示图片，即整个窗口都是背景图片
	
}

void menu()	//主菜单界面
{
	
	initWindow(1920, 1080);
	
	// 创建5个按钮的数组
	Button buttons[5];
	int buttonHeight = 80;
	int buttonWidth = 200;
	int buttonTop = 100;
	int buttonLeft = (640 - buttonWidth) / 2;
	//设置按钮的名字
	string button_name[5] = { "库存管理","用户管理","报表打印" ,"数据安全","退出"};

	for (int i = 0; i < 5; ++i) {
		buttons[i] = { buttonLeft, buttonTop + i * (buttonHeight + 20), buttonWidth, buttonHeight, button_name[i]};
	}
	

	// 绘制按钮
	for (Button& btn : buttons) {
		btn.draw();
	}
	map<string, ll> ti = getExceededWarningMapx();
	int temp = 1;
	for (auto k : ti)
	{
		temp++;
		outtextxy(600,400+temp*20,(LPCTSTR)(k.first + "的库存值已经超过预警值"+to_string(k.second)+"个了，请及时出库或者扩容").c_str());
	}
	ti.clear();

	temp = 1;
	ti = getRestockWarning();
	for (auto k : ti)
	{
		temp++;
		outtextxy(600, 200 + temp * 20, (LPCTSTR)(k.first + "的库存值已经低于下限值" + to_string(k.second) + "个了，请及时入库").c_str());
	}
	ti.clear();

	//用户登录状态
	if (getUser_State() == -1) {
		outtextxy(900, 100, (LPCTSTR)("当前无用户登录"));
	}
	if (getUser_State() == 0) {
		outtextxy(900, 100, (LPCTSTR)("当前为管理员用户"));
	}
	if (getUser_State() == 1) {
		outtextxy(900, 100, (LPCTSTR)("当前为普通用户"));
	}
	bool EXITGUI = true;		//退出的标志位
	
	// 主循环
	while (true) {
		// 检测鼠标点击事件
		if (MouseHit()) { // 检测是否有鼠标事件发生
			MOUSEMSG m = GetMouseMsg(); // 获取鼠标事件信息
			int mx = m.x; // 鼠标x坐标
			int my = m.y; // 鼠标y坐标
			for (Button& btn : buttons) { btn.MouseLeft = m.mkLButton; }	//获取鼠标左键
			// 检查鼠标点击是否在某个按钮上
			for (Button& btn : buttons) {
				if (mx >= btn.x && mx <= btn.x + btn.width && my >= btn.y && my <= btn.y + btn.height&&btn.MouseLeft) {
					if (btn.text == button_name[0] && getUser_State() == 0) {	//库存管理
						Inventory_GUI();
					}
					if (btn.text == button_name[1]) {	//用户管理
						User_GUI();
					}
					if (btn.text == button_name[2]&&(getUser_State()==1|| getUser_State() == 0)) {	//报表打印
						Reports_GUI();
					}
					if (btn.text == button_name[3]&&getUser_State() == 0) {	//数据安全
						Data_GUI();
					}
					//退出事件
					if (btn.text == button_name[4]) {		//退出
						EXITGUI = false;
					}
				}
			}
		}

		if (!EXITGUI) { // 
			break; // 
		}
	}

	// 关闭图形界面
	closegraph();

}



//入库手动输入界面
string TextInput()
{
	// 初始化图形界面
	initWindow(1920, 1080);
	string inputData="";
	
	// 创建按钮对象
	Button manualEntryButton = { 100, 100, 100, 50, "点击输入" };
	manualEntryButton.setBounds(100, 100, 100, 50);
	
	// 绘制按钮
	manualEntryButton.draw();
	
	// 消息处理循环
	while (true) {
		// 检测鼠标点击事件
		if (MouseHit()) {
			MOUSEMSG m = GetMouseMsg(); // 获取鼠标事件信息
			int mx = m.x; // 鼠标x坐标
			int my = m.y; // 鼠标y坐标
			manualEntryButton.MouseLeft = m.mkLButton;
			if (manualEntryButton.MouseLeft&& mx >= manualEntryButton.x && mx <= (manualEntryButton.x + 
				manualEntryButton.width) &&
				my >= manualEntryButton.y && my <= (manualEntryButton.y + 
				manualEntryButton.height)) {// 点击了按钮，执行点击事件
				
				inputData = manualEntryButton.TextInputClick();
				Put_in_cin(stringToTh(inputData));
				// 这里可以处理输入数据，例如显示或保存
				/*cout << "输入的数据为: " << inputData << endl;*/
				
				break;//退出循环，防止多次打开GUI
			}
		}
		
	}
	Put_in_GUI();	//输完就返回另一个GUI
	closegraph(); // 关闭图形界面
	return inputData;
}

//入库界面
void Put_in_GUI()
{
	// 初始化图形界面
	initWindow(1920, 1080);
	// 定义按钮
	Button manualButton;
	manualButton.setBounds(300, 250, 200, 60);
	manualButton.text = "手动输入入库";

	Button scanButton;
	scanButton.setBounds(300, 350, 200, 60);
	scanButton.text = "扫码入库";

	Button backButton;
	backButton.setBounds(300, 450, 200, 60);
	backButton.text = "返回";

	// 绘制按钮
	manualButton.draw();
	scanButton.draw();
	backButton.draw();

	string PngName="";	//默认为空字符串
	// 主循环
	while (true) {
		// 检测鼠标点击事件
		if (MouseHit()) {
			MOUSEMSG m = GetMouseMsg(); // 获取鼠标事件信息
			int mx = m.x; // 鼠标x坐标
			int my = m.y; // 鼠标y坐标
			manualButton.MouseLeft = m.mkLButton;
			scanButton.MouseLeft = m.mkLButton;	//鼠标左键是否被按下
			backButton.MouseLeft = m.mkLButton;

			if (manualButton.MouseLeft&& mx >= manualButton.x && mx <= (manualButton.x + manualButton.width) &&
				my >= manualButton.y && my <= (manualButton.y + manualButton.height)) {
				closegraph();
				TextInput();
				string inputData = manualButton.TextInputClick();
				// 这里可以处理输入数据，例如显示或保存
				/*cout << "输入的数据为: " << inputData << endl;*/
				m.mkLButton = false;
				break;
			}
			if (scanButton.MouseLeft&& mx >= scanButton.x && mx <= (scanButton.x + scanButton.width) &&
				my >= scanButton.y && my <= (scanButton.y + scanButton.height)) {
				
				PngName = scanButton.handleClick();
				closegraph();
				Put_in_cin(stringToTh(GetQRFromImage(PngName)));		//识别完二维码入库
				Sleep(300);
				/*cout << PngName << endl;*/
				m.mkLButton = false;
				//这边有一个bug，不敢乱动了   修好了已经
				
				break;
			}
			if (backButton.MouseLeft && mx >= backButton.x && mx <= (backButton.x + backButton.width) &&
				my >= backButton.y && my <= (backButton.y + backButton.height)) {
				m.mkLButton = false;
				break;
			}
			
		}
		
	}
	
	//返回主菜单
	Inventory_GUI();
	/*while (1);*/
	// 关闭图形界面
	closegraph();
}


//按耗材唯一ID出库
void ByID()
{
	initWindow(1920, 1080);
	
	//2个按钮
	Button Invent[2];
	int buttonHeight = 80;
	int buttonWidth = 200;
	int buttonTop = 100;
	int buttonLeft = (640 - buttonWidth) / 2;
	//设置按钮的名字
	string button_name[2] = { "点我输入id再回车出库唯一id耗材","返回"};

	for (int i = 0; i < 2; ++i) {
		Invent[i] = { buttonLeft, buttonTop + i * (buttonHeight + 20), buttonWidth, buttonHeight, button_name[i] };
	}

	// 绘制按钮
	for (Button& btn : Invent) {
		btn.draw();
	}
	bool back = false;
	string uid;
	while (1) {
		// 检测鼠标点击事件
		if (MouseHit()) { // 检测是否有鼠标事件发生
			MOUSEMSG m = GetMouseMsg(); // 获取鼠标事件信息
			int mx = m.x; // 鼠标x坐标
			int my = m.y; // 鼠标y坐标
			for (Button& btn : Invent) { btn.MouseLeft = m.mkLButton; }	//获取鼠标左键
			// 检查鼠标点击是否在某个按钮上
			for (Button& btn : Invent) {
				if (mx >= btn.x && mx <= btn.x + btn.width && my >= btn.y && my <= btn.y + btn.height && btn.MouseLeft) {
					outtextxy(500,150,"输入待查询id:");
					if (btn.text == button_name[0]) {	//点我输入id再回车删除耗材
						uid=btn.getInputField(500, 180, 200).getInput();
						createQRCodeImage(ThToString(search_Info(uid)->next).c_str(),"OutQRCODE\\"+uid+".png");		//666
						//根据id调用函数查询数据
						Out_bound(uid);
						outtextxy(500, 180, (LPCTSTR)("已删除id为" + uid + "的耗材").c_str());
					}
					if (btn.text == button_name[1]) {	//返回
						back = true;
					}
				}
			}
			if (back) {
				break;
			}
		}
	}
	Out_GUI();
	// 关闭图形界面
	closegraph();
}

//按耗材名批量出库
void ByAll()
{
	initWindow(1920, 1080);

	//2个按钮
	Button Invent[2];
	int buttonHeight = 80;
	int buttonWidth = 200;
	int buttonTop = 100;
	int buttonLeft = (640 - buttonWidth) / 2;
	//设置按钮的名字
	string button_name[2] = { "点我出库所有耗材","返回" };

	for (int i = 0; i < 2; ++i) {
		Invent[i] = { buttonLeft, buttonTop + i * (buttonHeight + 20), buttonWidth, buttonHeight, button_name[i] };
	}

	// 绘制按钮
	for (Button& btn : Invent) {
		btn.draw();
	}
	bool back = false;
	while (1) {
		// 检测鼠标点击事件
		if (MouseHit()) { // 检测是否有鼠标事件发生
			MOUSEMSG m = GetMouseMsg(); // 获取鼠标事件信息
			int mx = m.x; // 鼠标x坐标
			int my = m.y; // 鼠标y坐标
			for (Button& btn : Invent) { btn.MouseLeft = m.mkLButton; }	//获取鼠标左键
			// 检查鼠标点击是否在某个按钮上
			for (Button& btn : Invent) {
				if (mx >= btn.x && mx <= btn.x + btn.width && my >= btn.y && my <= btn.y + btn.height && btn.MouseLeft) {
					if (btn.text == button_name[0]) {
						del_All();
						/*Save("Cons.data");*/
						outtextxy(500, 180, (LPCTSTR)"已删除所有的耗材");
					}
					if (btn.text == button_name[1]) {	//返回
						back = true;
					}
				}
			}
			if (back) {
				break;
			}
		}
	}
	Out_GUI();
	// 关闭图形界面
	closegraph();

}

//出库界面
void Out_GUI()
{
	// 初始化图形界面
	initWindow(1920, 1080);
	
	//4个按钮
	Button Invent[3];
	int buttonHeight = 80;
	int buttonWidth = 200;
	int buttonTop = 100;
	int buttonLeft = (640 - buttonWidth) / 2;
	//设置按钮的名字
	string button_name[3] = { "按耗材唯一ID出库","出库所有耗材","返回" };

	for (int i = 0; i < 3; ++i) {
		Invent[i] = { buttonLeft, buttonTop + i * (buttonHeight + 20), buttonWidth, buttonHeight, button_name[i] };
	}

	// 绘制按钮
	for (Button& btn : Invent) {
		btn.draw();
	}
	bool back = false;
	while (1) {
		// 检测鼠标点击事件
		if (MouseHit()) { // 检测是否有鼠标事件发生
			MOUSEMSG m = GetMouseMsg(); // 获取鼠标事件信息
			int mx = m.x; // 鼠标x坐标
			int my = m.y; // 鼠标y坐标
			for (Button& btn : Invent) { btn.MouseLeft = m.mkLButton; }	//获取鼠标左键
			// 检查鼠标点击是否在某个按钮上
			for (Button& btn : Invent) {
				if (mx >= btn.x && mx <= btn.x + btn.width && my >= btn.y && my <= btn.y + btn.height && btn.MouseLeft) {
					if (btn.text == button_name[0]) {	//按耗材唯一ID出库
						ByID();
					}
					if (btn.text == button_name[1]) {	//全部出库
						ByAll();
					}
					if (btn.text == button_name[2]) {	//返回
						back = true;
					}
				}
			}
			if (back) {
				break;
			}
		}
	}

	Inventory_GUI();
	// 关闭图形界面
	closegraph();
}



//查询
void Secrch_GUI()
{
	// 初始化图形界面
	initWindow(1920, 1080);

	//2个按钮
	Button Invent[2];
	int buttonHeight = 80;
	int buttonWidth = 200;
	int buttonTop = 100;
	int buttonLeft = (640 - buttonWidth) / 2;
	//设置按钮的名字
	string button_name[2] = { "点击输入id查询","返回" };

	for (int i = 0; i < 2; ++i) {
		Invent[i] = { buttonLeft, buttonTop + i * (buttonHeight + 20), buttonWidth, buttonHeight, button_name[i] };
	}

	// 绘制按钮
	for (Button& btn : Invent) {
		btn.draw();
	}
	
	bool back = false;
	
	
	while (true) {
		// 检测鼠标点击事件
		if (MouseHit()) {
			MOUSEMSG m = GetMouseMsg();
			int mx = m.x;
			int my = m.y;
			bool isLf = m.mkLButton;
			for (Button& btn : Invent) { btn.MouseLeft = m.mkLButton; }	//获取鼠标左键
			for (Button& btn : Invent) {
				if (mx >= btn.x && mx <= btn.x + btn.width && my >= btn.y && my <= btn.y + btn.height && btn.MouseLeft) {
					if (btn.text == button_name[0]) {	//按耗材唯一ID出库
						outtextxy(500, 500, "请输入id");

						string id;
						id= btn.getInputField(500, 500, 200).getInput();
						Th* t = search_Info(id);
						t = t->next;
						if (t != NULL) {
							outtextxy(500, 220, (LPCTSTR)("id:" + t->id + " name:" + t->name + " Input date:" + t->In_date + " Outdate:" + t->Out_date + " User:" + t->uesr).c_str());
						}
						break;
					}
					if (btn.text == button_name[1]) {	//返回
						back = true;
						break;
					}
				}
			}
			if (back) {
				break;
			}
		}
	}
	
	// 关闭图形界面
	closegraph();

	Inventory_GUI();
}



//库存管理界面 包含出库和入库函数
void Inventory_GUI()
{
	//实现 查看当前所有库存，包括按id，按名字，按使用者
	//按id删除，按名字批量删除，按使用者批量删除
	
	// 初始化图形界面
	initWindow(1920, 1080);
	
	//4个按钮
	Button Invent[4];
	int buttonHeight = 80;
	int buttonWidth = 200;
	int buttonTop = 100;
	int buttonLeft = (640 - buttonWidth) / 2;
	//设置按钮的名字
	string button_name[4] = { "入库","出库","查询","返回"};

	for (int i = 0; i < 4; ++i) {
		Invent[i] = { buttonLeft, buttonTop + i * (buttonHeight + 20), buttonWidth, buttonHeight, button_name[i] };
	}

	// 绘制按钮
	for (Button& btn : Invent) {
		btn.draw();
	}
	bool back = false;
	while (1) {
		// 检测鼠标点击事件
		if (MouseHit()) { // 检测是否有鼠标事件发生
			MOUSEMSG m = GetMouseMsg(); // 获取鼠标事件信息
			int mx = m.x; // 鼠标x坐标
			int my = m.y; // 鼠标y坐标
			for (Button& btn : Invent) { btn.MouseLeft = m.mkLButton; }	//获取鼠标左键
			// 检查鼠标点击是否在某个按钮上
			for (Button& btn : Invent) {
				if (mx >= btn.x && mx <= btn.x + btn.width && my >= btn.y && my <= btn.y + btn.height && btn.MouseLeft) {
					if (btn.text == button_name[0]) {	//入库
						Put_in_GUI();
					}
					if (btn.text == button_name[1]) {	//出库 = 删除
						Out_GUI();
					}
					if (btn.text == button_name[2]) {	//查询
						Secrch_GUI();
					}
					if (btn.text == button_name[3]) {
						back = true;
					}
				}
			}
			if (back) {
				break;
			}
		}
	}


	menu();
	// 关闭图形界面
	closegraph();
}

//用户管理界面
void User_GUI()
{
	initWindow(1920, 1080);
	//3个按钮
	Button Invent[3];
	int buttonHeight = 80;
	int buttonWidth = 200;
	int buttonTop = 100;
	int buttonLeft = (640 - buttonWidth) / 2;
	//设置按钮的名字
	string button_name[3] = { "登录","登出","返回"};

	for (int i = 0; i < 3; ++i) {
		Invent[i] = { buttonLeft, buttonTop + i * (buttonHeight + 20), buttonWidth, buttonHeight, button_name[i] };
	}

	// 绘制按钮
	for (Button& btn : Invent) {
		btn.draw();
	}
	bool back = false;
	while (1) {
		// 检测鼠标点击事件
		if (MouseHit()) { // 检测是否有鼠标事件发生
			MOUSEMSG m = GetMouseMsg(); // 获取鼠标事件信息
			int mx = m.x; // 鼠标x坐标
			int my = m.y; // 鼠标y坐标
			for (Button& btn : Invent) { btn.MouseLeft = m.mkLButton; }	//获取鼠标左键
			// 检查鼠标点击是否在某个按钮上
			for (Button& btn : Invent) {
				if (mx >= btn.x && mx <= btn.x + btn.width && my >= btn.y && my <= btn.y + btn.height && btn.MouseLeft) {
					if (btn.text == button_name[0]) {
						outtextxy(500, 180, (LPCTSTR)"输入用户名后回车");
						string username= InputString();
						outtextxy(500, 200, (LPCTSTR)"输入密码后回车");
						string passwd = InputString();
						int t = login(username,passwd);
						if (t == -1) {	//登录失败 账户或密码错误
							outtextxy(500, 250, (LPCTSTR)"登录失败，账户或密码错误，请重新输入");
							Sleep(1000);
							back = true;
							break;
						}
						else if (t == 0) {	//登录成功 为管理员账户
							outtextxy(500, 250, (LPCTSTR)("登录成功，欢迎回来，管理员"+username).c_str());
							Sleep(2000);
							back = true;
							break;
						}
						else if(t == 1){	//登录成功 为普通账户
							outtextxy(500, 250, (LPCTSTR)("登录成功，欢迎访问，用户" + username).c_str());
							Sleep(2000);
							back = true;
							break;
						}

					}
					if (btn.text == button_name[1]) {
						int t=login_out();
						back = true;
						break;
					}

					if (btn.text == button_name[2]) {	//返回
						back = true;
					}
				}
			}
			if (back) {
				break;
			}
		}
	}
	menu();
	// 关闭图形界面
	closegraph();
}

// 从searchAllName()函数获取数据
vector<Th*> GetDataFromFunctionn(const string& name)
{
	vector<Th*> data = searchAllName(name);
	return data;
}

// 从getAllInfo()函数获取数据
vector<Th*> GetDataFromFunction() 
{
	vector<Th*> data = getAllInfo();
	return data;
}

// 打印报表数据
void PrintData(const vector<Th*>& data, int& currentPage, const int pageSize) 
{
	// 计算开始和结束的索引
	int start = (currentPage - 1) * pageSize;
	int end = std::min(start + pageSize, (int)data.size());

	// 清除之前的打印内容
	cleardevice();

	// 设置打印区域
	int printStartY = 100;
	outtextxy(50, printStartY-20, (LPCTSTR)"ID  　 NAME 　  IN_DATE 　　　　OUT_DATE 　　　 USER 　　　  MAXVALUE");
	for (int i = start; i < end; ++i) {
		outtextxy(50, 
			printStartY + i * 20, 
			(LPCTSTR)(data[i]->id+"   　　 "+data[i]->name+"     "+data[i]->In_date+"       　　  "+data[i]->Out_date+"   　　　　 "+data[i]->uesr+"     　　  "+to_string(data[i]->MAX_K)).c_str()
		);
	}

	// 绘制分页按钮
	int buttonHeight = 40;
	int buttonWidth = 100;
	int buttonTop = 20;
	int buttonLeft = 50;

	// 上一页按钮
	if (currentPage > 1) {
		Button prevButton = { buttonLeft, buttonTop, buttonWidth, buttonHeight, "上一页" };
		prevButton.draw();
	}

	// 下一页按钮
	Button nextButton = { buttonLeft + 200, buttonTop, buttonWidth, buttonHeight, "下一页" };
	nextButton.draw();

	// 第一页按钮
	Button firstButton = { buttonLeft + 400, buttonTop, buttonWidth, buttonHeight, "第一页" };
	firstButton.draw();

	// 最后一页按钮
	Button lastButton = { buttonLeft + 600, buttonTop, buttonWidth, buttonHeight, "最后一页" };
	lastButton.draw();

	// 返回按钮
	Button backButton = { buttonLeft + 800, buttonTop, buttonWidth, buttonHeight, "返回" };
	backButton.draw();
}

// 处理分页按钮的点击事件
bool HandlePaginationButtons(int& currentPage, const int pageSize, const int mouseX, const int mouseY,bool islf) {
	int buttonHeight = 40;
	int buttonWidth = 100;
	int buttonTop = 20;
	int buttonLeft = 50;

	// 上一页按钮
	if (mouseY >= buttonTop && mouseY <= buttonTop + buttonHeight && mouseX >= buttonLeft && mouseX <= buttonLeft + buttonWidth&&islf) {
		if (currentPage > 1) {
			--currentPage;
			
		}
		islf = false;
	}

	// 下一页按钮
	if (mouseY >= buttonTop && mouseY <= buttonTop + buttonHeight && mouseX >= buttonLeft + 200 && mouseX <= buttonLeft + 200 + buttonWidth && islf) {
		++currentPage;
		islf = false;
	}

	// 第一页按钮
	if (mouseY >= buttonTop && mouseY <= buttonTop + buttonHeight && mouseX >= buttonLeft + 400 && mouseX <= buttonLeft + 400 + buttonWidth && islf) {
		currentPage = 1;
		islf = false;
	}

	// 最后一页按钮
	if (mouseY >= buttonTop && mouseY <= buttonTop + buttonHeight && mouseX >= buttonLeft + 600 && mouseX <= buttonLeft + 600 + buttonWidth && islf) {
		currentPage = (int)std::ceil((double)GetDataFromFunction().size() / pageSize);
		islf = false;
	}

	// 返回按钮
	if (mouseY >= buttonTop && mouseY <= buttonTop + buttonHeight && mouseX >= buttonLeft + 800 && mouseX <= buttonLeft + 800 + buttonWidth && islf) {
		islf = false;
		return true;;
	}
	return false;
}
//报表打印界面
void Reports_GUI() {
	initWindow(1920, 1080);

	int currentPage = 1;
	int pageSize = 5; // 每页显示5个数据项
	vector<Th*> data = GetDataFromFunction();
	
	while (true) {
		// 检测鼠标点击事件
		if (MouseHit()) {
			MOUSEMSG m = GetMouseMsg();
			int mouseX = m.x;
			int mouseY = m.y;
			bool isLf = m.mkLButton;
			// 处理分页按钮的点击
			if (HandlePaginationButtons(currentPage, pageSize, mouseX, mouseY, isLf)) {
				break;
				
			}
			
			if (isLf) {
				PrintData(data, currentPage, pageSize);
			}
		}
	}
	closegraph();
	menu();
}


//数据备份界面
void Data_GUI()
{
	initWindow(1920, 1080);
	//3个按钮
	Button Invent[3];
	int buttonHeight = 80;
	int buttonWidth = 200;
	int buttonTop = 100;
	int buttonLeft = (640 - buttonWidth) / 2;
	//设置按钮的名字
	string button_name[3] = { "点击备份","保存数据到文件","返回" };

	for (int i = 0; i < 3; ++i) {
		Invent[i] = { buttonLeft, buttonTop + i * (buttonHeight + 20), buttonWidth, buttonHeight, button_name[i] };
	}

	// 绘制按钮
	for (Button& btn : Invent) {
		btn.draw();
	}
	bool back = false;
	while (1) {
		// 检测鼠标点击事件
		if (MouseHit()) { // 检测是否有鼠标事件发生
			MOUSEMSG m = GetMouseMsg(); // 获取鼠标事件信息
			int mx = m.x; // 鼠标x坐标
			int my = m.y; // 鼠标y坐标
			for (Button& btn : Invent) { btn.MouseLeft = m.mkLButton; }	//获取鼠标左键
			// 检查鼠标点击是否在某个按钮上
			for (Button& btn : Invent) {
				if (mx >= btn.x && mx <= btn.x + btn.width && my >= btn.y && my <= btn.y + btn.height && btn.MouseLeft) {
					if (btn.text == button_name[0]) {
						ByUserBackup("Cons.data","Cons.bak");
						outtextxy(500, 180, (LPCTSTR)"已为Cons.data创建名为Cons.bak的备份");
					}
					if (btn.text == button_name[1]) {		//保存信息到当前文件
						if (Save("Cons.data")) {
							outtextxy(500, 220, (LPCTSTR)"已将数据保存至Cons.data");
						}

					}
					if (btn.text == button_name[2]) {	//返回
						back = true;
					}
				}
			}
			if (back) {
				break;
			}
		}
	}
	menu();
	// 关闭图形界面
	closegraph();

}

// 定义一个函数，用于弹出输入窗口并获取用户输入
string InputString() 
{
	// 设置窗口标题
	const char* title = "输入信息";
	// 设置窗口大小
	int width = 300;
	int height = 200;
	// 创建窗口
	initgraph(width, height);
	setbkcolor(RGB(240, 240, 240)); // 设置窗口背景色
	cleardevice(); // 清除设备上下文
	setlinecolor(RGB(0, 0, 0)); // 设置线条颜色
	rectangle(0, 0, width, height); // 绘制窗口边框
	settextstyle(0, 0, "Consolas"); // 设置文本字体
	settextcolor(RGB(0, 0, 0)); // 设置文本颜色
	outtextxy(10, 10, title); // 显示窗口标题
	// 创建一个文本框用于输入
	int inputWidth = width - 20;
	int inputHeight = 30;
	int inputX = 10;
	int inputY = height - inputHeight - 10;
	rectangle(inputX, inputY, inputX + inputWidth, inputY + inputHeight); // 绘制文本框边框
	settextstyle(0, 0, "Consolas");
	settextcolor(RGB(0, 0, 0));
	outtextxy(inputX + 5, inputY + 5, ""); // 提示用户输入
	// 等待用户输入
	std::string inputText;
	while (true) {
		if (_kbhit()) { // 检测是否有键盘输入
			char ch = _getch(); // 获取键盘输入
			if (ch == '\r') { // 如果用户按下回车键
				break;
			}
			else if (ch == '\b') { // 如果用户按下退格键
				if (!inputText.empty()) {
					inputText.pop_back(); // 删除最后一个字符
				}
			}
			else if (ch >= ' ' && ch <= '~') { // 如果输入的是可见字符
				inputText.push_back(ch); // 添加字符到字符串
			}
			// 显示当前输入的文本
			settextcolor(RGB(0, 0, 0));
			outtextxy(inputX + 5, inputY + 5, inputText.c_str()); // 显示输入的文本
		}
		Sleep(10); // 稍作延时，避免CPU占用过高
	}
	// 关闭图形窗口
	closegraph();
	return inputText; // 返回用户输入的字符串
}