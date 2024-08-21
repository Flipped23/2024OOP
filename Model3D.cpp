/*************************************************************************
【文件名】Model3D.cpp
【功能模块和目的】实现Model3D类的行为
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
// Model3D头文件
#include "Model3D.hpp"
// Face3D头文件
#include "Face3D.hpp"
// Line3D头文件
#include "Line3D.hpp"
// Point3D头文件
#include "Point3D.hpp"
// vector所属头文件
#include <vector>
// vector操作所属头文件
#include <algorithm>
#include <functional>
// string所属头文件
#include <string>
// 异常类所属头文件
#include <limits>
// shared_ptr所属头文件
#include <memory>
// size_t所属头文件
#include <cstddef>
// numeric_limits所属头文件
#include <limits>
// 流操作所属头文件
#include <iostream>

using namespace std;

//-------------------------------------------------------------------------
// 内嵌异常类
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】FACE_ALREADY_EXISTS
【函数功能】构造函数，用于初始化FACE_NOT_FOUND异常类
【参数】无
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
Model3D::FACE_ALREADY_EXISTS::FACE_ALREADY_EXISTS()
    : logic_error("Face already exists") {
    }
/*************************************************************************
【函数名称】FACE_NOT_FOUND
【函数功能】构造函数，用于初始化FACE_NOT_FOUND异常类
【参数】无
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
Model3D::FACE_NOT_FOUND::FACE_NOT_FOUND() : logic_error("Face not found") {
}
/*************************************************************************
【函数名称】LINE_ALREADY_EXISTS
【函数功能】构造函数，用于初始化LINE_ALREADY_EXISTS异常类
【参数】无
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
Model3D::LINE_ALREADY_EXISTS::LINE_ALREADY_EXISTS()
    : logic_error("Line already exists") {
    }
/*************************************************************************
【函数名称】LINE_NOT_FOUND
【函数功能】构造函数，用于初始化LINE_NOT_FOUND异常类
【参数】无
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
Model3D::LINE_NOT_FOUND::LINE_NOT_FOUND() : logic_error("Line not found") {
}
/*************************************************************************
【函数名称】POINT_DUPLICATED
【函数功能】构造函数，用于初始化POINT_DUPLICATED异常类
【参数】无
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
Model3D::POINT_DUPLICATED::POINT_DUPLICATED()
    : logic_error("Point duplicated") {
    }
/*************************************************************************
【函数名称】POINT_NOT_FOUND
【函数功能】构造函数，用于初始化POINT_NOT_FOUND异常类
【参数】无
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
Model3D::POINT_NOT_FOUND::POINT_NOT_FOUND() : logic_error("Point not found") {
}

//-------------------------------------------------------------------------
// 必要的构造、析构、拷贝、赋值运算符重载函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】Model3D
【函数功能】带参构造函数，用于初始化Model3D类的对象
【参数】vector<Line3D> Lines, vector<Face3D> Faces
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
Model3D::Model3D(vector<Line3D> VLines, vector<Face3D> VFaces) {
    // 清空当前对象的m_Faces和m_Lines
    m_Faces.clear();
    m_Lines.clear();
    for (size_t i = 0; i < VFaces.size(); i++) {
        // 将VFaces中的元素转换为shared_ptr<Line3D>类型，并添加到m_Faces中
        shared_ptr<Face3D> FacePTR = make_shared<Face3D>(VFaces[i]);
        m_Faces.push_back(FacePTR);
    }
    for (size_t i = 0; i < VLines.size(); i++) {
        // 将VLines中的元素转换为shared_ptr<Line3D>类型，并添加到m_Lines中
        shared_ptr<Line3D> LinePTR = make_shared<Line3D>(VLines[i]);
        m_Lines.push_back(LinePTR);
    }
}
/*************************************************************************
【函数名称】Model3D
【函数功能】拷贝构造函数，用于初始化Model3D类的对象（深拷贝）
【参数】const Model3D& Source, 表示另一个Model3D类的对象
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】2024/8/11 谭雯心 将拷贝构造函数改为深拷贝
*************************************************************************/
Model3D::Model3D(const Model3D& Source) {
    // 清空当前对象的m_Faces和m_Lines
    m_Faces.clear();
    m_Lines.clear();
    // 深拷贝Source的m_Faces
    for (const auto& face : Source.m_Faces) {
        shared_ptr<Face3D> FacePTR = make_shared<Face3D>(*face);
        m_Faces.push_back(FacePTR);
    }
    // 深拷贝Source的m_Lines
    for (const auto& line : Source.m_Lines) {
        shared_ptr<Line3D> LinePTR = make_shared<Line3D>(*line);
        m_Lines.push_back(LinePTR);
    }
    // 拷贝其他成员变量
    Name = Source.Name;
    Description = Source.Description;
}
/*************************************************************************
【函数名称】operator=
【函数功能】重载赋值运算符，用于将一个Model3D类的对象赋值给另一个Model3D类的对象
【参数】const Model3D& Source, 表示另一个Model3D类的对象
【返回值】Model3D类的对象的引用
【开发者及日期】谭雯心 2024/8/8
【更改记录】2024/8/11 谭雯心 将赋值运算符改为深拷贝
*************************************************************************/
Model3D& Model3D::operator=(const Model3D& Source) {
    if (this != &Source) {
        // 清空当前对象的m_Faces和m_Lines
        m_Faces.clear();
        m_Lines.clear();
        // 深拷贝Source的m_Faces
        for (const auto& face : Source.m_Faces) {
            shared_ptr<Face3D> FacePTR = make_shared<Face3D>(*face);
            m_Faces.push_back(FacePTR);
        }
        // 深拷贝Source的m_Lines
        for (const auto& line : Source.m_Lines) {
            shared_ptr<Line3D> LinePTR = make_shared<Line3D>(*line);
            m_Lines.push_back(LinePTR);
        }
        // 拷贝其他成员变量
        Name = Source.Name;
        Description = Source.Description;
    }
    return *this;
}

