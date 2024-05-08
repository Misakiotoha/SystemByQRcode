/*
本仓库管理系统的核心
负责与底层交互，传参，调用，初始化
负责与上层GUI接口交互，接受参数，调用底层
如果不引入中间层，那么GUI层和底层直接交互会使得GUI层非常复杂，不易修改
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



/*
初始化函数
*/
bool InitAll(Th* h, Th* r)
{
	init(h,r);
	init_bound(h,r);
	Get_in_file("Cons.data");	//从文件当中读入数据
	setAllKC();		//计算出当前所有的库存值

	AutoBackup("Cons.data","Cons.bak");

	return true;
}


/*
与二维码识别的交互
*/
string Info="";
//传入一个路径，底层返回的识别结果，这里调用两个不同的底层，两个底层的精准的不相同
//返回一个string的值，供出库入库使用

//99%
bool GetQRInfoBest(const string& FileLocation)
{

	Info=GetQRFromImage(FileLocation);	//内部有处理路径为空的异常处理
	return true;
}

//90%
bool GetQRInfo(const string& FileLocation)
{
	Info = recognizeQRCode(FileLocation);
	return true;
}

//生成二维码部分
//传入一个const char* data即需要生成的信息, 生成一个文件路径下的二维码图片string outputPath
// 传入的值为待生成的文件名字
//这边涉及到一个二维码文件管理，这里使用相对路径，放在当前目录QRCODE下面
//返回值为文件路径
//文件名此处对应耗材的唯一id
string CreateQRcode(const char* data, string Filename)
{
	string outputPath = "QRCODE\\"+Filename+".png";	//处理输入的文件名字
	createQRCodeImage(data, outputPath);
	return outputPath;
}



/*
与库存管理的交互，也包括入库和出库
*/




/*
联合库存管理和二维码识别
涉及到map，等高级数据结构
*/



/*
与数据备份的交互
*/
//手动备份 为GUI提供接口
bool ManualBackup(const string& BeforeName, const string& AfterName)
{
	ByUserBackup(BeforeName, AfterName);
	return true;
}


/*
与用户管理的交互
*/

/*
与报表打印的交互
*/




/*
基于以上的交互
提供给上层GUI的一切接口
*/


