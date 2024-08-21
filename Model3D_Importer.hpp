/*************************************************************************
【文件名】Model3D_Importer.hpp
【功能模块和目的】定义Model3D_Importer类，继承自Porter类，表示三维模型的导入器
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
#ifndef IMPORTER_HPP
#define IMPORTER_HPP

// Model3D所属头文件
#include "Model3D.hpp"
// Porter所属头文件
#include "Porter.hpp"
// fstream所属头文件
#include <fstream>

using namespace std;

/*************************************************************************
【类名】Model3D_Importer
【功能】定义Model3D_Importer类，继承自Porter类，表示三维模型的导入器
【接口说明】
    默认构造函数
    带参构造函数
    拷贝构造函数
    重载赋值运算符
    虚析构函数
    从文件导入三维模型
    从流导入三维模型
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/

class Model3D_Importer : public Porter {
protected:
    //-------------------------------------------------------------------------
    // 受保护的必要的构造、析构、拷贝、赋值运算符重载函数
    //-------------------------------------------------------------------------
    // 默认构造函数
    Model3D_Importer() = default;
    // 带参构造函数
    Model3D_Importer(const string& FileName);
    // 禁止使用拷贝构造函数
    Model3D_Importer(const Model3D_Importer& Source) = delete;
    // 禁止使用赋值运算符
    Model3D_Importer& operator=(const Model3D_Importer& Source) = delete;
    // 虚析构函数
    virtual ~Model3D_Importer() = default;

public:
    //-------------------------------------------------------------------------
    // 非静态Getter成员函数
    //-------------------------------------------------------------------------
    // 从文件导入三维模型
    Model3D LoadFromFile(const string& FileName) const;
    // 从文件导入三维模型
    void LoadFromFile(const string& FileName, Model3D& AModel) const;
    // 从流导入三维模型（纯虚函数，由派生类具体实现不同文件的导入）
    virtual Model3D LoadFromStream(ifstream& Stream) const = 0;
};

#endif /* Importer.hpp */