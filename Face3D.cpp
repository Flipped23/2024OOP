/*************************************************************************
【文件名】Face3D.cpp
【功能模块和目的】定义Face3D类的成员函数
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/

// Face3D所属头文件
#include "Face3D.hpp"
// Point3D所属头文件
#include "Point3D.hpp"
// CountFixedElement3D所属头文件
#include "CountFixedElement3D.hpp"
// pow, sqrt所属头文件
#include <cmath>

using namespace std;

//-------------------------------------------------------------------------
// 必要的构造、析构、拷贝、赋值运算符重载函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】Face3D
【函数功能】默认构造函数，用于初始化Face3D类的对象
【参数】无
【返回值】无
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
Face3D::Face3D() : CountFixedElement3D(3) { // 3表示面的点数为3
} 
/*************************************************************************
【函数名称】Face3D
【函数功能】带参构造函数，用于初始化Face3D类的对象
【参数】const Point3D& Point1, const Point3D& Point2, const Point3D& Point3
【返回值】无
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
Face3D::Face3D(const Point3D& Point1, const Point3D& Point2,
    const Point3D& Point3) : CountFixedElement3D({Point1, Point2, Point3}, 3) {
    }  // 3表示面的点数为3
/*************************************************************************
【函数名称】Face3D
【函数功能】拷贝构造函数，用于初始化Face3D类的对象
【参数】const Face3D& Source, 表示另一个Face3D类的对象
【返回值】无
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
Face3D::Face3D(const Face3D& Source) : CountFixedElement3D(Source) {
}
/*************************************************************************
【函数名称】operator=
【函数功能】重载赋值运算符，用于将一个Face3D类的对象赋值给另一个Face3D类的对象
【参数】const Face3D& Source, 表示另一个Face3D类的对象
【返回值】Face3D类的对象的引用
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
Face3D& Face3D::operator=(const Face3D& Source) {
    if (this != &Source) {
        CountFixedElement3D::operator=(Source);
    }
    return *this;
}
/*************************************************************************
【函数名称】Area
【函数功能】计算三维空间中的面的面积
【参数】无
【返回值】double类型，表示三维空间中的面的面积
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
double Face3D::Area() const {
    // 用海伦公式求面积
    double a = Points[0].Distance(Points[1]);
    double b = Points[1].Distance(Points[2]);
    double c = Points[2].Distance(Points[0]);
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}
/*************************************************************************
【函数名称】Length
【函数功能】计算三维空间中的面的周长
【参数】无
【返回值】double类型，表示三维空间中的面的周长
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
double Face3D::Length() const {
    return Points[0].Distance(Points[1])
        + Points[1].Distance(Points[2])
        + Points[2].Distance(Points[0]);
}
