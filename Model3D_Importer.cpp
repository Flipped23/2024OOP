/*************************************************************************
【文件名】Model3D_Importer.cpp
【功能模块和目的】定义Model3D_Importer类的成员函数
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
// Model3D_Importer所属头文件
#include "Model3D_Importer.hpp"
// Model3D所属头文件
#include "Model3D.hpp"
// fstream所属头文件
#include <fstream>
// string所属头文件
#include <string>
// 流操作所属头文件
#include <iostream>

using namespace std;

//-------------------------------------------------------------------------
// 必要的构造、析构、拷贝、赋值运算符重载函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】Model3D_Importer
【函数功能】带参构造函数，用于初始化Model3D_Importer类的对象
【参数】const string& FileName, 表示文件名
【返回值】无
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
Model3D_Importer::Model3D_Importer(const string& FileName)
    : Porter(GetExtension(FileName)) {
    }

//-------------------------------------------------------------------------
// 非静态Getter成员函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】LoadFromFile
【函数功能】从文件导入三维模型
【参数】const string& FileName, 表示文件名
【返回值】Model3D类的对象
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
Model3D Model3D_Importer::LoadFromFile(const string& FileName) const {
    // 测试文件扩展名是否有效
    FileValid(FileName);
    // 测试文件能否打开
    FileAvailable(FileName);
    ifstream File(FileName);
    Model3D AModel = LoadFromStream(File);
    File.close();
    return AModel;
}
/*************************************************************************
【函数名称】LoadFromFile
【函数功能】从文件导入三维模型
【参数】const string& FileName, 表示文件名；Model3D& AModel, 表示Model3D类的对象
【返回值】无
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
void Model3D_Importer::LoadFromFile(
    const string& FileName, Model3D& AModel) const {
    // 测试文件扩展名是否有效
    FileValid(FileName);
    // 测试文件能否打开
    FileAvailable(FileName);
    ifstream File(FileName);
    AModel = LoadFromStream(File);
    File.close();
}
