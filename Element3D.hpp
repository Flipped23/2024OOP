/*************************************************************************
【文件名】Element3D.hpp
【功能模块和目的】定义Element3D类，表示三维空间中的元素
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
#ifndef ELEMENT3D_HPP
#define ELEMENT3D_HPP

// Point3DSet所属头文件
#include "Point3DSet.hpp"
// Point3D所属头文件
#include "Point3D.hpp"
// initializer_list所属头文件
#include <initializer_list>
// 流操作所属头文件
#include <iostream>
// vector所属头文件
#include <vector>
// vector操作所属头文件
#include <algorithm>
#include <functional>
// 异常类所属头文件
#include <stdexcept>
// string所属头文件
#include <string>
// size_t所属头文件
#include <cstddef>
// numeric_limits所属头文件
#include <limits>

using namespace std;

/*************************************************************************
【类名】Element3D
【功能】定义Element3D类，表示三维空间中的元素
【接口说明】
    默认构造函数
    带参构造函数
    拷贝构造函数
    重载赋值运算符
    虚析构函数
    直接获取Element3D类的点集合
    直接获取Element3D类的点数
    重载==运算符
    重载!=运算符
    向点集合中添加点
    删除点集合中的某个位置的点
    删除点集合中的某个点
    修改点集合中的某个点到另一个点
    修改点集合中的某个位置的点
    清空点集合
    重载流插入运算符
    派生类接口：计算长度
    派生类接口：计算面积
    派生类接口：向点集合中添加点（按照派生类的规则添加点）
    派生类接口：删除指定点（按照派生类的规则删除点）
    派生类接口：删除指定位置的点（按照派生类的规则删除点）
    派生类接口：修改指定点（按照派生类的规则修改点）
    派生类接口：修改指定位置的点（按照派生类的规则修改点）
    派生类接口：清空集合中的点（按照派生类的规则清空点）
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/

class Element3D {
public:
    //-------------------------------------------------------------------------
    // 必要的构造、析构、拷贝、赋值运算符重载函数
    //-------------------------------------------------------------------------
    // 默认构造函数
    Element3D(size_t MaxPointCount = numeric_limits<size_t>::max());
    // 带参构造函数
    Element3D(initializer_list<Point3D> List,
        size_t MaxPointCount = numeric_limits<size_t>::max());
    // 拷贝构造函数
    Element3D(const Element3D& Source);
    // 赋值运算符
    Element3D& operator=(const Element3D& Source);
    // 析构函数
    virtual ~Element3D() = default;
    //-------------------------------------------------------------------------
    // 非静态Getter成员函数
    //-------------------------------------------------------------------------
    // 直接获取Element3D类的点数
    size_t CountPoint() const;
    // 重载==运算符
    bool operator==(const Element3D& AElement) const;
    // 重载!=运算符
    bool operator!=(const Element3D& AElement) const;
    // 计算长度，纯虚函数，作为派生类接口
    virtual double Length() const = 0;
    // 计算面积，纯虚函数，作为派生类接口
    virtual double Area() const = 0;
    //-------------------------------------------------------------------------
    // 非静态Setter成员函数
    //-------------------------------------------------------------------------
    // 向点集合中添加点
    void AddPoint(const Point3D& APoint);
    // 删除点集合中的某个位置的点
    void RemovePoint(size_t Index);
    // 删除点集合中的某个点
    void RemovePoint(const Point3D& APoint);
    // 修改点集合中的某个点到另一个点
    void ChangePoint(const Point3D& From, const Point3D& To);
    // 修改点集合中的某个位置的点
    void ChangePoint(const Point3D& APoint, size_t Index);
    // 清空点集合
    void ClearPoint(); 
    //-------------------------------------------------------------------------
    // 公有非静态数据成员
    //-------------------------------------------------------------------------
    // 直接获取Element3D类的点集合
    const Point3DSet& Points{m_Points};
    //-------------------------------------------------------------------------
    // 友元函数
    //-------------------------------------------------------------------------
    // 重载流插入运算符
    friend ostream& operator<<(ostream& out, const Element3D& AElement);

protected:
    //-------------------------------------------------------------------------
    // 受保护的非静态Setter成员函数
    //-------------------------------------------------------------------------
    // 向点集合中添加点（Element3D中点的数量固定）
    virtual void FixedAddPoint(const Point3D& APoint);
    // 删除指定点（Element3D中点的数量固定）
    virtual void FixedRemovePoint(size_t Index);
    // 删除指定位置的点（Element3D中点的数量固定）
    virtual void FixedRemovePoint(const Point3D& APoint);
    // 修改指定位置的点（Element3D中点的数量固定）
    virtual void FixedChangePoint(const Point3D& APoint, size_t Index);
    // 修改指定的点（Element3D中点的数量固定）
    virtual void FixedChangePoint(const Point3D& From, const Point3D& To);
    // 清空集合中的点（Element3D中点的数量固定）
    virtual void FixedClearPoint();
    //-------------------------------------------------------------------------
    // 受保护的非静态Getter成员函数
    //-------------------------------------------------------------------------
    // 获取Element3D类的点数（Element3D中点的数量固定）
    virtual size_t FixedCountPoint() const;
private:
    // 点集合
    Point3DSet m_Points;
};

#endif /* Element3D.hpp */