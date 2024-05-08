#pragma once
#include "Base.h"

//自动备份函数 每次启动备份一次数据
//返回值为bool，即自动备份成功则返回bool
//接受两个文件名，前面的是需要备份的文件，后一个是备份文件名
bool AutoBackup(const string& BeforeName, const string& AfterName);

//手动备份 用户自行决定是否备份
//和AutoBackup的区别在于，AutoBackup会被载入init()初始化方法当中
bool ByUserBackup(const string& BeforeName, const string& AfterName);