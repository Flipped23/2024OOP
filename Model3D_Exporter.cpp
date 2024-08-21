/*************************************************************************
【文件名】Model3D_Exporter.cpp
【功能模块和目的】定义Model3D_Exporter类的成员函数
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/

// Model3D_Exporter所属头文件
#include "Model3D_Exporter.hpp"
// Model3D所属头文件
#include "Model3D.hpp"
// fstream所属头文件
#include <fstream>
// string所属头文件
#include <string>

using namespace std;

//-------------------------------------------------------------------------
// 必要的构造、析构、拷贝、赋值运算符重载函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】Model3D_Exporter
【函数功能】带参构造函数，用于初始化Model3D_Exporter类的对象
【参数】const string& FileName, 表示文件名
【返回值】无
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
Model3D_Exporter::Model3D_Exporter(const string& FileName)
    : Porter(GetExtension(FileName)) {
    }

//-------------------------------------------------------------------------
// 非静态Getter成员函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】SaveToFile
【函数功能】保存三维模型到文件
【参数】const string& FileName, 表示文件名；const Model3D& AModel,
表示Model3D类的对象 【返回值】无 【开发者及日期】谭雯心 2024/8/7 【更改记录】
*************************************************************************/
void Model3D_Exporter::SaveToFile(
    const string& FileName, const Model3D& AModel) {
    FileValid(FileName);
    CreateFileNotExists(FileName);
    FileAvailable(FileName);
    ofstream File(FileName, ios::trunc);
    SaveToStream(File, AModel);
    File.close();
}
