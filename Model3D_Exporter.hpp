/*************************************************************************
【文件名】Model3D_Exporter.hpp
【功能模块和目的】定义Model3D_Exporter类，继承自Porter类，表示三维模型的导出器
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
#ifndef EXPORTER_HPP
#define EXPORTER_HPP

// Model3D所属头文件
#include "Model3D.hpp"
// Porter所属头文件
#include "Porter.hpp"
// fstream所属头文件
#include <fstream>
// string所属头文件
#include <string>

/*************************************************************************
【类名】Model3D_Exporter
【功能】定义Model3D_Exporter类，继承自Porter类，表示三维模型的导出器
【接口说明】
    默认构造函数
    带参构造函数
    拷贝构造函数
    重载赋值运算符
    虚析构函数
    保存三维模型到文件
    保存三维模型到流
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/

class Model3D_Exporter : public Porter {
protected:
    //-------------------------------------------------------------------------
    // 受保护的必要的构造、析构、拷贝、赋值运算符重载函数
    //-------------------------------------------------------------------------
    // 默认构造函数
    Model3D_Exporter() = default;
    // 带参构造函数
    Model3D_Exporter(const string& FileName);
    // 拷贝构造函数
    Model3D_Exporter(const Model3D_Exporter& Source) = delete;
    // 赋值运算符
    Model3D_Exporter& operator=(const Model3D_Exporter& Source) = delete;
    // 析构函数
    virtual ~Model3D_Exporter() = default;

public:
    //-------------------------------------------------------------------------
    // 非静态Getter成员函数
    //-------------------------------------------------------------------------
    // 保存三维模型到文件
    void SaveToFile(const string& FileName, const Model3D& AModel);
    // 保存三维模型到流（纯虚函数，由派生类具体实现不同文件的导出）
    virtual void SaveToStream(
        ofstream& Stream, const Model3D& AModel) const = 0;
};

#endif /* Exporter.hpp */