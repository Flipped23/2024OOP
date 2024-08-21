/*************************************************************************
【文件名】Model3D_OBJ_Importer.hpp
【功能模块和目的】定义Model3D_OBJ_Importer类，
    继承自Model3D_Importer类，表示三维模型的OBJ格式导入器
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
#ifndef MODEL3D_OBJ_IMPORTER_HPP
#define MODEL3D_OBJ_IMPORTER_HPP

// Model3D所属头文件
#include "Model3D.hpp"
// Model3D_Importer所属头文件
#include "Model3D_Importer.hpp"
// fstream所属头文件
#include <fstream>
// string所属头文件
#include <string>

using namespace std;


/*************************************************************************
【类名】Model3D_OBJ_Importer
【功能】定义Model3D_OBJ_Importer类，
    继承自Model3D_Importer类，表示三维模型的OBJ格式导入器
【接口说明】
    默认构造函数
    带参构造函数
    拷贝构造函数
    重载赋值运算符
    虚析构函数
    从流导入三维模型的OBJ格式实现
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/

class Model3D_OBJ_Importer : public Model3D_Importer {
public:
    //-------------------------------------------------------------------------
    // 必要的构造、析构、拷贝、赋值运算符重载函数
    //-------------------------------------------------------------------------
    // 默认构造函数
    Model3D_OBJ_Importer();
    // 禁止外界调用拷贝构造函数
    Model3D_OBJ_Importer(const Model3D_OBJ_Importer& Source) = delete;
    // 禁止外界调用重载赋值运算符
    Model3D_OBJ_Importer& operator=(
        const Model3D_OBJ_Importer& Source) = delete;
    // 虚析构函数
    virtual ~Model3D_OBJ_Importer() = default;
    //-------------------------------------------------------------------------
    // 非静态Getter成员函数
    //-------------------------------------------------------------------------
    // 从流导入三维模型的OBJ格式实现
    virtual Model3D LoadFromStream(ifstream& Stream) const override;
};

#endif /* Model3D_OBJ_Importer.hpp */