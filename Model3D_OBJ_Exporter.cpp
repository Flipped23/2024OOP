/*************************************************************************
【文件名】Model3D_OBJ_Exporter.cpp
【功能模块和目的】定义Model3D_OBJ_Exporter类的成员函数
【开发者及日期】谭雯心 2024/8/7
【更改记录】2024/8/8 谭雯心 将导出模型的逻辑改为点不重复输出
*************************************************************************/
// Model3D_OBJ_Exporter所属头文件
#include "Model3D_OBJ_Exporter.hpp"
// Face3D所属头文件
#include "Face3D.hpp"
// Line3D所属头文件
#include "Line3D.hpp"
// Point3D所属头文件
#include "Model3D.hpp"
// Point3D所属头文件
#include "Point3D.hpp"
// Point3DSet所属头文件
#include "Point3DSet.hpp"
// fstream所属头文件
#include <fstream>
// string所属头文件
#include <string>
// size_t所属头文件
#include <cstddef>
// 流输出所属头文件
#include <iostream>

using namespace std;

//-------------------------------------------------------------------------
// 必要的构造、析构、拷贝、赋值运算符重载函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】Model3D_OBJ_Exporter
【函数功能】默认构造函数, 将Model3D_Exporter文件扩展名设为".obj"
【参数】无
【返回值】无
【开发者及日期】谭雯心 2024/8/7
【更改记录】
*************************************************************************/
Model3D_OBJ_Exporter::Model3D_OBJ_Exporter() : Model3D_Exporter(".obj") {
}

//-------------------------------------------------------------------------
// 非静态Getter成员函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】SaveToStream
【函数功能】保存三维模型到流的OBJ格式实现
【参数】ofstream& Stream, 表示输出流；const Model3D& AModel, 表示Model3D类的对象
【返回值】无
【开发者及日期】谭雯心 2024/8/7
【更改记录】2024/8/8 谭雯心 将导出模型的逻辑改为点不重复输出
*************************************************************************/
void Model3D_OBJ_Exporter::SaveToStream(
    ofstream& Stream, const Model3D& AModel) const {
    // 导出到流前先清空流
    Stream.clear();
    // 输出模型的注释和名称
    Stream << "# " << AModel.Description << endl;
    Stream << "g " << AModel.Name << endl;
    // 定义Point3DSet类的对象Points，用于存储模型的点集合
    Point3DSet Points;
    // 遍历模型的线集合，将线的两个端点加入到Points中
    for (auto Line : AModel.Lines()) {
        for (size_t i = 0; i < 2; i++) {
            // 如果点已经存在，则跳过
            try {
                Points.Add(Line->Points[i]);
            } 
            catch (...) {
                continue;
            }
        }
    }
    // 遍历模型的面集合，将面的三个顶点加入到Points中
    for (auto Face : AModel.Faces()) {
        for (size_t i = 0; i < 3; i++) {
            // 如果点已经存在，则跳过
            try {
                Points.Add(Face->Points[i]);
            } 
            catch (...) {
                continue;
            }
        }
    }
    // 定义整型变量PointCount，用于存储点的数量，便于后续遍历输出
    size_t PointCount = Points.CountElement();
    // 遍历Points，输出每个点的坐标
    for (size_t i = 0; i < PointCount; i++) {
        Stream << "v " << Points[i].X << " " 
            << Points[i].Y << " " << Points[i].Z << endl;
    }
    // 遍历模型的线集合，输出每条线的两个端点
    for (auto Line : AModel.Lines()) {
        Stream << "l ";
        for (size_t i = 0; i < 2; i++) {
            // 利用Search输出点的索引 + 1，因为索引从1开始
            Stream << Points.Search(Line->Points[i]) + 1 << " ";
        }
        Stream << endl;
    }
    // 遍历模型的面集合，输出每个面的三个顶点
    for (auto Face : AModel.Faces()) {
        Stream << "f ";
        for (size_t i = 0; i < 3; i++) {
            // 利用Search输出点的索引 + 1，因为索引从1开始
            Stream << Points.Search(Face->Points[i]) + 1 << " ";
        }
        Stream << endl;
    }
}
