/*
���cpp����ŵ���GUI���棬ȫ���ǵ��õĵײ㺯��
GUI����EasyX
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
//��ȫ��һ��ʹ�ã�������initgraph�ĵ���������
void initWindow(int w, int h)
{
	// ��ʼ��ͼ�ν���
	initgraph(w, h); // ��ʼ��һ��ȫ������
	setbkcolor(WHITE);
	cleardevice();
	// ���ر���ͼƬ  
	IMAGE img;
	loadimage(&img, _T("background.jpg")); 

	// ��ͼƬ����Ϊ����  
	putimage(0, 0, &img); // �� (0,0) λ����ʾͼƬ�����������ڶ��Ǳ���ͼƬ
	
}

void menu()	//���˵�����
{
	
	initWindow(1920, 1080);
	
	// ����5����ť������
	Button buttons[5];
	int buttonHeight = 80;
	int buttonWidth = 200;
	int buttonTop = 100;
	int buttonLeft = (640 - buttonWidth) / 2;
	//���ð�ť������
	string button_name[5] = { "������","�û�����","�����ӡ" ,"���ݰ�ȫ","�˳�"};

	for (int i = 0; i < 5; ++i) {
		buttons[i] = { buttonLeft, buttonTop + i * (buttonHeight + 20), buttonWidth, buttonHeight, button_name[i]};
	}
	

	// ���ư�ť
	for (Button& btn : buttons) {
		btn.draw();
	}
	map<string, ll> ti = getExceededWarningMapx();
	int temp = 1;
	for (auto k : ti)
	{
		temp++;
		outtextxy(600,400+temp*20,(LPCTSTR)(k.first + "�Ŀ��ֵ�Ѿ�����Ԥ��ֵ"+to_string(k.second)+"���ˣ��뼰ʱ�����������").c_str());
	}
	ti.clear();

	temp = 1;
	ti = getRestockWarning();
	for (auto k : ti)
	{
		temp++;
		outtextxy(600, 200 + temp * 20, (LPCTSTR)(k.first + "�Ŀ��ֵ�Ѿ���������ֵ" + to_string(k.second) + "���ˣ��뼰ʱ���").c_str());
	}
	ti.clear();

	//�û���¼״̬
	if (getUser_State() == -1) {
		outtextxy(900, 100, (LPCTSTR)("��ǰ���û���¼"));
	}
	if (getUser_State() == 0) {
		outtextxy(900, 100, (LPCTSTR)("��ǰΪ����Ա�û�"));
	}
	if (getUser_State() == 1) {
		outtextxy(900, 100, (LPCTSTR)("��ǰΪ��ͨ�û�"));
	}
	bool EXITGUI = true;		//�˳��ı�־λ
	
	// ��ѭ��
	while (true) {
		// ���������¼�
		if (MouseHit()) { // ����Ƿ�������¼�����
			MOUSEMSG m = GetMouseMsg(); // ��ȡ����¼���Ϣ
			int mx = m.x; // ���x����
			int my = m.y; // ���y����
			for (Button& btn : buttons) { btn.MouseLeft = m.mkLButton; }	//��ȡ������
			// ���������Ƿ���ĳ����ť��
			for (Button& btn : buttons) {
				if (mx >= btn.x && mx <= btn.x + btn.width && my >= btn.y && my <= btn.y + btn.height&&btn.MouseLeft) {
					if (btn.text == button_name[0] && getUser_State() == 0) {	//������
						Inventory_GUI();
					}
					if (btn.text == button_name[1]) {	//�û�����
						User_GUI();
					}
					if (btn.text == button_name[2]&&(getUser_State()==1|| getUser_State() == 0)) {	//�����ӡ
						Reports_GUI();
					}
					if (btn.text == button_name[3]&&getUser_State() == 0) {	//���ݰ�ȫ
						Data_GUI();
					}
					//�˳��¼�
					if (btn.text == button_name[4]) {		//�˳�
						EXITGUI = false;
					}
				}
			}
		}

		if (!EXITGUI) { // 
			break; // 
		}
	}

	// �ر�ͼ�ν���
	closegraph();

}



//����ֶ��������
string TextInput()
{
	// ��ʼ��ͼ�ν���
	initWindow(1920, 1080);
	string inputData="";
	
	// ������ť����
	Button manualEntryButton = { 100, 100, 100, 50, "�������" };
	manualEntryButton.setBounds(100, 100, 100, 50);
	
	// ���ư�ť
	manualEntryButton.draw();
	
	// ��Ϣ����ѭ��
	while (true) {
		// ���������¼�
		if (MouseHit()) {
			MOUSEMSG m = GetMouseMsg(); // ��ȡ����¼���Ϣ
			int mx = m.x; // ���x����
			int my = m.y; // ���y����
			manualEntryButton.MouseLeft = m.mkLButton;
			if (manualEntryButton.MouseLeft&& mx >= manualEntryButton.x && mx <= (manualEntryButton.x + 
				manualEntryButton.width) &&
				my >= manualEntryButton.y && my <= (manualEntryButton.y + 
				manualEntryButton.height)) {// ����˰�ť��ִ�е���¼�
				
				inputData = manualEntryButton.TextInputClick();
				Put_in_cin(stringToTh(inputData));
				// ������Դ����������ݣ�������ʾ�򱣴�
				/*cout << "���������Ϊ: " << inputData << endl;*/
				
				break;//�˳�ѭ������ֹ��δ�GUI
			}
		}
		
	}
	Put_in_GUI();	//����ͷ�����һ��GUI
	closegraph(); // �ر�ͼ�ν���
	return inputData;
}

