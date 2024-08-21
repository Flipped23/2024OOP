/*************************************************************************
【文件名】Model3D.hpp
【功能模块和目的】定义Model3D类，表示三维空间中包含线和面的模型
【开发者及日期】谭雯心 2024/8/8
【更改记录】2024/8/10 谭雯心
修改了向模型中添加面、线，修改面和线中点的函数名称和参数 2024/8/9 谭雯心
修改了获取模型信息的逻辑
*************************************************************************/
#ifndef MODEL3D_HPP
#define MODEL3D_HPP

// Face3D所属头文件
#include "Face3D.hpp"
// Line3D所属头文件
#include "Line3D.hpp"
// Point3D所属头文件
#include "Point3D.hpp"
// shared_ptr所属头文件
#include <memory>
// logic_error所属头文件
#include <stdexcept>
// string所属头文件
#include <string>
// vector所属头文件
#include <vector>
// size_t所属头文件
#include <cstddef>

using namespace std;

/*************************************************************************
【类名】Model3D
【功能】定义Model3D类，表示三维空间中包含线和面的模型
【接口说明】
    默认构造函数
    带参构造函数
    拷贝构造函数
    重载赋值运算符
    虚析构函数
    向模型中添加面
    删除模型中已有的面
    修改模型中的面
    修改模型中面的特定点
    修改模型中面的指定位置的点
    清空模型中的面
    向模型中添加线
    删除模型中已有的线
    修改模型中的线
    修改模型中线的特定点
    修改模型中线的指定位置的点
    清空线
    清空所有面和线
    +=运算符重载，合并两个模型
    +=运算符重载，合并面到模型
    +=运算符重载，合并线到模型
    -=运算符重载，从模型中删除模型
    -=运算符重载，从模型中删除面
    -=运算符重载，从模型中删除线
    ==运算符重载，判断两个模型是否相等
    !=运算符重载，判断两个模型是否不相等
    +运算符重载，合并两个模型
    +运算符重载，合并面到模型
    +运算符重载，合并线到模型
    -运算符重载，从模型中删除模型
    -运算符重载，从模型中删除面
    -运算符重载，从模型中删除线
    拷贝模型
    获取模型中点的总数量
    获取模型中元素的总数量
    获取模型中面的总数量
    获取模型中线的总数量
    获取模型面的总面积
    获取模型中线的总长度
    获取包围盒的体积
    判断模型中是否包含指定面
    判断模型中是否包含指定线
【开发者及日期】谭雯心 2024/8/8
【更改记录】2024/8/10 谭雯心
修改了向模型中添加面、线，修改面和线中点的函数名称和参数 2024/8/9 谭雯心
修改了获取模型信息的逻辑
*************************************************************************/

