/*************************************************************************
【文件名】Porter.hpp
【功能模块和目的】定义Porter类，声明文件操作的基本功能
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
#ifndef PORTER_HPP
#define PORTER_HPP

// fstream所属头文件
#include <fstream>
// invalid_argument所属头文件
#include <stdexcept>
// string所属头文件
#include <string>

using namespace std;

/*************************************************************************
【类名】Porter
【功能】定义Porter类，提供文件操作的基本功能
【接口说明】
    默认构造函数
    拷贝构造函数
    赋值运算符
    虚析构函数
    静态：测试文件扩展名是否一致
    静态：测试文件是否存在，若不存在则创建文件
    静态：测试文件是否打开
    静态：测试文件是否关闭
    静态：获取文件扩展名
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
class Porter {
protected:
    //-------------------------------------------------------------------------
    // 受保护的内嵌异常类
    //-------------------------------------------------------------------------
    // 若文件不存在，则抛出该异常
    class FILE_NOT_FOUND : public invalid_argument {
    public:
        FILE_NOT_FOUND(const string& FileName);
    };
    // 若文件类型不支持，则抛出该异常
    class FILE_NOT_SUPPORTED : public invalid_argument {
    public:
        FILE_NOT_SUPPORTED(const string& FileName);
    };
    // 若文件无法打开，则抛出该异常
    class FILE_NOT_AVAILABLE : public invalid_argument {
    public:
        FILE_NOT_AVAILABLE(const string& FileName);
    };
    // 若文件未关闭，则抛出该异常
    class FILE_NOT_CLOSED : public invalid_argument {
    public:
        FILE_NOT_CLOSED(const string& FileName);
    };

protected:
    //-------------------------------------------------------------------------
    // 受保护的必要的构造、拷贝、赋值、析构函数
    //-------------------------------------------------------------------------
    // 默认构造函数
    Porter() = default;
    // 带参构造函数
    Porter(const string& Extension);
    // 禁止调用拷贝构造函数
    Porter(const Porter& Source) = delete;
    // 禁止调用赋值运算符
    Porter& operator=(const Porter& Source) = delete;
    // 虚析构函数
    virtual ~Porter() = default;

public:
    //-------------------------------------------------------------------------
    // 公有非静态成员函数
    //-------------------------------------------------------------------------
    // 测试文件扩展名是否一致
    void FileValid(const string& FileName) const;
    //-------------------------------------------------------------------------
    // 公有静态成员函数
    //-------------------------------------------------------------------------
    // 测试文件是否存在，若不存在则创建文件
    static void CreateFileNotExists(const string& FileName);
    // 测试文件是否能打开
    static void FileAvailable(const string& FileName);
    // 测试文件是否关闭
    static void FileClosed(const string& FileName);
    // 获取文件扩展名
    static string GetExtension(const string& FileName);
    //-------------------------------------------------------------------------
    // 非静态Getter成员
    //-------------------------------------------------------------------------
    // string类常量Extension，存储文件扩展名
    const string& Extension{m_Extension};

private:
    //-------------------------------------------------------------------------
    // 私有数据成员
    //-------------------------------------------------------------------------
    // 字符串常量，存储文件扩展名
    const string m_Extension;
};

#endif /* Porter.hpp */