//������
void Put_in_GUI()
{
	// ��ʼ��ͼ�ν���
	initWindow(1920, 1080);
	// ���尴ť
	Button manualButton;
	manualButton.setBounds(300, 250, 200, 60);
	manualButton.text = "�ֶ��������";

	Button scanButton;
	scanButton.setBounds(300, 350, 200, 60);
	scanButton.text = "ɨ�����";

	Button backButton;
	backButton.setBounds(300, 450, 200, 60);
	backButton.text = "����";

	// ���ư�ť
	manualButton.draw();
	scanButton.draw();
	backButton.draw();

	string PngName="";	//Ĭ��Ϊ���ַ���
	// ��ѭ��
	while (true) {
		// ���������¼�
		if (MouseHit()) {
			MOUSEMSG m = GetMouseMsg(); // ��ȡ����¼���Ϣ
			int mx = m.x; // ���x����
			int my = m.y; // ���y����
			manualButton.MouseLeft = m.mkLButton;
			scanButton.MouseLeft = m.mkLButton;	//�������Ƿ񱻰���
			backButton.MouseLeft = m.mkLButton;

			if (manualButton.MouseLeft&& mx >= manualButton.x && mx <= (manualButton.x + manualButton.width) &&
				my >= manualButton.y && my <= (manualButton.y + manualButton.height)) {
				closegraph();
				TextInput();
				string inputData = manualButton.TextInputClick();
				// ������Դ����������ݣ�������ʾ�򱣴�
				/*cout << "���������Ϊ: " << inputData << endl;*/
				m.mkLButton = false;
				break;
			}
			if (scanButton.MouseLeft&& mx >= scanButton.x && mx <= (scanButton.x + scanButton.width) &&
				my >= scanButton.y && my <= (scanButton.y + scanButton.height)) {
				
				PngName = scanButton.handleClick();
				closegraph();
				Put_in_cin(stringToTh(GetQRFromImage(PngName)));		//ʶ�����ά�����
				Sleep(300);
				/*cout << PngName << endl;*/
				m.mkLButton = false;
				//�����һ��bug�������Ҷ���   �޺����Ѿ�
				
				break;
			}
			if (backButton.MouseLeft && mx >= backButton.x && mx <= (backButton.x + backButton.width) &&
				my >= backButton.y && my <= (backButton.y + backButton.height)) {
				m.mkLButton = false;
				break;
			}
			
		}
		
	}
	
	//�������˵�
	Inventory_GUI();
	/*while (1);*/
	// �ر�ͼ�ν���
	closegraph();
}