class Model3D {
public:
    //-------------------------------------------------------------------------
    // 内嵌异常类
    //-------------------------------------------------------------------------
    // 面已存在类异常
    class FACE_ALREADY_EXISTS : public logic_error {
    public:
        FACE_ALREADY_EXISTS();
    };
    // 面未找到类异常
    class FACE_NOT_FOUND : public logic_error {
    public:
        FACE_NOT_FOUND();
    };
    // 线已存在类异常
    class LINE_ALREADY_EXISTS : public logic_error {
    public:
        LINE_ALREADY_EXISTS();
    };
    // 线未找到类异常
    class LINE_NOT_FOUND : public logic_error {
    public:
        LINE_NOT_FOUND();
    };
    // 点已存在类异常
    class POINT_DUPLICATED : public logic_error {
    public:
        POINT_DUPLICATED();
    };
    // 点未找到类异常
    class POINT_NOT_FOUND : public logic_error {
    public:
        POINT_NOT_FOUND();
    };
    //-------------------------------------------------------------------------
    // 必要的构造、析构、拷贝、赋值运算符重载函数
    //-------------------------------------------------------------------------
    // 默认构造函数
    Model3D() = default;
    // 带参构造函数
    Model3D(vector<Line3D> Lines, vector<Face3D> Faces);
    // 拷贝构造函数
    Model3D(const Model3D& Source);
    // 重载赋值运算符
    Model3D& operator=(const Model3D& Source);
    // 虚析构函数
    virtual ~Model3D() = default;
    //-------------------------------------------------------------------------
    // 非静态Setter成员函数
    //-------------------------------------------------------------------------
    // 向模型中添加面
    void AddFace(const Face3D& AFace);
    // 向模型中添加面
    void AddFace(const Point3D& Point1, const Point3D& Point2,
                 const Point3D& Point3);
    // 删除模型中已有的面
    void RemoveFace(const Face3D& AFace);
    // 删除模型中已有的面
    void RemoveFace(const Point3D& Point1, const Point3D& Point2,
                    const Point3D& Point3);
    // 删除模型中已有的面
    void RemoveFace(size_t FaceIndex);
    // 修改模型中已有的面
    void ChangeFace(const Face3D& FaceFrom, const Face3D& FaceTo);
    // 修改模型中已有的面
    void ChangeFace(size_t FaceIndex, const Face3D& AFace);
    // 修改模型中面的指定点
    void ChangeFacePoint(const Face3D& AFace, const Point3D& PointFrom,
                         const Point3D& PointTo);
    // 修改模型中面的指定点
    void ChangeFacePoint(size_t FaceIndex, const Point3D& PointFrom,
                         const Point3D& PointTo);
    // 修改模型中面的指定点
    void ChangeFacePoint(const Face3D& AFace, size_t PointIndex,
                         const Point3D& PointTo);
    // 修改模型中面的指定点
    void ChangeFacePoint(size_t FaceIndex, size_t PointIndex,
                         const Point3D& PointTo);
    // 清空模型中的面
    void ClearFaces();
    // 向模型中添加线
    void AddLine(const Line3D& ALine);
    // 向模型中添加线
    void AddLine(const Point3D& Point1, const Point3D& Point2);
    // 删除模型中已有的线
    void RemoveLine(const Line3D& ALine);
    // 删除模型中已有的线
    void RemoveLine(const Point3D& Point1, const Point3D& Point2);
    // 删除模型中已有的线
    void RemoveLine(size_t LineIndex);
    // 修改模型中的线
    void ChangeLine(const Line3D& LineFrom, const Line3D& LineTo);
    // 修改模型中的线
    void ChangeLine(size_t LineIndex, const Line3D& ALine);
    // 修改模型中线的指定点
    void ChangeLinePoint(const Line3D& ALine, const Point3D& PointFrom,
                         const Point3D& PointTo);
    // 修改模型中线的指定点
    void ChangeLinePoint(size_t LineIndex, const Point3D& PointFrom,
                         const Point3D& PointTo);
    // 修改模型中线的指定点
    void ChangeLinePoint(const Line3D& ALine, size_t PointIndex,
                         const Point3D& PointTo);
    // 修改模型中线的指定点
    void ChangeLinePoint(size_t LineIndex, size_t PointIndex,
                         const Point3D& PointTo);
    // 清空线
    void ClearLines();
    // 清空所有面和线
    void Clear();
    //+=运算符重载，合并两个模型
    Model3D& operator+=(const Model3D& AModel);
    //+=运算符重载，合并面到模型
    Model3D& operator+=(const vector<Face3D>& Faces);
    //+=运算符重载，合并线到模型
    Model3D& operator+=(const vector<Line3D>& Lines);
    //-=运算符重载，从模型中删除模型
    Model3D& operator-=(const Model3D& AModel);
    //-=运算符重载，从模型中删除面
    Model3D& operator-=(const vector<Face3D>& Faces);
    //-=运算符重载，从模型中删除线
    Model3D& operator-=(const vector<Line3D>& Lines);
    //-------------------------------------------------------------------------
    // 非静态Getter成员函数
    //-------------------------------------------------------------------------
    //==运算符重载，判断两个模型是否相等
    bool operator==(const Model3D& AModel) const;
    //!=运算符重载，判断两个模型是否不相等
    bool operator!=(const Model3D& AModel) const;
    //+运算符重载，合并两个模型
    Model3D operator+(const Model3D& AModel) const;
    //+运算符重载，合并面到模型
    Model3D operator+(const vector<Face3D>& Faces) const;
    //+运算符重载，合并线到模型
    Model3D operator+(const vector<Line3D>& Lines) const;
    //-运算符重载，从模型中删除模型
    Model3D operator-(const Model3D& AModel) const;
    //-运算符重载，从模型中删除面
    Model3D operator-(const vector<Face3D>& Faces) const;
    //-运算符重载，从模型中删除线
    Model3D operator-(const vector<Line3D>& Lines) const;
    // 拷贝模型
    Model3D Copy() const;
    // 获取模型中的面
    const vector<shared_ptr<const Face3D>>& Faces() const;
    // 获取模型中的线
    const vector<shared_ptr<const Line3D>>& Lines() const;
    // 获取模型中点的总数量
    size_t GetPointCount() const;
    // 获取模型中元素的总数量
    size_t GetElementCount() const;
    // 获取模型中面的总数量
    size_t GetFaceCount() const;
    // 获取模型中线的总数量
    size_t GetLineCount() const;
    // 获取模型面的总面积
    double Area() const;
    // 获取模型中线的总长度
    double Length() const;
    // 获取包围盒的体积
    double BoundingBoxVolume() const;
    // 判断模型中是否包含指定面
    bool ContainFace(const Face3D& AFace) const;
    // 判断模型中是否包含指定线
    bool ContainLine(const Line3D& ALine) const;
    // ------------------------------------------------------------------------
    // 公有数据成员
    // ------------------------------------------------------------------------
    // 模型名称
    string Name{string("EMPTY")};
    // 模型注释
    string Description{string("EMPTY")};
    //-------------------------------------------------------------------------
    // 友元函数
    //-------------------------------------------------------------------------
    // 重载流插入运算符
    friend ostream& operator<<(ostream& out, const Model3D& AModel);

private:
    //-------------------------------------------------------------------------
    // 私有非静态成员
    //-------------------------------------------------------------------------
    // 私有vector<shared_ptr<Line3D>>类型成员，存储模型中的所有线
    vector<shared_ptr<Line3D>> m_Lines{};
    // 私有vector<shared_ptr<Face3D>>类型成员，存储模型中的所有面
    vector<shared_ptr<Face3D>> m_Faces{};
};

#endif /* Model3D.hpp */