//-------------------------------------------------------------------------
// 非静态Setter成员函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】AddFace
【函数功能】添加面到模型面列表的末尾
【参数】const Face3D& AFace, 表示要添加的面
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
void Model3D::AddFace(const Face3D& AFace) {
    shared_ptr<Face3D> FacePTR = make_shared<Face3D>(AFace);
    // 若已经存在该面，则抛出FACE_ALREADY_EXISTS异常
    if (ContainFace(AFace)) {
        throw FACE_ALREADY_EXISTS();
    }
    // 将面添加到模型面列表的末尾
    m_Faces.push_back(FacePTR);
}
/*************************************************************************
【函数名称】AddFace
【函数功能】添加面到模型面列表的末尾
【参数】const Point3D& Point1,
       const Point3D& Point2,
       const Point3D& Point3，表示要添加的面的三个点
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
void Model3D::AddFace(
    const Point3D& Point1, 
    const Point3D& Point2,
    const Point3D& Point3) {
    shared_ptr<Face3D> FacePTR = make_shared<Face3D>(Point1, Point2, Point3);
    // 若已经存在该面，则抛出FACE_ALREADY_EXISTS异常
    if (ContainFace(*FacePTR)) {
        throw FACE_ALREADY_EXISTS();
    }
    m_Faces.push_back(FacePTR);
}
/*************************************************************************
【函数名称】RemoveFace
【函数功能】从模型面列表中删除指定面
【参数】const Face3D& AFace, 表示要删除的面
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
void Model3D::RemoveFace(const Face3D& AFace) {
    // 若找不到对应面，抛出FACE_NOT_FOUND异常
    if (!ContainFace(AFace)) {
        throw FACE_NOT_FOUND();
    }
    for (size_t i = 0; i < m_Faces.size(); i++) {
        // 若找到对应面，则删除该面
        if (*m_Faces[i] == AFace) {
            m_Faces.erase(m_Faces.begin() + i);
            break;
        }
    }
}
/*************************************************************************
【函数名称】RemoveFace
【函数功能】从模型面列表中删除指定面
【参数】const Point3D& Point1,
       const Point3D& Point2,
       const Point3D& Point3，表示要删除的面的三个点
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
void Model3D::RemoveFace(
    const Point3D& Point1, 
    const Point3D& Point2,
    const Point3D& Point3) {
    shared_ptr<Face3D> FacePTR = make_shared<Face3D>(Point1, Point2, Point3);
    // 若找不到对应面，抛出FACE_NOT_FOUND异常
    if (!ContainFace(*FacePTR)) {
        throw FACE_NOT_FOUND();
    }
    for (size_t i = 0; i < m_Faces.size(); i++) {
        // 若找到对应面，则删除该面
        if (m_Faces[i] == FacePTR) {
            m_Faces.erase(m_Faces.begin() + i);
            break;
        }
    }
}
/*************************************************************************
【函数名称】RemoveFace
【函数功能】从模型面列表中删除指定面
【参数】size_t Index, 表示要删除的面的位置
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
void Model3D::RemoveFace(size_t FaceIndex) {
    // 若找不到对应面，抛出FACE_NOT_FOUND异常
    if (FaceIndex >= m_Faces.size()) {
        throw FACE_NOT_FOUND();
    }
    // 删除模型面列表中指定位置的面
    m_Faces.erase(m_Faces.begin() + FaceIndex);
}
/*************************************************************************
【函数名称】ChangeFace
【函数功能】修改模型面列表中指定面
【参数】const Face3D& FaceFrom, 表示要修改的面
       const Face3D& FaceTo, 表示修改后的面
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
void Model3D::ChangeFace(const Face3D& FaceFrom, const Face3D& FaceTo) {
    // 若找不到对应面，抛出FACE_NOT_FOUND异常
    if (!ContainFace(FaceFrom)) {
        throw FACE_NOT_FOUND();
    }
    for (size_t i = 0; i < m_Faces.size(); i++) {
        // 若找到对应面，则尝试修改该面
        if (*m_Faces[i] == FaceFrom) {
            shared_ptr<Face3D> FacePTR = make_shared<Face3D>(FaceTo);
            m_Faces[i] = FacePTR;
            break;
        }
    }
}
/*************************************************************************
【函数名称】ChangeFace
【函数功能】修改模型面列表中指定位置的面
【参数】int Index, 表示要修改的面的位置
       const Face3D& AFace, 表示要修改的面
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
void Model3D::ChangeFace(size_t FaceIndex, const Face3D& AFace) {
    // 若找不到对应面，抛出FACE_NOT_FOUND异常
    if (FaceIndex >= m_Faces.size()) {
        throw FACE_NOT_FOUND();
    }
    // 将AFace转换为shared_ptr<Face3D>类型，并替换模型面列表中指定位置的面
    shared_ptr<Face3D> FacePTR = make_shared<Face3D>(AFace);
    m_Faces[FaceIndex] = FacePTR;
}
/*************************************************************************
【函数名称】ChangeFacePoint
【函数功能】修改模型面列表中指定面的指定点
【参数】const Face3D& AFace, 表示要修改的面
       const Point3D& PointFrom, 表示要修改的点
       const Point3D& PointTo, 表示修改后的点
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
void Model3D::ChangeFacePoint(
    const Face3D& AFace, 
    const Point3D& PointFrom,
    const Point3D& PointTo) {
    // 若找不到对应面，抛出FACE_NOT_FOUND异常
    if (!ContainFace(AFace)) {
        throw FACE_NOT_FOUND();
    }
    for (size_t i = 0; i < m_Faces.size(); i++) {
        // 若找到对应面，则尝试修改该面的指定点
        if (*m_Faces[i] == AFace) {
            m_Faces[i]->ChangePoint(PointFrom, PointTo);
            break;
        }
    }
}
/*************************************************************************
【函数名称】ChangeFacePoint
【函数功能】修改模型面列表中指定面的指定点
【参数】size_t Index, 表示要修改的面的位置
       const Point3D& PointFrom, 表示要修改的点
       const Point3D& PointTo, 表示修改后的点
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
void Model3D::ChangeFacePoint(
    size_t FaceIndex, 
    const Point3D& PointFrom,
    const Point3D& PointTo) {
    // 若找不到对应面，抛出FACE_NOT_FOUND异常
    if (FaceIndex >= m_Faces.size()) {
        throw FACE_NOT_FOUND();
    }
    // 尝试修改模型面列表中指定位置的面的指定点
    m_Faces[FaceIndex]->ChangePoint(PointFrom, PointTo);
}
/*************************************************************************
【函数名称】ChangeFacePoint
【函数功能】修改模型面列表中指定面的指定位置的点
【参数】const Face3D& AFace, 表示要修改的面
       size_t Index, 表示要修改的点的位置
       const Point3D& PointTo, 表示修改后的点
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】2024/8/11 谭雯心 增加POINT_NOT_FOUND异常处理
*************************************************************************/
void Model3D::ChangeFacePoint(
    const Face3D& AFace, 
    size_t Index,
    const Point3D& PointTo) {
    // 若找不到对应面，抛出FACE_NOT_FOUND异常
    if (!ContainFace(AFace)) {
        throw FACE_NOT_FOUND();
    }
    // 若找不到对应点，抛出POINT_NOT_FOUND异常
    if (Index > 2) {
        throw POINT_NOT_FOUND();
    }
    for (size_t i = 0; i < m_Faces.size(); i++) {
        // 若找到对应面，则尝试修改该面的指定位置的点
        if (*m_Faces[i] == AFace) {
            m_Faces[i]->ChangePoint(PointTo, Index);
            break;
        }
    }
}
/*************************************************************************
【函数名称】ChangeFacePoint
【函数功能】修改模型面列表中指定面的指定点
【参数】size_t Index, 表示要修改的面的位置
       size_t PointIndex, 表示要修改的点的位置
       const Point3D& PointTo, 表示修改后的点
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
void Model3D::ChangeFacePoint(
    size_t FaceIndex, 
    size_t PointIndex,
    const Point3D& PointTo) {
    // 若找不到对应面，抛出FACE_NOT_FOUND异常
    if (FaceIndex >= m_Faces.size()) {
        throw FACE_NOT_FOUND();
    }
    // 若找不到对应点，抛出POINT_NOT_FOUND异常
    if (PointIndex > 2) {
        throw POINT_NOT_FOUND();
    }
    // 尝试修改模型面列表中指定位置的面的指定位置的点
    m_Faces[FaceIndex]->ChangePoint(PointTo, PointIndex);
}
/*************************************************************************
【函数名称】ClearFaces
【函数功能】清空模型面列表
【参数】无
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
void Model3D::ClearFaces() { 
    m_Faces.clear(); 
}
/*************************************************************************
【函数名称】AddLine
【函数功能】添加线到模型线列表的末尾
【参数】const Line3D& ALine, 表示要添加的线
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
void Model3D::AddLine(const Line3D& ALine) {
    shared_ptr<Line3D> LinePTR = make_shared<Line3D>(ALine);
    // 若已经存在该线，则抛出LINE_ALREADY_EXISTS异常
    if (ContainLine(ALine)) {
        throw LINE_ALREADY_EXISTS();
    }
    m_Lines.push_back(LinePTR);
}
/*************************************************************************
【函数名称】AddLine
【函数功能】添加线到模型线列表的末尾
【参数】const Point3D& Point1,
       const Point3D& Point2，表示要添加的线的两个点
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
void Model3D::AddLine(const Point3D& Point1, const Point3D& Point2) {
    shared_ptr<Line3D> LinePTR = make_shared<Line3D>(Point1, Point2);
    // 若已经存在该线，则抛出LINE_ALREADY_EXISTS异常
    if (ContainLine(*LinePTR)) {
        throw LINE_ALREADY_EXISTS();
    }
    m_Lines.push_back(LinePTR);
}
/*************************************************************************
【函数名称】RemoveLine
【函数功能】从模型线列表中删除指定线
【参数】const Line3D& ALine, 表示要删除的线
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
void Model3D::RemoveLine(const Line3D& ALine) {
    // 若找不到对应线，抛出LINE_NOT_FOUND异常
    if (!ContainLine(ALine)) {
        throw LINE_NOT_FOUND();
    }
    for (size_t i = 0; i < m_Lines.size(); i++) {
        // 若找到对应线，则删除该线
        if (*m_Lines[i] == ALine) {
            m_Lines.erase(m_Lines.begin() + i);
            break;
        }
    }
}
/*************************************************************************
【函数名称】RemoveLine
【函数功能】从模型线列表中删除指定线
【参数】size_t Index, 表示要删除的线的位置
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
void Model3D::RemoveLine(size_t LineIndex) {
    // 若找不到对应线，抛出LINE_NOT_FOUND异常
    if (LineIndex >= m_Lines.size()) {
        throw LINE_NOT_FOUND();
    }
    // 删除模型线列表中指定位置的线
    m_Lines.erase(m_Lines.begin() + LineIndex);
}
/*************************************************************************
【函数名称】RemoveLine
【函数功能】从模型线列表中删除指定线
【参数】const Point3D& Point1,
       const Point3D& Point2，表示要删除的线的两个点
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
void Model3D::RemoveLine(const Point3D& Point1, const Point3D& Point2) {
    shared_ptr<Line3D> LinePTR = make_shared<Line3D>(Point1, Point2);
    // 若找不到对应线，抛出LINE_NOT_FOUND异常
    if (!ContainLine(*LinePTR)) {
        throw LINE_NOT_FOUND();
    }
    for (size_t i = 0; i < m_Lines.size(); i++) {
        // 若找到对应线，则删除该线
        if (m_Lines[i] == LinePTR) {
            m_Lines.erase(m_Lines.begin() + i);
            break;
        }
    }
}
/*************************************************************************
【函数名称】ChangeLine
【函数功能】修改模型线列表中指定位置的线
【参数】const Line3D& LineFrom, 表示要修改的线
       const Line3D& LineTo, 表示修改后的线
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
void Model3D::ChangeLine(const Line3D& LineFrom, const Line3D& LineTo) {
    // 若找不到对应线，抛出LINE_NOT_FOUND异常
    if (!ContainLine(LineFrom)) {
        throw LINE_NOT_FOUND();
    }
    for (size_t i = 0; i < m_Lines.size(); i++) {
        // 若找到对应线，则尝试修改该线
        if (*m_Lines[i] == LineFrom) {
            shared_ptr<Line3D> LinePTR = make_shared<Line3D>(LineTo);
            m_Lines[i] = LinePTR;
            break;
        }
    }
}
/*************************************************************************
【函数名称】ChangeLine
【函数功能】修改模型线列表中指定位置的线
【参数】int Index, 表示要修改的线的位置
       const Line3D& ALine, 表示要修改的线
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
void Model3D::ChangeLine(size_t LineIndex, const Line3D& ALine) {
    // 若找不到对应线，抛出LINE_NOT_FOUND异常
    if (LineIndex >= m_Lines.size()) {
        throw LINE_NOT_FOUND();
    }
    // 将ALine转换为shared_ptr<Line3D>类型，并替换模型线列表中指定位置的线
    shared_ptr<Line3D> LinePTR = make_shared<Line3D>(ALine);
    m_Lines[LineIndex] = LinePTR;
}
/*************************************************************************
【函数名称】ChangeLinePoint
【函数功能】修改模型线列表中指定线的指定点
【参数】const Line3D& ALine, 表示要修改的线
       const Point3D& PointFrom, 表示要修改的点
       const Point3D& PointTo, 表示修改后的点
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
void Model3D::ChangeLinePoint(
    const Line3D& ALine, 
    const Point3D& PointFrom,
    const Point3D& PointTo) {
    // 若找不到对应线，抛出LINE_NOT_FOUND异常
    if (!ContainLine(ALine)) {
        throw LINE_NOT_FOUND();
    }
    for (size_t i = 0; i < m_Lines.size(); i++) {
        // 若找到对应线，则尝试修改该线的指定点
        if (*m_Lines[i] == ALine) {
            m_Lines[i]->ChangePoint(PointFrom, PointTo);
            break;
        }
    }
}
/*************************************************************************
【函数名称】ChangeLinePoint
【函数功能】修改模型线列表中指定线的指定点
【参数】size_t Index, 衝突要修改的线的位置
       const Point3D& PointFrom, 表示要修改的点
       const Point3D& PointTo, 表示修改后的点
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
void Model3D::ChangeLinePoint(
    size_t LineIndex, 
    const Point3D& PointFrom,
    const Point3D& PointTo) {
    // 若找不到对应线，抛出LINE_NOT_FOUND异常
    if (LineIndex >= m_Lines.size()) {
        throw LINE_NOT_FOUND();
    }
    // 尝试修改模型线列表中指定位置的线的指定点
    m_Lines[LineIndex]->ChangePoint(PointFrom, PointTo);
}
/*************************************************************************
【函数名称】ChangeLinePoint
【函数功能】修改模型线列表中指定线的指定位置的点
【参数】const Line3D& ALine, 表示要修改的线
       size_t Index, 表示要修改的点的位置
       const Point3D& PointTo, 表示修改后的点
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】2024/8/11 谭雯心 增加POINT_NOT_FOUND异常处理
*************************************************************************/
void Model3D::ChangeLinePoint(
    const Line3D& ALine, 
    size_t Index,
    const Point3D& PointTo) {
    // 若找不到对应线，抛出LINE_NOT_FOUND异常
    if (!ContainLine(ALine)) {
        throw LINE_NOT_FOUND();
    }
    // 若找不到对应点，抛出POINT_NOT_FOUND异常
    if (Index > 1) {
        throw POINT_NOT_FOUND();
    }
    for (size_t i = 0; i < m_Lines.size(); i++) {
        // 若找到对应线，则尝试修改该线的指定位置的点
        if (*m_Lines[i] == ALine) {
            m_Lines[i]->ChangePoint(PointTo, Index);
            break;
        }
    }
}
/*************************************************************************
【函数名称】ChangeLinePoint
【函数功能】修改模型线列表中指定线的指定点
【参数】size_t Index, 表示要修改的线的位置
       size_t PointIndex, 表示要修改的点的位置
       const Point3D& PointTo, 表示修改后的点
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
void Model3D::ChangeLinePoint(
    size_t LineIndex, 
    size_t PointIndex,
    const Point3D& PointTo) {
    // 若找不到对应线，抛出LINE_NOT_FOUND异常
    if (LineIndex >= m_Lines.size()) {
        throw LINE_NOT_FOUND();
    }
    // 若找不到对应点，抛出POINT_NOT_FOUND异常
    if (PointIndex > 1) {
        throw POINT_NOT_FOUND();
    }
    // 尝试修改模型线列表中指定位置的线的指定位置的点
    m_Lines[LineIndex]->ChangePoint(PointTo, PointIndex);
}
/*************************************************************************
【函数名称】ClearLines
【函数功能】清空模型线列表
【参数】无
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
void Model3D::ClearLines() { 
    m_Lines.clear(); 
}
/*************************************************************************
【函数名称】Clear
【函数功能】清空模型中的所有面和线
【参数】无
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
void Model3D::Clear() {
    ClearFaces();
    ClearLines();
}
/*************************************************************************
【函数名称】operator+=
【函数功能】+=运算符重载，合并两个模型
【参数】const Model3D& AModel, 表示另一个Model3D类的对象
【返回值】Model3D类的对象的引用
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
Model3D& Model3D::operator+=(const Model3D& AModel) {
    // 利用+运算符重载，合并两个模型
    *this = *this + AModel;
    return *this;
}
/*************************************************************************
【函数名称】operator+=
【函数功能】+=运算符重载，合并面到模型
【参数】const vector<Face3D>& VFaces, 表示要合并的面列表
【返回值】Model3D类的对象的引用
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
Model3D& Model3D::operator+=(const vector<Face3D>& VFaces) {
    // 利用+运算符重载，合并面到模型
    *this = *this + VFaces;
    return *this;
}
/*************************************************************************
【函数名称】operator+=
【函数功能】+=运算符重载，合并线到模型
【参数】const vector<Line3D>& VLines, 表示要合并的线列表
【返回值】Model3D类的对象的引用
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
Model3D& Model3D::operator+=(const vector<Line3D>& VLines) {
    // 利用+运算符重载，合并线到模型
    *this = *this + VLines;
    return *this;
}
/*************************************************************************
【函数名称】operator-=
【函数功能】-=运算符重载，从模型中删除模型
【参数】const Model3D& AModel, 表示另一个Model3D类的对象
【返回值】Model3D类的对象的引用
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
Model3D& Model3D::operator-=(const Model3D& AModel) {
    // 利用-运算符重载，从模型中删除模型
    *this = *this - AModel;
    return *this;
}
/*************************************************************************
【函数名称】operator-=
【函数功能】-=运算符重载，从模型中删除面
【参数】const vector<Face3D>& VFaces, 表示要删除的面列表
【返回值】Model3D类的对象的引用
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
Model3D& Model3D::operator-=(const vector<Face3D>& VFaces) {
    // 利用-运算符重载，从模型中删除面
    *this = *this - VFaces;
    return *this;
}
/*************************************************************************
【函数名称】operator-=
【函数功能】+=运算符重载，合并两个模型
【参数】const vector<Line3D>& VLines, 表示要删除的线列表
【返回值】Model3D类的对象的引用
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
Model3D& Model3D::operator-=(const vector<Line3D>& VLines) {
    *this = *this - VLines;
    return *this;
}

//-------------------------------------------------------------------------
// 非静态Getter成员函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】operator==
【函数功能】==运算符重载，判断两个模型是否相等
【参数】const Model3D& AModel, 表示另一个Model3D类的对象
【返回值】bool，表示两个模型是否相等
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
bool Model3D::operator==(const Model3D& AModel) const {
    // 若两个模型的面和线数量不相等，则两个模型不相等
    if (m_Faces.size() != AModel.Faces().size()
        || m_Lines.size() != AModel.Lines().size()) {
        return false;
    }
    // 若两个模型的面和线不相等，则两个模型不相等
    for (size_t i = 0; i < m_Faces.size(); i++) {
        if (*m_Faces[i] != *AModel.Faces()[i]) {
            return false;
        }
    }
    for (size_t i = 0; i < m_Lines.size(); i++) {
        if (*m_Lines[i] != *AModel.Lines()[i]) {
            return false;
        }
    }
    return true;
}
/*************************************************************************
【函数名称】operator!=
【函数功能】!=运算符重载，判断两个模型是否不相等
【参数】const Model3D& AModel, 表示另一个Model3D类的对象
【返回值】bool，表示两个模型是否不相等
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
bool Model3D::operator!=(const Model3D& AModel) const {
    return !(*this == AModel);
}
/*************************************************************************
【函数名称】+
【函数功能】+运算符重载，合并两个模型
【参数】const Model3D& AModel, 表示另一个Model3D类的对象
【返回值】Model3D类的对象
【开发者及日期】谭雯心 2024/8/8
【更改记录】2024/8/11 谭雯心 修改合并模型的逻辑
*************************************************************************/
Model3D Model3D::operator+(const Model3D& AModel) const {
    Model3D result = *this;
    for (auto Face : AModel.Faces()) {
        // 若AModel中的面已经存在于result中，则不添加到result中
        try {
            result.AddFace(*Face);
        } 
        catch (const Model3D::FACE_ALREADY_EXISTS& e) {
            continue;
        }
    }
    for (auto Line : AModel.Lines()) {
        // 若AModel中的线已经存在于result中，则不添加到result中
        try {
            result.AddLine(*Line);
        } 
        catch (const Model3D::LINE_ALREADY_EXISTS& e) {
            continue;
        }
    }
    return result;
}
/*************************************************************************
【函数名称】operator+
【函数功能】+运算符重载，合并面到模型
【参数】const vector<Face3D>& VFaces, 表示要合并的面列表
【返回值】Model3D类的对象
【开发者及日期】谭雯心 2024/8/8
【更改记录】2024/8/11 谭雯心 修改合并面的逻辑
*************************************************************************/
Model3D Model3D::operator+(const vector<Face3D>& VFaces) const {
    Model3D result = *this;
    for (auto Face : VFaces) {
        // 若VFaces中的面已经存在于result中，则不添加到result中
        try {
            result.AddFace(Face);
        } 
        catch (const Model3D::FACE_ALREADY_EXISTS& e) {
            continue;
        }
    }
    return result;
}
/*************************************************************************
【函数名称】operator+
【函数功能】+运算符重载，合并线到模型
【参数】const vector<Line3D>& VLines, 表示要合并的线列表
【返回值】Model3D类的对象
【开发者及日期】谭雯心 2024/8/8
【更改记录】2024/8/11 谭雯心 修改合并线的逻辑
*************************************************************************/
Model3D Model3D::operator+(const vector<Line3D>& VLines) const {
    Model3D result = *this;
    for (auto Line : VLines) {
        // 若VLines中的线已经存在于result中，则不添加到result中
        try {
            result.AddLine(Line);
        } 
        catch (const Model3D::LINE_ALREADY_EXISTS& e) {
            continue;
        }
    }
    return result;
}
/*************************************************************************
【函数名称】operator-
【函数功能】-运算符重载，从模型中删除模型
【参数】const Model3D& AModel, 表示另一个Model3D类的对象
【返回值】Model3D类的对象
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
Model3D Model3D::operator-(const Model3D& AModel) const {
    Model3D result = *this;
    for (auto Face : AModel.Faces()) {
        result.RemoveFace(*Face);
    }
    for (auto Line : AModel.Lines()) {
        result.RemoveLine(*Line);
    }
    return result;
}
/*************************************************************************
【函数名称】operator-
【函数功能】-运算符重载，从模型中删除面
【参数】const vector<Face3D>& VFaces, 表示要删除的面列表
【返回值】Model3D类的对象
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
Model3D Model3D::operator-(const vector<Face3D>& VFaces) const {
    Model3D result = *this;
    for (auto Face : VFaces) {
        result.RemoveFace(Face);
    }
    return result;
}
/*************************************************************************
【函数名称】operator-
【函数功能】-运算符重载，从模型中删除线
【参数】const vector<Line3D>& VLines, 表示要删除的线列表
【返回值】Model3D类的对象
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
Model3D Model3D::operator-(const vector<Line3D>& VLines) const {
    Model3D result = *this;
    for (auto Line : VLines) {
        result.RemoveLine(Line);
    }
    return result;
}
/*************************************************************************
【函数名称】Copy
【函数功能】复制模型
【参数】无
【返回值】Model3D类的对象
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
Model3D Model3D::Copy() const {
    Model3D result = *this;
    return result;
}
/*************************************************************************
【函数名称】GetPointCount
【函数功能】获取模型中点的总数量
【参数】无
【返回值】size_t，表示模型中点的总数量
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
size_t Model3D::GetPointCount() const {
    return GetFaceCount() * 3 + GetLineCount() * 2;
}
/*************************************************************************
【函数名称】GetElementCount
【函数功能】获取模型中元素的总数量
【参数】无
【返回值】size_t，表示模型中元素的总数量
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
size_t Model3D::GetElementCount() const {
    return GetFaceCount() + GetLineCount();
}
/*************************************************************************
【函数名称】GetFaceCount
【函数功能】获取模型中面的总数量
【参数】无
【返回值】size_t，表示模型中面的总数量
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
size_t Model3D::GetFaceCount() const {
    return m_Faces.size();
}
/*************************************************************************
【函数名称】GetLineCount
【函数功能】获取模型中线的总数量
【参数】无
【返回值】size_t，表示模型中线的总数量
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
size_t Model3D::GetLineCount() const { 
    return m_Lines.size(); 
}
/*************************************************************************
【函数名称】Area
【函数功能】获取模型中面的总面积
【参数】无
【返回值】double，表示模型中面的总面积
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
double Model3D::Area() const {
    double sum = 0;
    for (auto Face : m_Faces) {
        sum += Face->Area();
    }
    return sum;
}
/*************************************************************************
【函数名称】Length
【函数功能】获取模型中线的总长度
【参数】无
【返回值】double，表示模型中线的总长度
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
double Model3D::Length() const {
    double sum = 0;
    for (auto Line : m_Lines) {
        sum += Line->Length();
    }
    return sum;
}
/*************************************************************************
【函数名称】BoundingBoxVolume
【函数功能】获取模型的包围盒体积
【参数】无
【返回值】double，表示模型的包围盒体积
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
double Model3D::BoundingBoxVolume() const {
    // 将模型中的所有点的坐标值的最大值和最小值分别赋给
    // MaxX, MinX, MaxY, MinY, MaxZ, MinZ
    double MinX = numeric_limits<double>::infinity();
    double MinY = numeric_limits<double>::infinity();
    double MinZ = numeric_limits<double>::infinity();
    double MaxX = -numeric_limits<double>::infinity();
    double MaxY = -numeric_limits<double>::infinity();
    double MaxZ = -numeric_limits<double>::infinity();
    // 遍历模型中的所有面和线，找到所有点的坐标值的最大值和最小值
    for (auto Face : m_Faces) {
        for (size_t i = 0; i < 3; i++) {
            // 若点的坐标值大于MaxX，则将点的坐标值赋给MaxX
            if (Face->Points[i].X > MaxX) {
                MaxX = Face->Points[i].X;
            }
            // 若点的坐标值小于MinX，则将点的坐标值赋给MinX
            if (Face->Points[i].X < MinX) {
                MinX = Face->Points[i].X;
            }
            // 若点的坐标值大于MaxY，则将点的坐标值赋给MaxY
            if (Face->Points[i].Y > MaxY) {
                MaxY = Face->Points[i].Y;
            }
            // 若点的坐标值小于MinY，则将点的坐标值赋给MinY
            if (Face->Points[i].Y < MinY) {
                MinY = Face->Points[i].Y;
            }
            // 若点的坐标值大于MaxZ，则将点的坐标值赋给MaxZ
            if (Face->Points[i].Z > MaxZ) {
                MaxZ = Face->Points[i].Z;
            }
            // 若点的坐标值小于MinZ，则将点的坐标值赋给MinZ
            if (Face->Points[i].Z < MinZ) {
                MinZ = Face->Points[i].Z;
            }
        }
    }
    // 遍历模型中的所有线，找到所有点的坐标值的最大值和最小值
    for (auto Line : m_Lines) {
        for (size_t i = 0; i < 2; i++) {
            // 若点的坐标值大于MaxX，则将点的坐标值赋给MaxX
            if (Line->Points[i].X > MaxX) {
                MaxX = Line->Points[i].X;
            }
            // 若点的坐标值小于MinX，则将点的坐标值赋给MinX
            if (Line->Points[i].X < MinX) {
                MinX = Line->Points[i].X;
            }
            // 若点的坐标值大于MaxY，则将点的坐标值赋给MaxY
            if (Line->Points[i].Y > MaxY) {
                MaxY = Line->Points[i].Y;
            }
            // 若点的坐标值小于MinY，则将点的坐标值赋给MinY
            if (Line->Points[i].Y < MinY) {
                MinY = Line->Points[i].Y;
            }
            // 若点的坐标值大于MaxZ，则将点的坐标值赋给MaxZ
            if (Line->Points[i].Z > MaxZ) {
                MaxZ = Line->Points[i].Z;
            }
            // 若点的坐标值小于MinZ，则将点的坐标值赋给MinZ
            if (Line->Points[i].Z < MinZ) {
                MinZ = Line->Points[i].Z;
            }
        }
    }
    // 返回包围盒体积
    return (MaxX - MinX) * (MaxY - MinY) * (MaxZ - MinZ);
}
/*************************************************************************
【函数名称】ContainFace
【函数功能】判断模型中是否包含指定面
【参数】const Face3D& AFace, 表示要查找的面
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
bool Model3D::ContainFace(const Face3D& AFace) const {
    for (auto Face : m_Faces) {
        if (*Face == AFace) {
            return true;
        }
    }
    return false;
}
/*************************************************************************
【函数名称】ContainLine
【函数功能】判断模型中是否包含指定线
【参数】const Face3D& AFace, 表示要查找的线
【返回值】无
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
bool Model3D::ContainLine(const Line3D& ALine) const {
    for (auto Line : m_Lines) {
        if (*Line == ALine) {
            return true;
        }
    }
    return false;
}
/*************************************************************************
【函数名称】Faces
【函数功能】获取模型中的面
【参数】无
【返回值】vector<shared_ptr<const Face3D>>，外界无法修改的面列表
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
const vector<shared_ptr<const Face3D>>& Model3D::Faces() const {
    // 静态变量result, 避免每次调用函数都重新分配内存
    static vector<shared_ptr<const Face3D>> result;
    // 清空result之前的内容
    result.clear();
    // 为result预留足够的空间
    result.reserve(m_Faces.size());
    // 遍历m_Faces中的元素，将其转换为shared_ptr<const Face3D>类型，
    // 并添加到result中
    for (const auto& Face : m_Faces) {
        // 使用static_pointer_cast将shared_ptr<Face3D>类型
        // 转换为shared_ptr<const Face3D>类型
        result.push_back(static_pointer_cast<const Face3D>(Face));
    }
    return result;
}
/*************************************************************************
【函数名称】Lines
【函数功能】获取模型中的线
【参数】无
【返回值】vector<shared_ptr<const Line3D>>，外界无法修改的线列表
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
const vector<shared_ptr<const Line3D>>& Model3D::Lines() const {
    // 静态变量result, 避免每次调用函数都重新分配内存
    static vector<shared_ptr<const Line3D>> result;
    // 清空result之前的内容
    result.clear();
    // 为result预留足够的空间
    result.reserve(m_Lines.size());
    // 遍历m_Lines中的元素，将其转换为shared_ptr<const Line3D>类型，
    // 并添加到result中
    for (const auto& Line : m_Lines) {
        // 使用static_pointer_cast将shared_ptr<Line3D>类型
        // 转换为shared_ptr<const Line3D>类型
        result.push_back(static_pointer_cast<const Line3D>(Line));
    }
    return result;
}
/*************************************************************************
【函数名称】operator<<
【函数功能】<<运算符重载，输出模型的信息
【参数】ostream& out, 表示输出流
       const Model3D& AModel, 表示要输出的模型
【返回值】ostream&，表示输出流
【开发者及日期】谭雯心 2024/8/8
【更改记录】
*************************************************************************/
 ostream& operator<<(ostream& out, const Model3D& AModel) {
     out << "Model3D: " << endl;
     out << "Faces: ";
     for (auto Face : AModel.Faces()) {
         out << *Face << endl;
     }
     out << "Lines: ";
     for (auto Line : AModel.Lines()) {
         out << *Line << endl;
     }
     return out;
 }