//���Ĳ�ΨһID����
void ByID()
{
	initWindow(1920, 1080);
	
	//2����ť
	Button Invent[2];
	int buttonHeight = 80;
	int buttonWidth = 200;
	int buttonTop = 100;
	int buttonLeft = (640 - buttonWidth) / 2;
	//���ð�ť������
	string button_name[2] = { "��������id�ٻس�����Ψһid�Ĳ�","����"};

	for (int i = 0; i < 2; ++i) {
		Invent[i] = { buttonLeft, buttonTop + i * (buttonHeight + 20), buttonWidth, buttonHeight, button_name[i] };
	}

	// ���ư�ť
	for (Button& btn : Invent) {
		btn.draw();
	}
	bool back = false;
	string uid;
	while (1) {
		// ���������¼�
		if (MouseHit()) { // ����Ƿ�������¼�����
			MOUSEMSG m = GetMouseMsg(); // ��ȡ����¼���Ϣ
			int mx = m.x; // ���x����
			int my = m.y; // ���y����
			for (Button& btn : Invent) { btn.MouseLeft = m.mkLButton; }	//��ȡ������
			// ���������Ƿ���ĳ����ť��
			for (Button& btn : Invent) {
				if (mx >= btn.x && mx <= btn.x + btn.width && my >= btn.y && my <= btn.y + btn.height && btn.MouseLeft) {
					outtextxy(500,150,"�������ѯid:");
					if (btn.text == button_name[0]) {	//��������id�ٻس�ɾ���Ĳ�
						uid=btn.getInputField(500, 180, 200).getInput();
						createQRCodeImage(ThToString(search_Info(uid)->next).c_str(),"OutQRCODE\\"+uid+".png");		//666
						//����id���ú�����ѯ����
						Out_bound(uid);
						outtextxy(500, 180, (LPCTSTR)("��ɾ��idΪ" + uid + "�ĺĲ�").c_str());
					}
					if (btn.text == button_name[1]) {	//����
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
	// �ر�ͼ�ν���
	closegraph();
}

//���Ĳ�����������
void ByAll()
{
	initWindow(1920, 1080);

	//2����ť
	Button Invent[2];
	int buttonHeight = 80;
	int buttonWidth = 200;
	int buttonTop = 100;
	int buttonLeft = (640 - buttonWidth) / 2;
	//���ð�ť������
	string button_name[2] = { "���ҳ������кĲ�","����" };

	for (int i = 0; i < 2; ++i) {
		Invent[i] = { buttonLeft, buttonTop + i * (buttonHeight + 20), buttonWidth, buttonHeight, button_name[i] };
	}

	// ���ư�ť
	for (Button& btn : Invent) {
		btn.draw();
	}
	bool back = false;
	while (1) {
		// ���������¼�
		if (MouseHit()) { // ����Ƿ�������¼�����
			MOUSEMSG m = GetMouseMsg(); // ��ȡ����¼���Ϣ
			int mx = m.x; // ���x����
			int my = m.y; // ���y����
			for (Button& btn : Invent) { btn.MouseLeft = m.mkLButton; }	//��ȡ������
			// ���������Ƿ���ĳ����ť��
			for (Button& btn : Invent) {
				if (mx >= btn.x && mx <= btn.x + btn.width && my >= btn.y && my <= btn.y + btn.height && btn.MouseLeft) {
					if (btn.text == button_name[0]) {
						del_All();
						/*Save("Cons.data");*/
						outtextxy(500, 180, (LPCTSTR)"��ɾ�����еĺĲ�");
					}
					if (btn.text == button_name[1]) {	//����
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
	// �ر�ͼ�ν���
	closegraph();

}

//�������
void Out_GUI()
{
	// ��ʼ��ͼ�ν���
	initWindow(1920, 1080);
	
	//4����ť
	Button Invent[3];
	int buttonHeight = 80;
	int buttonWidth = 200;
	int buttonTop = 100;
	int buttonLeft = (640 - buttonWidth) / 2;
	//���ð�ť������
	string button_name[3] = { "���Ĳ�ΨһID����","�������кĲ�","����" };

	for (int i = 0; i < 3; ++i) {
		Invent[i] = { buttonLeft, buttonTop + i * (buttonHeight + 20), buttonWidth, buttonHeight, button_name[i] };
	}

	// ���ư�ť
	for (Button& btn : Invent) {
		btn.draw();
	}
	bool back = false;
	while (1) {
		// ���������¼�
		if (MouseHit()) { // ����Ƿ�������¼�����
			MOUSEMSG m = GetMouseMsg(); // ��ȡ����¼���Ϣ
			int mx = m.x; // ���x����
			int my = m.y; // ���y����
			for (Button& btn : Invent) { btn.MouseLeft = m.mkLButton; }	//��ȡ������
			// ���������Ƿ���ĳ����ť��
			for (Button& btn : Invent) {
				if (mx >= btn.x && mx <= btn.x + btn.width && my >= btn.y && my <= btn.y + btn.height && btn.MouseLeft) {
					if (btn.text == button_name[0]) {	//���Ĳ�ΨһID����
						ByID();
					}
					if (btn.text == button_name[1]) {	//ȫ������
						ByAll();
					}
					if (btn.text == button_name[2]) {	//����
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
	// �ر�ͼ�ν���
	closegraph();
}



//��ѯ
void Secrch_GUI()
{
	// ��ʼ��ͼ�ν���
	initWindow(1920, 1080);

	//2����ť
	Button Invent[2];
	int buttonHeight = 80;
	int buttonWidth = 200;
	int buttonTop = 100;
	int buttonLeft = (640 - buttonWidth) / 2;
	//���ð�ť������
	string button_name[2] = { "�������id��ѯ","����" };

	for (int i = 0; i < 2; ++i) {
		Invent[i] = { buttonLeft, buttonTop + i * (buttonHeight + 20), buttonWidth, buttonHeight, button_name[i] };
	}

	// ���ư�ť
	for (Button& btn : Invent) {
		btn.draw();
	}
	
	bool back = false;
	
	
	while (true) {
		// ���������¼�
		if (MouseHit()) {
			MOUSEMSG m = GetMouseMsg();
			int mx = m.x;
			int my = m.y;
			bool isLf = m.mkLButton;
			for (Button& btn : Invent) { btn.MouseLeft = m.mkLButton; }	//��ȡ������
			for (Button& btn : Invent) {
				if (mx >= btn.x && mx <= btn.x + btn.width && my >= btn.y && my <= btn.y + btn.height && btn.MouseLeft) {
					if (btn.text == button_name[0]) {	//���Ĳ�ΨһID����
						outtextxy(500, 500, "������id");

						string id;
						id= btn.getInputField(500, 500, 200).getInput();
						Th* t = search_Info(id);
						t = t->next;
						if (t != NULL) {
							outtextxy(500, 220, (LPCTSTR)("id:" + t->id + " name:" + t->name + " Input date:" + t->In_date + " Outdate:" + t->Out_date + " User:" + t->uesr).c_str());
						}
						break;
					}
					if (btn.text == button_name[1]) {	//����
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
	
	// �ر�ͼ�ν���
	closegraph();

	Inventory_GUI();
}



//��������� �����������⺯��
void Inventory_GUI()
{
	//ʵ�� �鿴��ǰ���п�棬������id�������֣���ʹ����
	//��idɾ��������������ɾ������ʹ��������ɾ��
	
	// ��ʼ��ͼ�ν���
	initWindow(1920, 1080);
	
	//4����ť
	Button Invent[4];
	int buttonHeight = 80;
	int buttonWidth = 200;
	int buttonTop = 100;
	int buttonLeft = (640 - buttonWidth) / 2;
	//���ð�ť������
	string button_name[4] = { "���","����","��ѯ","����"};

	for (int i = 0; i < 4; ++i) {
		Invent[i] = { buttonLeft, buttonTop + i * (buttonHeight + 20), buttonWidth, buttonHeight, button_name[i] };
	}

	// ���ư�ť
	for (Button& btn : Invent) {
		btn.draw();
	}
	bool back = false;
	while (1) {
		// ���������¼�
		if (MouseHit()) { // ����Ƿ�������¼�����
			MOUSEMSG m = GetMouseMsg(); // ��ȡ����¼���Ϣ
			int mx = m.x; // ���x����
			int my = m.y; // ���y����
			for (Button& btn : Invent) { btn.MouseLeft = m.mkLButton; }	//��ȡ������
			// ���������Ƿ���ĳ����ť��
			for (Button& btn : Invent) {
				if (mx >= btn.x && mx <= btn.x + btn.width && my >= btn.y && my <= btn.y + btn.height && btn.MouseLeft) {
					if (btn.text == button_name[0]) {	//���
						Put_in_GUI();
					}
					if (btn.text == button_name[1]) {	//���� = ɾ��
						Out_GUI();
					}
					if (btn.text == button_name[2]) {	//��ѯ
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
	// �ر�ͼ�ν���
	closegraph();
}

//�û��������
void User_GUI()
{
	initWindow(1920, 1080);
	//3����ť
	Button Invent[3];
	int buttonHeight = 80;
	int buttonWidth = 200;
	int buttonTop = 100;
	int buttonLeft = (640 - buttonWidth) / 2;
	//���ð�ť������
	string button_name[3] = { "��¼","�ǳ�","����"};

	for (int i = 0; i < 3; ++i) {
		Invent[i] = { buttonLeft, buttonTop + i * (buttonHeight + 20), buttonWidth, buttonHeight, button_name[i] };
	}

	// ���ư�ť
	for (Button& btn : Invent) {
		btn.draw();
	}
	bool back = false;
	while (1) {
		// ���������¼�
		if (MouseHit()) { // ����Ƿ�������¼�����
			MOUSEMSG m = GetMouseMsg(); // ��ȡ����¼���Ϣ
			int mx = m.x; // ���x����
			int my = m.y; // ���y����
			for (Button& btn : Invent) { btn.MouseLeft = m.mkLButton; }	//��ȡ������
			// ���������Ƿ���ĳ����ť��
			for (Button& btn : Invent) {
				if (mx >= btn.x && mx <= btn.x + btn.width && my >= btn.y && my <= btn.y + btn.height && btn.MouseLeft) {
					if (btn.text == button_name[0]) {
						outtextxy(500, 180, (LPCTSTR)"�����û�����س�");
						string username= InputString();
						outtextxy(500, 200, (LPCTSTR)"���������س�");
						string passwd = InputString();
						int t = login(username,passwd);
						if (t == -1) {	//��¼ʧ�� �˻����������
							outtextxy(500, 250, (LPCTSTR)"��¼ʧ�ܣ��˻��������������������");
							Sleep(1000);
							back = true;
							break;
						}
						else if (t == 0) {	//��¼�ɹ� Ϊ����Ա�˻�
							outtextxy(500, 250, (LPCTSTR)("��¼�ɹ�����ӭ����������Ա"+username).c_str());
							Sleep(2000);
							back = true;
							break;
						}
						else if(t == 1){	//��¼�ɹ� Ϊ��ͨ�˻�
							outtextxy(500, 250, (LPCTSTR)("��¼�ɹ�����ӭ���ʣ��û�" + username).c_str());
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

					if (btn.text == button_name[2]) {	//����
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
	// �ر�ͼ�ν���
	closegraph();
}

// ��searchAllName()������ȡ����
vector<Th*> GetDataFromFunctionn(const string& name)
{
	vector<Th*> data = searchAllName(name);
	return data;
}

// ��getAllInfo()������ȡ����
vector<Th*> GetDataFromFunction() 
{
	vector<Th*> data = getAllInfo();
	return data;
}

// ��ӡ��������
void PrintData(const vector<Th*>& data, int& currentPage, const int pageSize) 
{
	// ���㿪ʼ�ͽ���������
	int start = (currentPage - 1) * pageSize;
	int end = std::min(start + pageSize, (int)data.size());

	// ���֮ǰ�Ĵ�ӡ����
	cleardevice();

	// ���ô�ӡ����
	int printStartY = 100;
	outtextxy(50, printStartY-20, (LPCTSTR)"ID  �� NAME ��  IN_DATE ��������OUT_DATE ������ USER ������  MAXVALUE");
	for (int i = start; i < end; ++i) {
		outtextxy(50, 
			printStartY + i * 20, 
			(LPCTSTR)(data[i]->id+"   ���� "+data[i]->name+"     "+data[i]->In_date+"       ����  "+data[i]->Out_date+"   �������� "+data[i]->uesr+"     ����  "+to_string(data[i]->MAX_K)).c_str()
		);
	}

	// ���Ʒ�ҳ��ť
	int buttonHeight = 40;
	int buttonWidth = 100;
	int buttonTop = 20;
	int buttonLeft = 50;

	// ��һҳ��ť
	if (currentPage > 1) {
		Button prevButton = { buttonLeft, buttonTop, buttonWidth, buttonHeight, "��һҳ" };
		prevButton.draw();
	}

	// ��һҳ��ť
	Button nextButton = { buttonLeft + 200, buttonTop, buttonWidth, buttonHeight, "��һҳ" };
	nextButton.draw();

	// ��һҳ��ť
	Button firstButton = { buttonLeft + 400, buttonTop, buttonWidth, buttonHeight, "��һҳ" };
	firstButton.draw();

	// ���һҳ��ť
	Button lastButton = { buttonLeft + 600, buttonTop, buttonWidth, buttonHeight, "���һҳ" };
	lastButton.draw();

	// ���ذ�ť
	Button backButton = { buttonLeft + 800, buttonTop, buttonWidth, buttonHeight, "����" };
	backButton.draw();
}

// �����ҳ��ť�ĵ���¼�
bool HandlePaginationButtons(int& currentPage, const int pageSize, const int mouseX, const int mouseY,bool islf) {
	int buttonHeight = 40;
	int buttonWidth = 100;
	int buttonTop = 20;
	int buttonLeft = 50;

	// ��һҳ��ť
	if (mouseY >= buttonTop && mouseY <= buttonTop + buttonHeight && mouseX >= buttonLeft && mouseX <= buttonLeft + buttonWidth&&islf) {
		if (currentPage > 1) {
			--currentPage;
			
		}
		islf = false;
	}

	// ��һҳ��ť
	if (mouseY >= buttonTop && mouseY <= buttonTop + buttonHeight && mouseX >= buttonLeft + 200 && mouseX <= buttonLeft + 200 + buttonWidth && islf) {
		++currentPage;
		islf = false;
	}

	// ��һҳ��ť
	if (mouseY >= buttonTop && mouseY <= buttonTop + buttonHeight && mouseX >= buttonLeft + 400 && mouseX <= buttonLeft + 400 + buttonWidth && islf) {
		currentPage = 1;
		islf = false;
	}

	// ���һҳ��ť
	if (mouseY >= buttonTop && mouseY <= buttonTop + buttonHeight && mouseX >= buttonLeft + 600 && mouseX <= buttonLeft + 600 + buttonWidth && islf) {
		currentPage = (int)std::ceil((double)GetDataFromFunction().size() / pageSize);
		islf = false;
	}

	// ���ذ�ť
	if (mouseY >= buttonTop && mouseY <= buttonTop + buttonHeight && mouseX >= buttonLeft + 800 && mouseX <= buttonLeft + 800 + buttonWidth && islf) {
		islf = false;
		return true;;
	}
	return false;
}
//�����ӡ����
void Reports_GUI() {
	initWindow(1920, 1080);

	int currentPage = 1;
	int pageSize = 5; // ÿҳ��ʾ5��������
	vector<Th*> data = GetDataFromFunction();
	
	while (true) {
		// ���������¼�
		if (MouseHit()) {
			MOUSEMSG m = GetMouseMsg();
			int mouseX = m.x;
			int mouseY = m.y;
			bool isLf = m.mkLButton;
			// �����ҳ��ť�ĵ��
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


//���ݱ��ݽ���
void Data_GUI()
{
	initWindow(1920, 1080);
	//3����ť
	Button Invent[3];
	int buttonHeight = 80;
	int buttonWidth = 200;
	int buttonTop = 100;
	int buttonLeft = (640 - buttonWidth) / 2;
	//���ð�ť������
	string button_name[3] = { "�������","�������ݵ��ļ�","����" };

	for (int i = 0; i < 3; ++i) {
		Invent[i] = { buttonLeft, buttonTop + i * (buttonHeight + 20), buttonWidth, buttonHeight, button_name[i] };
	}

	// ���ư�ť
	for (Button& btn : Invent) {
		btn.draw();
	}
	bool back = false;
	while (1) {
		// ���������¼�
		if (MouseHit()) { // ����Ƿ�������¼�����
			MOUSEMSG m = GetMouseMsg(); // ��ȡ����¼���Ϣ
			int mx = m.x; // ���x����
			int my = m.y; // ���y����
			for (Button& btn : Invent) { btn.MouseLeft = m.mkLButton; }	//��ȡ������
			// ���������Ƿ���ĳ����ť��
			for (Button& btn : Invent) {
				if (mx >= btn.x && mx <= btn.x + btn.width && my >= btn.y && my <= btn.y + btn.height && btn.MouseLeft) {
					if (btn.text == button_name[0]) {
						ByUserBackup("Cons.data","Cons.bak");
						outtextxy(500, 180, (LPCTSTR)"��ΪCons.data������ΪCons.bak�ı���");
					}
					if (btn.text == button_name[1]) {		//������Ϣ����ǰ�ļ�
						if (Save("Cons.data")) {
							outtextxy(500, 220, (LPCTSTR)"�ѽ����ݱ�����Cons.data");
						}

					}
					if (btn.text == button_name[2]) {	//����
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
	// �ر�ͼ�ν���
	closegraph();

}

// ����һ�����������ڵ������봰�ڲ���ȡ�û�����
string InputString() 
{
	// ���ô��ڱ���
	const char* title = "������Ϣ";
	// ���ô��ڴ�С
	int width = 300;
	int height = 200;
	// ��������
	initgraph(width, height);
	setbkcolor(RGB(240, 240, 240)); // ���ô��ڱ���ɫ
	cleardevice(); // ����豸������
	setlinecolor(RGB(0, 0, 0)); // ����������ɫ
	rectangle(0, 0, width, height); // ���ƴ��ڱ߿�
	settextstyle(0, 0, "Consolas"); // �����ı�����
	settextcolor(RGB(0, 0, 0)); // �����ı���ɫ
	outtextxy(10, 10, title); // ��ʾ���ڱ���
	// ����һ���ı�����������
	int inputWidth = width - 20;
	int inputHeight = 30;
	int inputX = 10;
	int inputY = height - inputHeight - 10;
	rectangle(inputX, inputY, inputX + inputWidth, inputY + inputHeight); // �����ı���߿�
	settextstyle(0, 0, "Consolas");
	settextcolor(RGB(0, 0, 0));
	outtextxy(inputX + 5, inputY + 5, ""); // ��ʾ�û�����
	// �ȴ��û�����
	std::string inputText;
	while (true) {
		if (_kbhit()) { // ����Ƿ��м�������
			char ch = _getch(); // ��ȡ��������
			if (ch == '\r') { // ����û����»س���
				break;
			}
			else if (ch == '\b') { // ����û������˸��
				if (!inputText.empty()) {
					inputText.pop_back(); // ɾ�����һ���ַ�
				}
			}
			else if (ch >= ' ' && ch <= '~') { // ���������ǿɼ��ַ�
				inputText.push_back(ch); // ����ַ����ַ���
			}
			// ��ʾ��ǰ������ı�
			settextcolor(RGB(0, 0, 0));
			outtextxy(inputX + 5, inputY + 5, inputText.c_str()); // ��ʾ������ı�
		}
		Sleep(10); // ������ʱ������CPUռ�ù���
	}
	// �ر�ͼ�δ���
	closegraph();
	return inputText; // �����û�������ַ���
}