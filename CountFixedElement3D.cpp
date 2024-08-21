/*************************************************************************
【文件名】CountFixedElement3D.cpp
【功能模块和目的】定义CountFixedElement3D类的成员函数
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/

// CountFixedElement3D所属头文件
#include "CountFixedElement3D.hpp"
// Point3D所属头文件
#include "Point3D.hpp"
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

//-------------------------------------------------------------------------
// 内嵌异常类
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】POINT_COUNT_IS_FIXED
【函数功能】带参构造函数，用于初始化POINT_COUNT_IS_FIXED类的对象
【参数】无
【返回值】无
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
CountFixedElement3D::POINT_COUNT_IS_FIXED::POINT_COUNT_IS_FIXED()
    : logic_error("Point count is fixed.") {
    }
/*************************************************************************
【函数名称】POINT_COUNT_NOT_MATCH
【函数功能】带参构造函数，用于初始化POINT_COUNT_NOT_MATCH类的对象
【参数】无
【返回值】无
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
CountFixedElement3D::POINT_COUNT_NOT_MATCH::POINT_COUNT_NOT_MATCH()
    : logic_error("Point count not match.") {
    }

//-------------------------------------------------------------------------
// 必要的构造、析构、拷贝、赋值运算符重载函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】CountFixedElement3D
【函数功能】默认构造函数，用于初始化CountFixedElement3D类的对象
【参数】size_t PointCount, 表示点的数量
【返回值】无
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
CountFixedElement3D::CountFixedElement3D(size_t PointCount)
    : Element3D(PointCount) {
    }
/*************************************************************************
【函数名称】CountFixedElement3D
【函数功能】带参构造函数，用于初始化CountFixedElement3D类的对象
【参数】initializer_list<Point3D> ilist, 表示Point3D类的对象的列表
【返回值】无
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
CountFixedElement3D::CountFixedElement3D(
    initializer_list<Point3D> List, size_t PointCount)
    : Element3D(List, PointCount) {
    if (List.size() != PointCount) {
        throw POINT_COUNT_NOT_MATCH();
    }
}
/*************************************************************************
【函数名称】CountFixedElement3D
【函数功能】拷贝构造函数，用于初始化CountFixedElement3D类的对象
【参数】const CountFixedElement3D& ACountFixedElement3D,
表示另一个CountFixedElement3D类的对象 【返回值】无 【开发者及日期】谭雯心
2024/8/5 【更改记录】
*************************************************************************/
CountFixedElement3D::CountFixedElement3D(
    const CountFixedElement3D& ACountFixedElement3D)
    : Element3D(ACountFixedElement3D) {
    if (ACountFixedElement3D.CountPoint() != CountPoint()) {
        throw POINT_COUNT_NOT_MATCH();
    }
}
/*************************************************************************
【函数名称】operator=
【函数功能】重载赋值运算符，
    用于将一个CountFixedElement3D类的对象赋值给另一个CountFixedElement3D类的对象
【参数】const CountFixedElement3D& ACountFixedElement3D,
表示另一个CountFixedElement3D类的对象 【返回值】无 【开发者及日期】谭雯心
2024/8/5 【更改记录】
*************************************************************************/
CountFixedElement3D& CountFixedElement3D::operator=(
    const CountFixedElement3D& ACountFixedElement3D) {
    if (this != &ACountFixedElement3D) {
        Element3D::operator=(ACountFixedElement3D);
        if (ACountFixedElement3D.CountPoint() != CountPoint()) {
            throw POINT_COUNT_NOT_MATCH();
        }
    }
    return *this;

}

//-------------------------------------------------------------------------
// 受保护的非静态Setter成员函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】FixedAddPoint
【函数功能】若尝试调用此函数，抛出POINT_COUNT_IS_FIXED异常
【参数】const Point3D& APoint, 表示Point3D类的对象
【返回值】无
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
void CountFixedElement3D::FixedAddPoint(const Point3D& APoint) {
    // 显示标记未使用的参数
    (void)APoint;
    throw POINT_COUNT_IS_FIXED();
}
/*************************************************************************
【函数名称】FixedRemovePoint
【函数功能】若尝试调用此函数，抛出POINT_COUNT_IS_FIXED异常
【参数】size_t Index, 表示点的位置
【返回值】无
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
void CountFixedElement3D::FixedRemovePoint(size_t Index) {
    // 显示标记未使用的参数
    (void)Index;
    throw POINT_COUNT_IS_FIXED();
}
/*************************************************************************
【函数名称】FixedRemovePoint
【函数功能】若尝试调用此函数，抛出POINT_COUNT_IS_FIXED异常
【参数】const Point3D& APoint, 表示Point3D类的对象
【返回值】无
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
void CountFixedElement3D::FixedRemovePoint(const Point3D& APoint) {
    // 显示标记未使用的参数
    (void)APoint;
    throw POINT_COUNT_IS_FIXED();
}
/*************************************************************************
【函数名称】FixedClearPoint
【函数功能】若尝试调用此函数，抛出POINT_COUNT_IS_FIXED异常
【参数】无
【返回值】无
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
void CountFixedElement3D::FixedClearPoint() { 
    throw POINT_COUNT_IS_FIXED();
}

//-------------------------------------------------------------------------
// 受保护的非静态Getter成员函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】FixedCountPoint
【函数功能】获取CounrFixedElement3D类的点数
【参数】无
【返回值】size_t，表示点的数量
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
size_t CountFixedElement3D::FixedCountPoint() const {
    return Points.MaxElementCount();
}
