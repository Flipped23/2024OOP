/*************************************************************************
【文件名】Porter.cpp
【功能模块和目的】定义Porter类，定义文件操作的基本功能
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/

// Porter类头文件
#include "Porter.hpp"
// ifstream, ofstream所属头文件
#include <fstream>
// invalid_argument所属头文件
#include <stdexcept>
// string所属头文件
#include <string>
// sstream所属头文件
#include <sstream>

using namespace std;

//-------------------------------------------------------------------------
// 受保护的内嵌异常类
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】FILE_NOT_FOUND
【函数功能】内嵌异常类构造函数，若文件不存在，则抛出该异常
【参数】const string& FileName，文件名
【返回值】无
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
Porter::FILE_NOT_FOUND::FILE_NOT_FOUND(const string& FileName)
    : invalid_argument(string("File") + FileName + string("not found.")) {
    }
/*************************************************************************
【函数名称】FILE_NOT_SUPPORTED
【函数功能】内嵌异常类构造函数，若文件类型不支持，则抛出该异常
【参数】const string& FileName，文件名
【返回值】无
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
Porter::FILE_NOT_SUPPORTED::FILE_NOT_SUPPORTED(const string& FileName)
    : invalid_argument(string("File") + FileName
    + string("is not supported type.")) {
    }
/*************************************************************************
【函数名称】FILE_NOT_AVAILABLE
【函数功能】内嵌异常类构造函数，若文件未打开，则抛出该异常
【参数】const string& FileName，文件名
【返回值】无
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
Porter::FILE_NOT_AVAILABLE::FILE_NOT_AVAILABLE(const string& FileName)
    : invalid_argument(string("File") + FileName + string("not opened.")) {
    }
/*************************************************************************
【函数名称】FILE_NOT_CLOSED
【函数功能】内嵌异常类构造函数，若文件未关闭，则抛出该异常
【参数】const string& FileName，文件名
【返回值】无
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
Porter::FILE_NOT_CLOSED::FILE_NOT_CLOSED(const string& FileName)
    : invalid_argument(string("File") + FileName + string("not closed.")) {
    }

//-------------------------------------------------------------------------
// 受保护的必要的构造、拷贝、赋值、析构函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】Porter
【函数功能】带参构造函数
【参数】const string& FileName，文件名
【返回值】无
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
Porter::Porter(const string& Extension) : m_Extension(Extension) {
}
/*************************************************************************
【函数名称】FileValid
【函数功能】测试文件扩展名是否一致
【参数】const string& FileName，文件名
        const string& Extension，文件扩展名
【返回值】无
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
void Porter::FileValid(const string& FileName) const {
    // 测试文件扩展名是否一致，若不一致则抛出异常
    if (GetExtension(FileName) != m_Extension) {
        throw FILE_NOT_SUPPORTED(FileName);
    }
}
/*************************************************************************
【函数名称】CreateFileNotExists
【函数功能】测试文件是否存在，若不存在则创建文件
【参数】const string& FileName，文件名
【返回值】无
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
void Porter::CreateFileNotExists(const string& FileName) {
    ifstream infile(FileName);
    // 文件不存在则创建文件
    if (!infile.good()) {
        // 创建文件
        ofstream outfile(FileName);
        // 若文件创建失败，则抛出异常
        if (outfile.is_open()) {
            outfile.close();
        } 
        else {
            throw FILE_NOT_AVAILABLE(FileName);
        }
    }
}
/*************************************************************************
【函数名称】FileOpened
【函数功能】测试文件是否能打开
【参数】const string& FileName，文件名
【返回值】无
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
void Porter::FileAvailable(const string& FileName) {
    // 测试文件是否打开，若未打开则抛出异常
    ifstream File(FileName);
    if (!File.is_open()) {
        throw FILE_NOT_AVAILABLE(FileName);
    }
    File.close();
}
/*************************************************************************
【函数名称】FileClosed
【函数功能】测试文件是否关闭
【参数】const string& FileName，文件名
【返回值】无
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
void Porter::FileClosed(const string& FileName) {
    // 测试文件是否关闭，若未关闭则抛出异常
    ifstream File(FileName);
    if (File.is_open()) {
        throw FILE_NOT_CLOSED(FileName);
    }
}
/*************************************************************************
【函数名称】GetExtension
【函数功能】获取文件扩展名
【参数】const string& FileName，文件名
【返回值】无
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
string Porter::GetExtension(const string& FileName) {
    string result;
    size_t Pos = FileName.find_last_of('.');
    // 若文件名中不包含'.'，则抛出异常
    if (Pos == string::npos) {
        throw FILE_NOT_SUPPORTED(FileName);
    }
    // 获取文件扩展名
    result = FileName.substr(Pos + 1);
    return result;
}