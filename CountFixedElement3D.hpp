/*************************************************************************
【文件名】CountFixedElement3D.hpp
【功能模块和目的】定义CountFixedElement3D类，表示三维空间中的元素，点数固定
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
#ifndef COUNTFIXEDELEMENT3D_HPP
#define COUNTFIXEDELEMENT3D_HPP

// Point3D所属头文件
#include "Point3D.hpp"
// Element3D所属头文件
#include "Element3D.hpp"
// initializer_list所属头文件
#include <initializer_list>
// logic_error所属头文件
#include <stdexcept>
// string所属头文件
#include <string>
// size_t所属头文件
#include <cstddef>
// numeric_limits所属头文件
#include <limits>

using namespace std;

/*************************************************************************
【类名】CountFixedElement3D
【功能】定义CountFixedElement3D类，表示三维空间中的元素，点数固定
【接口说明】
    默认构造函数
    带参构造函数
    拷贝构造函数
    赋值运算符
    虚析构函数
    向点集合中添加点（固定点数）
    删除点集合中的某个位置的点（固定点数）
    删除点集合中的某个点（固定点数）
    清空点集合（固定点数）
    派生类接口：计算长度（纯虚函数）
    派生类接口：计算面积（纯虚函数）
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/

class CountFixedElement3D : public Element3D {
public:
    //-------------------------------------------------------------------------
    // 内嵌异常类
    //-------------------------------------------------------------------------
    // 点数固定异常类
    class POINT_COUNT_IS_FIXED : public logic_error {
    public:
        POINT_COUNT_IS_FIXED();
    };
    class POINT_COUNT_NOT_MATCH : public logic_error {
    public:
        POINT_COUNT_NOT_MATCH();
    };
    //-------------------------------------------------------------------------
    // 必要的构造、析构、拷贝、赋值运算符重载函数
    //-------------------------------------------------------------------------
    // 默认构造函数
    CountFixedElement3D(size_t PointCount = numeric_limits<size_t>::max());
    // 带参构造函数
    CountFixedElement3D(initializer_list<Point3D> List, 
        size_t PointCount = numeric_limits<size_t>::max());
    // 拷贝构造函数
    CountFixedElement3D(const CountFixedElement3D& ACountFixedElement3D);
    // 赋值运算符
    CountFixedElement3D& operator=(
        const CountFixedElement3D& ACountFixedElement3D);
    // 析构函数
    virtual ~CountFixedElement3D() = default;
    //-------------------------------------------------------------------------
    // 非静态Getter成员函数（纯虚函数）
    //-------------------------------------------------------------------------
    // 计算长度
    virtual double Length() const = 0;
    // 计算面积
    virtual double Area() const = 0;
protected:
    //-------------------------------------------------------------------------
    // 受保护的非静态成员函数
    //-------------------------------------------------------------------------
    // 重载基类向点集合中添加点（固定点数）
    virtual void FixedAddPoint(const Point3D& APoint) override;
    // 重载基类删除点集合中的某个位置的点（固定点数）
    virtual void FixedRemovePoint(size_t Index) override;
    // 重载基类删除点集合中的某个点（固定点数）
    virtual void FixedRemovePoint(const Point3D& APoint) override;
    // 重载基类清空点集合（固定点数）
    virtual void FixedClearPoint() override;
    //-------------------------------------------------------------------------
    // 受保护的非静态Getter成员函数
    //-------------------------------------------------------------------------
    // 重载基类直接获取Element3D类的点数
    virtual size_t FixedCountPoint() const override; 
private:
    //-------------------------------------------------------------------------
    // 私有数据成员
    //-------------------------------------------------------------------------
    // 点数
    size_t m_PointCount;
};

#endif /* CountFixedElement3D.hpp */