/*************************************************************************
【文件名】Model3D_OBJ_Exporter.hpp
【功能模块和目的】定义Model3D_OBJ_Exporter类，
    继承自Model3D_Exporter类，表示三维模型的OBJ格式导出器
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
#ifndef MODEL3D_OBJ_EXPORTER_HPP
#define MODEL3D_OBJ_EXPORTER_HPP

// Model3D_Exporter所属头文件
#include "Model3D_Exporter.hpp"
// fstream所属头文件
#include <fstream>
// string所属头文件
#include <string>

/*************************************************************************
【类名】Model3D_OBJ_Exporter
【功能】定义Model3D_OBJ_Exporter类，
    继承自Model3D_Exporter类，表示三维模型的OBJ格式导出器
【接口说明】
    默认构造函数
    带参构造函数
    拷贝构造函数
    重载赋值运算符
    虚析构函数
    保存三维模型到流的OBJ格式实现
【开发者及日期】谭雯心 2024/8/7
【更改记录】2024/8/8 谭雯心 将导出模型的逻辑改为点不重复输出
*************************************************************************/

class Model3D_OBJ_Exporter : public Model3D_Exporter {
public:
    //-------------------------------------------------------------------------
    // 必要的构造、析构、拷贝、赋值运算符重载函数
    //-------------------------------------------------------------------------
    // 默认构造函数
    Model3D_OBJ_Exporter();
    // 禁止外界调用拷贝构造函数
    Model3D_OBJ_Exporter(const Model3D_OBJ_Exporter& Source) = delete;
    // 禁止外界调用赋值运算符
    Model3D_OBJ_Exporter& operator=(
        const Model3D_OBJ_Exporter& Source) = delete;
    // 虚析构函数
    virtual ~Model3D_OBJ_Exporter() = default;
    //-------------------------------------------------------------------------
    // 非静态Getter成员函数
    //-------------------------------------------------------------------------
    // 保存三维模型到流的OBJ格式实现
    virtual void SaveToStream(
        ofstream& Stream, const Model3D& AModel) const override;
};

#endif /* Model3D_OBJ_Exporter.hpp */