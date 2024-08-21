/*************************************************************************
【文件名】Point3D.hpp
【功能模块和目的】定义Point3D类，继承自Vector3D类，表示三维空间中的点
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
#ifndef POINT3D_HPP
#define POINT3D_HPP

// Vector3D所属头文件
#include "Vector3D.hpp"
// size_t所属头文件
#include <cstddef>
// pow所属头文件
#include <cmath>

using namespace std;

/*************************************************************************
【类名】Point3D
【功能】定义Point3D类，继承自Vector3D类，表示三维空间中的点
【接口说明】
    默认构造函数
    带参构造函数
    拷贝构造函数
    重载赋值运算符
    虚析构函数
    两点间距离函数
    设置X坐标
    设置Y坐标
    设置Z坐标
    设置X, Y, Z坐标
    通过X, Y, Z获取点坐标
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/

class Point3D : public Vector3D<double> {
public:
    //-------------------------------------------------------------------------
    // 必要的构造、析构、拷贝、赋值运算符重载函数
    //-------------------------------------------------------------------------
    // 默认构造函数
    Point3D() = default;
    // 带参构造函数
    Point3D(double x, double y, double z);
    // 拷贝构造函数
    Point3D(const Point3D& APoint);
    // 重载赋值运算符
    Point3D& operator=(const Point3D& APoint);
    // 虚析构函数
    virtual ~Point3D() = default;
    //-------------------------------------------------------------------------
    // 非静态Getter成员函数
    //-------------------------------------------------------------------------
    // 计算两点间的距离
    double Distance(const Point3D& APoint) const;
    // X存储点的X坐标
    const double& X{Components[0]};
    // Y存储点的Y坐标
    const double& Y{Components[1]};
    // Z存储点的Z坐标
    const double& Z{Components[2]};
    //-------------------------------------------------------------------------
    // 非静态Setter成员函数
    //-------------------------------------------------------------------------
    // 设置X坐标
    void SetX(double x);
    // 设置Y坐标
    void SetY(double y);
    // 设置Z坐标
    void SetZ(double z);
    // 设置X, Y, Z坐标
    void Set(double x, double y, double z);
    //-------------------------------------------------------------------------
    // 禁用的成员函数和重载运算符
    //-------------------------------------------------------------------------
    // 禁用+运算符（点没有加法行为）
    Point3D operator+(const Point3D& APoint) const = delete;
    // 禁用-运算符（点没有减法行为）
    Point3D operator-(const Vector& APoint) const = delete;
    // 禁用*运算符（点没有叉乘行为）
    Point3D operator*(const Vector& APoint) const = delete;
    // 禁用*运算符（点没有乘法行为）
    Point3D operator*(const double& AScalar) const = delete;
    // 禁用+=运算符（点没有加法行为）
    Point3D& operator*=(const Point3D& APoint) = delete;
    // 禁用-=运算符（点没有减法行为）
    Point3D& operator-=(const Vector& APoint) = delete;
    // 禁用+=运算符（点没有加法行为）
    Point3D& operator+=(const Vector& APoint) = delete;
    // 禁用-=运算符（点没有减法行为）
    Point3D& operator*=(const double& AScalar) = delete;
    // 点无求L0范数行为
    double L0() const = delete;
    // 点无求L1范数行为
    double L1() const = delete;
    // 点无求L2范数行为
    double L2() const = delete;
    // 点无求Lp范数行为
    double L(size_t p) const = delete;
    // 点无求无穷范数行为
    double Lmax() const = delete;
    // 点无求模长行为
    double Module() const = delete;
    // 点无求长度行为
    double Length() const = delete;
    // 点无叉乘行为
    Vector3D<double> CrossProduct(const Point3D& APoint) const = delete;
};

#endif /* Point3D.hpp */