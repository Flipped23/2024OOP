/*************************************************************************
【文件名】Model3D_OBJ_Importer.cpp
【功能模块和目的】定义Model3D_OBJ_Importer类的成员函数
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
// Model3D_OBJ_Importer所属头文件
#include "Model3D_OBJ_Importer.hpp"
// Face3D所属头文件
#include "Face3D.hpp"
// Line3D所属头文件
#include "Line3D.hpp"
// Point3D所属头文件
#include "Point3D.hpp"
// Model3D所属头文件
#include "Model3D.hpp"
// fstream所属头文件
#include <fstream>
// string所属头文件
#include <string>   
// vector所属头文件
#include <vector>

using namespace std;

//-------------------------------------------------------------------------
// 必要的构造、析构、拷贝、赋值运算符重载函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】Model3D_OBJ_Importer
【函数功能】默认构造函数, 将Model3D_Importer文件扩展名设为".obj"
【参数】无
【返回值】无
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
Model3D_OBJ_Importer::Model3D_OBJ_Importer() : Model3D_Importer(".obj") {
}

//-------------------------------------------------------------------------
// 非静态Getter成员函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】LoadFromStream
【函数功能】从流导入三维模型的OBJ格式实现
【参数】ifstream& Stream, 表示输入流
【返回值】Model3D类的对象
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
Model3D Model3D_OBJ_Importer::LoadFromStream(ifstream& Stream) const {
    // 定义Model3D类的对象，以及存储点、面、线的容器
    Model3D Model;
    vector<Point3D> Points;
    vector<Face3D> Faces;
    vector<Line3D> Lines;
    // 定义字符类型Tag用于读取文件中的每一行的第一个字符
    char Tag;
    // 定义字符串类型Description和Name用于存储模型的注释和名称
    string Description;
    string Name;
    // 读取文件中的每一行的第一个字符
    while (Stream >> Tag) {
        // 跳过第一个字符后的空格
        Stream.get();
        switch (Tag) {
            // 读取模型的注释
            case '#': {
                getline(Stream, Description);
                Model.Description = Description;
                break;
            }
            // 读取模型的名称
            case 'g': {
                getline(Stream, Name);
                Model.Name = Name;
                break;
            }
            // 读取模型的点，将点存入Points容器
            case 'v': {
                double X, Y, Z;
                Stream >> X >> Y >> Z;
                Points.push_back(Point3D(X, Y, Z));
                break;
            }
            // 按照点的索引读取模型的面，将面存入Faces容器
            case 'f': {
                size_t Index1, Index2, Index3;
                Stream >> Index1 >> Index2 >> Index3;
                Faces.push_back(Face3D(
                    Points[Index1 - 1], 
                    Points[Index2 - 1], 
                    Points[Index3 - 1]));
                break;
            }
            // 按照点的索引读取模型的线，将线存入Lines容器
            case 'l': {
                size_t Index1, Index2;
                Stream >> Index1 >> Index2;
                Lines.push_back(Line3D(
                    Points[Index1 - 1], 
                    Points[Index2 - 1]));
                break;
            }
            default: {
                break;
            }
        }
    }
    // 利用重载的+=运算符将点、面、线存入Model3D类的对象
    Model += Faces;
    Model += Lines;
    return Model;
}