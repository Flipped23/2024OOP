/*************************************************************************
【文件名】Vector.cpp
【功能模块和目的】三维向量类模板的定义与实现，存储T类型的三维向量
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

// Vector所属头文件
#include "Vector.hpp"
// size_t所属头文件
#include <cstddef>
// pow所属头文件
#include <cmath>
// initializer_list所属头文件
#include <initializer_list>

using namespace std;

/*************************************************************************
【类名】Vector3D
【功能】定义三维向量类模板，存储T类型的三维向量
【接口说明】
    默认构造函数
    带参构造函数
    拷贝构造函数
    赋值运算符
    虚析构函数
    重载基类求p范数函数
    重载基类外积函数
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/

template <typename T>
class Vector3D : public Vector<T, 3> {
public:
    //-------------------------------------------------------------------------
    // 必要的构造、析构、拷贝、赋值运算符重载函数
    //-------------------------------------------------------------------------
    // 默认构造函数
    Vector3D() = default;
    // 带参构造函数
    Vector3D(initializer_list<T> List);
    // 拷贝构造函数
    Vector3D(const Vector3D& AVector);
    // 赋值运算符
    Vector3D& operator=(const Vector3D& AVector);
    // 虚析构函数
    virtual ~Vector3D() = default;

private:
    //-------------------------------------------------------------------------
    // 私有成员函数，重载基类函数
    //-------------------------------------------------------------------------
    // 重载基类求p范数函数
    T InnerL(size_t p) const override;
    // 重载基类外积函数
    Vector<T, 3> InnerCrossProduct(const Vector<T, 3>& AVector) const override;
};

//-------------------------------------------------------------------------
// 必要的构造、析构、拷贝、赋值运算符重载函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】Vector3D
【函数功能】带参构造函数，根据initializer_list初始化向量的分量
【参数】initializer_list<T> List，初始化列表
【返回值】无
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
Vector3D<T>::Vector3D(initializer_list<T> List) : Vector<T, 3>(List) {
}
/*************************************************************************
【函数名称】Vector3D
【函数功能】拷贝构造函数
【参数】const Vector3D& AVector，另一个三维向量
【返回值】无
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
Vector3D<T>::Vector3D(const Vector3D& AVector) : Vector<T, 3>(AVector) {
}
/*************************************************************************
【函数名称】operator=
【函数功能】重载赋值运算符，将一个三维向量赋值给另一个三维向量
【参数】const Vector3D& AVector，另一个三维向量
【返回值】Vector3D&，赋值后的三维向量
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
Vector3D<T>& Vector3D<T>::operator=(const Vector3D& AVector) {
    // 若两个向量不同，调用基类赋值运算符
    if (this != &AVector) {
        Vector<T, 3>::operator=(AVector);
    }
    return *this;
}

//-------------------------------------------------------------------------
// 私有成员函数，重载基类函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】InnerL
【函数功能】重载基类求p范数函数，求向量的p范数
【参数】size_t p，范数的p值
【返回值】T类型，向量的p范数
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
T Vector3D<T>::InnerL(size_t p) const {
    T sum = 0;
    // 求三维向量的p范数
    for (size_t i = 0; i < 3; i++) {
        sum += pow(this->Components[i], p);
    }
    return pow(sum, 1.0 / p);
}
/*************************************************************************
【函数名称】InnerCrossProduct
【函数功能】重载基类外积函数，求两个三维向量的外积
【参数】const Vector<T, 3>& AVector，另一个三维向量
【返回值】Vector<T, 3>类型，两个三维向量的外积
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
Vector<T, 3> Vector3D<T>::InnerCrossProduct(const Vector<T, 3>& AVector) const {
    Vector<T, 3> result;
    // 求两个三维向量的外积
    result.SetVector(0, this->Components[1] * AVector.Components[2]
        - this->Components[2] * AVector.Components[1]);
    result.SetVector(1, this->Components[2] * AVector.Components[0] 
        - this->Components[0] * AVector.Components[2]);
    result.SetVector(2, this->Components[0] * AVector.Components[1] 
        - this->Components[1] * AVector.Components[0]);
    return result;
}

#endif /* Vector3D.hpp */
