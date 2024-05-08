#pragma once

#include "Base.h"

/*
初始化函数
*/
bool InitAll(Th* h, Th* r);


/*
与二维码识别的交互
*/
//传入一个路径，底层返回的识别结果，这里调用两个不同的底层，两个底层的精准的不相同
//返回一个string的值，供出库入库使用

//99%
bool GetQRInfoBest(const string& FileLocation);

//90%
bool GetQRInfo(const string& FileLocation);


//生成二维码部分
//传入一个const char* data即需要生成的信息, 生成一个文件路径下的二维码图片string outputPath
// 传入的值为待生成的文件名字
//这边涉及到一个二维码文件管理，这里使用相对路径，放在当前目录QRCODE下面
//返回值为文件路径
//文件名此处对应耗材的唯一id
string CreateQRcode(const char* data, string Filename);