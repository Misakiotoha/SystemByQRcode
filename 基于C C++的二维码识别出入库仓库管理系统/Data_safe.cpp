/*
该函数为数据安全函数
实现了数据的自动和手动备份
备份的数据文件默认名为"Cons.bak"
*/
#include "Base.h"
#include "Inventory_management.h"
#include "Out_bound.h"
#include "Put_in_s.h"

//自动备份函数 每次启动备份一次数据
//返回值为bool，即自动备份成功则返回bool
//接受两个文件名，前面的是需要备份的文件，后一个是备份文件名
bool AutoBackup(const string& BeforeName,const string& AfterName)
{
    std::ifstream source;      // 输入文件流，用于读取原始文件
    std::ofstream backup;      // 输出文件流，用于写入备份文件

    // 打开原始文件
    source.open(BeforeName, std::ios::binary);
    if (!source.is_open()) {
        std::cerr << "无法打开原始文件: " << BeforeName << std::endl;
        return false;
    }

    // 打开备份文件
    backup.open(AfterName, std::ios::binary);
    if (!backup.is_open()) {
        std::cerr << "无法创建备份文件: " << AfterName << std::endl;
        source.close(); // 关闭原始文件
        return false;
    }

    // 读取原始文件内容并写入备份文件
    backup << source.rdbuf(); // 使用 rdbuf() 读取源文件的所有内容并写入备份文件

    // 关闭文件流
    source.close();
    backup.close();
    return false;
}


//手动备份 用户自行决定是否备份
//和上面的区别在于，上面的会被载入init()初始化方法当中
bool ByUserBackup(const string& BeforeName, const string& AfterName)
{
    std::ifstream source;      // 输入文件流，用于读取原始文件
    std::ofstream backup;      // 输出文件流，用于写入备份文件

    // 打开原始文件
    source.open(BeforeName, std::ios::binary);
    if (!source.is_open()) {
        std::cerr << "无法打开原始文件: " << BeforeName << std::endl;
        return false;
    }

    // 打开备份文件
    backup.open(AfterName, std::ios::binary);
    if (!backup.is_open()) {
        std::cerr << "无法创建备份文件: " << AfterName << std::endl;
        source.close(); // 关闭原始文件
        return false;
    }

    // 读取原始文件内容并写入备份文件
    backup << source.rdbuf(); // 使用 rdbuf() 读取源文件的所有内容并写入备份文件

    // 关闭文件流
    source.close();
    backup.close();
    return true;
}