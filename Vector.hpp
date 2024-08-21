/*************************************************************************
【文件名】Vector.cpp
【功能模块和目的】向量类模板的定义与实现，存储T类型的N维向量
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
#ifndef VECTOR_HPP
#define VECTOR_HPP

// array所属头文件
#include <array>
// pow, sqrt, abs等数学函数所属头文件
#include <cmath>
// cin, cout, endl所属头文件
#include <iostream>
// runtime_error, out_of_range所属头文件
#include <stdexcept>
// initializer_list所属头文件
#include <initializer_list>
// numeric_limits所属头文件
#include <limits>
// vector所属头文件
#include <vector>
// vector操作所属头文件
#include <algorithm>
#include <functional>
// string所属头文件
#include <string>
// size_t所属头文件
#include <cstddef>

using namespace std;

// 向量类模板的前置声明，用于友元函数的定义
template <typename T, size_t N>
class Vector;

/*************************************************************************
【函数名称】operator<<
【函数功能】流插入运算符重载，输出向量
【参数】istream& in，输入流；
       Vector<T, N>& AVector，向量
【返回值】ostream&，输出流
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
ostream& operator<<(ostream& out, const Vector<T, N>& AVector) {
    // 以(x1, x2...)形式输出向量各个分量
    out << "(";
    for (size_t i = 0; i < N; i++) {
        out << AVector.Components[i];
        if (i != N - 1) {
            out << ", ";
        }
    }
    out << ")";
    return out;
}
/*************************************************************************
【函数名称】operator>>
【函数功能】流提取运算符重载，输入向量
【参数】istream& in，输入流；
       Vector<T, N>& AVector，向量
【返回值】istream&，输入流
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
istream& operator>>(istream& in, Vector<T, N>& AVector) {
    // 输入向量各个分量
    for (size_t i = 0; i < N; i++) {
        in >> AVector.Components[i];
    }
    return in;
}

/*************************************************************************
【类名】Vector
【功能】T类型的N维向量模板类，提供向量的基本运算和范数计算
【接口说明】
    默认构造函数
    带参构造函数
    拷贝构造函数
    赋值运算符重载
    虚析构函数
    返回分量引用的[]运算符重载
    返回向量引用的+运算符重载
    返回向量引用的-运算符重载
    返回向量引用的*运算符重载
    返回向量引用的*（叉乘）运算符重载
    求向量的L0范数
    求向量的L1范数
    求向量的L2范数
    求向量的Lp范数
    求向量的无穷范数
    求向量的模（同向量的L2范数）
    求向量的长度（同向量的L2范数）
    判断向量是否相等的运算符重载
    判断向量是否不等的运算符重载
    返回向量的叉乘
    返回向量引用的+=运算符重载
    返回向量引用的-=运算符重载
    返回向量引用的*=（数乘）运算符重载
    返回向量引用的*=（叉乘）运算符重载
    设置向量的分量
    设置向量的分量数组
    友元函数，流插入运算符，输出向量
    友元函数，流提取运算符，输入向量
    存储分量的数组数据成员Component
    存储维数大小的常量数据成员DIMENSION
    派生类接口：实际的求向量的Lp范数
    派生类接口：实际的返回向量的叉乘
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
class Vector {
public:
    //-------------------------------------------------------------------------
    // 内嵌异常类
    //-------------------------------------------------------------------------
    // 向量维数超出范围异常类
    class VECTOR_SIZE_ERROR : public out_of_range {
    public:
        VECTOR_SIZE_ERROR() : out_of_range("Vector size out of range") {
        }
    };
    // 叉乘未定义异常类
    class CROSS_PRODUCT_NOT_DEFINED : logic_error {
    public:
        CROSS_PRODUCT_NOT_DEFINED()
            : logic_error(
                  "Cross product is not defined for this type of vector.") {
                  }
    };
    // Lp范数未定义异常类
    class LP_NORM_NOT_DEFINED : logic_error {
    public:
        LP_NORM_NOT_DEFINED()
            : logic_error("Lp norm is not defined for this type of vector.") {
            }
    };
    //-------------------------------------------------------------------------
    // 必要的构造、析构、拷贝、赋值运算符重载函数
    //-------------------------------------------------------------------------
    // 默认构造函数
    Vector() = default;
    // 带参构造函数
    Vector(initializer_list<T> List);
    // 拷贝构造函数
    Vector(const Vector<T, N>& AVector);
    // 赋值运算符重载
    Vector<T, N>& operator=(const Vector<T, N>& AVector);
    // 析构函数
    virtual ~Vector() = default;
    //-------------------------------------------------------------------------
    // 非静态Getter成员函数
    //-------------------------------------------------------------------------
    // 返回分量引用的下标运算符重载
    T operator[](size_t Index) const;
    // 返回向量引用的和运算符重载
    Vector<T, N> operator+(const Vector<T, N>& AVector) const;
    // 返回向量引用的差运算符重载
    Vector<T, N> operator-(const Vector<T, N>& AVector) const;
    // 返回向量引用的叉乘运算符重载
    Vector<T, N> operator*(const Vector<T, N>& AVector) const;
    // 返回向量引用的数乘运算符重载
    Vector<T, N> operator*(const T& AScalar) const;
    // 求向量的L0范数
    T L0() const;
    // 求向量的L1范数
    T L1() const;
    // 求向量的L2范数
    T L2() const;
    // 求向量的Lp范数
    T L(size_t p) const;
    // 求向量的无穷范数
    T Lmax() const;
    // 求向量的模（同向量的L2范数）
    T Module() const;
    // 求向量的长度（同向量的L2范数）
    T Length() const;
    // 判断向量是否相等
    bool operator==(const Vector<T, N>& AVector) const;
    // 判断向量是否不等
    bool operator!=(const Vector<T, N>& AVector) const;
    // 返回向量的叉乘
    Vector<T, N> CrossProduct(const Vector<T, N>& AVector) const;
    //-------------------------------------------------------------------------
    // 非静态Setter成员函数
    //-------------------------------------------------------------------------
    // 返回向量引用的和运算符重载
    Vector<T, N>& operator+=(const Vector<T, N>& AVector);
    // 返回向量引用的差运算符重载
    Vector<T, N>& operator-=(const Vector<T, N>& AVector);
    // 返回向量引用的叉乘运算符重载
    Vector<T, N>& operator*=(const Vector<T, N>& AVector);
    // 返回向量引用的数乘运算符重载
    Vector<T, N>& operator*=(const T& AScalar);
    // 设置向量的分量
    void SetVector(size_t Index, T Value);
    // 设置向量的分量数组
    void SetVector(const array<T, N>& AComponents);
    // 流插入运算符重载，友元函数
    friend ostream& operator<< <T, N>(ostream& out,
                                      const Vector<T, N>& AVector);
    // 流提取运算符重载，友元函数
    friend istream& operator>> <T, N>(istream& in, Vector<T, N>& AVector);
    //-------------------------------------------------------------------------
    // 非静态数据成员
    //-------------------------------------------------------------------------
    // 定义ComponentsType为T[N]类型，存储向量的分量，因为无访问规则，所以为public
    using ComponentsType = T[N];
    const ComponentsType& Components{m_Components};
    //-------------------------------------------------------------------------
    // 静态数据成员
    //-------------------------------------------------------------------------
    // 常量数据成员，存储维数大小N
    static constexpr size_t DIMENSION{N};

protected:
    //-------------------------------------------------------------------------
    // 受保护的非静态Getter成员函数
    //-------------------------------------------------------------------------
    // 实际的求向量的Lp范数，由派生类实现
    virtual T InnerL(size_t p) const;
    // 实际的返回向量的叉乘，由派生类实现
    virtual Vector<T, N> InnerCrossProduct(const Vector<T, N>& AVector) const;

private:
    //-------------------------------------------------------------------------
    // 私有数据成员
    //-------------------------------------------------------------------------
    // 存储向量，为T[N]类型
    ComponentsType m_Components;
};

//-------------------------------------------------------------------------
// 必要的构造、析构、拷贝、赋值运算符重载函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】Vector
【函数功能】带参构造函数，根据initializer_list初始化向量的分量
【参数】initializer_list<T> List，初始化列表
【返回值】无
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
Vector<T, N>::Vector(initializer_list<T> List) {
    size_t i = 0;
    // 若初始化列表的大小不等于向量的维数，则抛出异常
    if (List.size() != N) {
        throw VECTOR_SIZE_ERROR();
    }
    // 遍历初始化列表，将分量赋值给向量
    for (auto it = List.begin(); it != List.end(); ++it) {
        m_Components[i] = *it;
        i++;
    }
}
/*************************************************************************
【函数名称】Vector
【函数功能】拷贝构造函数
【参数】const Vector<T, N>& AVector，另一个向量
【返回值】无
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
Vector<T, N>::Vector(const Vector<T, N>& AVector) {
    // 遍历向量的分量，将分量赋值给向量
    for (size_t i = 0; i < N; i++) {
        m_Components[i] = AVector.m_Components[i];
    }
}
/*************************************************************************
【函数名称】operator=
【函数功能】赋值运算符重载，将一个向量赋值给另一个向量
【参数】const Vector<T, N>& AVector
【返回值】Vector<T, N>&，赋值后的向量
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator=(const Vector<T, N>& AVector) {
    // 若向量地址与自身不同，则将分量赋值给向量
    if (this != &AVector) {
        for (size_t i = 0; i < N; i++) {
            m_Components[i] = AVector.m_Components[i];
        }
    }
    return *this;
}

//-------------------------------------------------------------------------
// 非静态Getter成员函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】operator[] const
【函数功能】返回分量引用的下标运算符重载，返回向量的第Index个分量
【参数】size_t Index，分量的下标
【返回值】T类型，向量的第Index个分量
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
T Vector<T, N>::operator[](size_t Index) const {
    // 若下标超出范围，则抛出异常
    if (Index >= N) {
        throw VECTOR_SIZE_ERROR();
    }
    return m_Components[Index];
}
/*************************************************************************
【函数名称】operator+ const
【函数功能】返回向量引用的和运算符重载，返回两个向量的和
【参数】const Vector<T, N>& AVector，另一个向量
【返回值】两个向量的和向量
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::operator+(const Vector<T, N>& AVector) const {
    Vector<T, N> result;
    // 遍历向量的分量，将两个向量的对应分量相加
    for (size_t i = 0; i < N; i++) {
        result.SetVector(i, Components[i] + AVector.Components[i]);
    }
    return result;
}
/*************************************************************************
【函数名称】operator- const
【函数功能】返回向量引用的减运算符重载，返回两个向量的差
【参数】const Vector<T, N>& AVector，另一个向量
【返回值】两个向量的差向量
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::operator-(const Vector<T, N>& AVector) const {
    Vector<T, N> result;
    // 遍历向量的分量，将两个向量的对应分量相减
    for (size_t i = 0; i < N; i++) {
        result.SetVector(i, Components[i] - AVector.Components[i]);
    }
    return result;
}
/*************************************************************************
【函数名称】operator* const
【函数功能】返回向量引用的叉乘运算符重载，返回两个向量的叉乘
【参数】const Vector<T, N>& AVector，另一个向量
【返回值】两个向量叉乘得到的向量
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::operator*(const Vector<T, N>& AVector) const {
    return CrossProduct(AVector);
}
/*************************************************************************
【函数名称】operator* const
【函数功能】返回向量引用的*运算符重载，返回向量与标量的乘积
【参数】const T& AScalar
【返回值】向量与T类型的乘积向量
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::operator*(const T& AScalar) const {
    Vector<T, N> result;
    // 遍历向量的分量，将向量的每个分量与T类型的aScalar相乘
    for (size_t i = 0; i < N; i++) {
        result.SetVector(i, Components[i] * AScalar);
    }
    return result;
}
/*************************************************************************
【函数名称】L0 const
【函数功能】求向量的L0范数，即向量中非零分量的个数
【参数】无
【返回值】T类型，向量的L0范数
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
T Vector<T, N>::L0() const {
    T result = 0;
    // 遍历向量的分量，若分量不为0，则L0范数加1
    for (size_t i = 0; i < N; i++) {
        if (Components[i] != 0) {
            result++;
        }
    }
    return result;
}
/*************************************************************************
【函数名称】L1 const
【函数功能】求向量的L1范数，即向量分量绝对值之和
【参数】无
【返回值】T类型，向量的L1范数
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
T Vector<T, N>::L1() const {
    T result = 0;
    // 遍历向量的分量，将分量的绝对值加到L1范数上
    for (size_t i = 0; i < N; i++) {
        result += abs(Components[i]);
    }
    return result;
}
/*************************************************************************
【函数名称】L2 const
【函数功能】求向量的L2范数，即向量分量平方和的平方根
【参数】无
【返回值】T类型，向量的L2范数
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
T Vector<T, N>::L2() const {
    T result = 0;
    // 遍历向量的分量，将分量的平方加到L2范数上
    for (size_t i = 0; i < N; i++) {
        result += Components[i] * Components[i];
    }
    return sqrt(result);
}
/*************************************************************************
【函数名称】L const
【函数功能】求向量的Lp范数，即向量分量绝对值的p次方和的1/p次方
【参数】size_t p
【返回值】若p=0，返回向量的L0范数；
         若p=1，返回向量的L1范数；
         若p=2，返回向量的L2范数；
         否则返回实际的派生类Lp范数
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
T Vector<T, N>::L(size_t p) const {
    // 若p不是0、1、2，则调用派生类的实际求Lp范数的函数
    if (p == 0) {
        return L0();
    } 
    else if (p == 1) {
        return L1();
    }
    else if (p == 2) {
        return L2();
    }
    else {
        return InnerL(p);
    }
}
/*************************************************************************
【函数名称】Lmax const
【函数功能】求向量的无穷范数，即向量分量绝对值的最大值
【参数】无
【返回值】向量的无穷范数
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
T Vector<T, N>::Lmax() const {
    // 初始化无穷范数为负无穷
    T result = -std::numeric_limits<T>::infinity();
    // 遍历向量的分量，将分量的绝对值与无穷范数比较，取较大值
    for (size_t i = 0; i < N; i++) {
        if (abs(Components[i]) > result) {
            result = abs(Components[i]);
        }
    }
    return result;
}
/*************************************************************************
【函数名称】InnerL const
【函数功能】若派生类未定义Lp范数的计算，则抛出异常
【参数】size_t p
【返回值】无
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
T Vector<T, N>::InnerL(size_t p) const {
    // 显示标记未使用的参数
    (void)p;
    throw LP_NORM_NOT_DEFINED();
}
/*************************************************************************
【函数名称】Module const
【函数功能】求向量的模，即向量的L2范数
【参数】无
【返回值】T类型，向量的模
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
T Vector<T, N>::Module() const {
    return L2();
}
/*************************************************************************
【函数名称】Length const
【函数功能】求向量的长度，即向量的L2范数
【参数】无
【返回值】T类型，向量的长度
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
T Vector<T, N>::Length() const {
    return L2();
}
/*************************************************************************
【函数名称】operater== const
【函数功能】判断向量是否相等，即向量的分量是否相等
【参数】const Vector<T, N>& AVector，另一个向量
【返回值】bool类型，若向量相等则返回true，否则返回false
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
bool Vector<T, N>::operator==(const Vector<T, N>& AVector) const {
    for (size_t i = 0; i < N; i++) {
        if (Components[i] != AVector.Components[i]) {
            return false;
        }
    }
    return true;
}
/*************************************************************************
【函数名称】operater!= const
【函数功能】判断向量是否不等
【参数】const Vector<T, N>& AVector，另一个向量
【返回值】bool类型，若向量不等则返回true，否则返回false
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
bool Vector<T, N>::operator!=(const Vector<T, N>& AVector) const {
    return !(*this == AVector);
}
/*************************************************************************
【函数名称】CrossProduct const
【函数功能】返回向量的叉乘，若维数为1或2则抛出异常
【参数】const Vector<T, N>& AVector，另一个向量
【返回值】实际的叉乘结果，由派生类实现
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::CrossProduct(const Vector<T, N>& AVector) const {
    // 若维数为1或2，则抛出异常
    if (N == 1 || N == 2) {
        throw CROSS_PRODUCT_NOT_DEFINED();
    }
    // 否则调用派生类的实际叉乘函数
    else {
        return InnerCrossProduct(AVector);
    }
}
/*************************************************************************
【函数名称】InnerCrossProduct const
【函数功能】若派生类未定义叉乘运算，则抛出异常
【参数】const Vector<T, N>& AVector，另一个向量
【返回值】无
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
Vector<T, N> Vector<T, N>::InnerCrossProduct(
    const Vector<T, N>& AVector) const {
    // 显示标记未使用的参数
    (void)AVector;
    // 若派生类未定义叉乘运算，则抛出异常
    throw CROSS_PRODUCT_NOT_DEFINED();
}

//-------------------------------------------------------------------------
// 非静态Setter成员函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】operator+=
【函数功能】重载+=运算符，向量加上另一个向量
【参数】const Vector<T, N>& AVector，另一个向量
【返回值】Vector<T, N>&，加上另一个向量后的向量
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator+=(const Vector<T, N>& AVector) {
    for (size_t i = 0; i < N; i++) {
        m_Components[i] += AVector.m_Components[i];
    }
    return *this;
}
/*************************************************************************
【函数名称】operator-=
【函数功能】重载-=运算符，向量减去另一个向量
【参数】const Vector<T, N>& AVector，另一个向量
【返回值】Vector<T, N>&，减去另一个向量后的向量
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator-=(const Vector<T, N>& AVector) {
    for (size_t i = 0; i < N; i++) {
        m_Components[i] -= AVector.m_Components[i];
    }
    return *this;
}
/*************************************************************************
【函数名称】operator*=
【函数功能】重载*=运算符，向量叉乘另一个向量
【参数】const Vector<T, N>& AVector，另一个向量
【返回值】Vector<T, N>&，叉乘另一个向量后的向量
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator*=(const Vector<T, N>& AVector) {
    this = CrossProduct(AVector);
    return *this;
}
/*************************************************************************
【函数名称】operator*=
【函数功能】重载*=运算符
【参数】const T& AScalar
【返回值】Vector<T, N>&，数乘T类型后的向量
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
Vector<T, N>& Vector<T, N>::operator*=(const T& AScalar) {
    for (size_t i = 0; i < N; i++) {
        m_Components[i] *= AScalar;
    }
    return *this;
}
/*************************************************************************
【函数名称】SetVector
【函数功能】设置向量的分量
【参数】size_t Index，分量的下标
       T Value，分量的值
【返回值】无
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
void Vector<T, N>::SetVector(size_t Index, T Value) {
    if (Index >= N) {
        throw VECTOR_SIZE_ERROR();
    }
    m_Components[Index] = Value;
}
/*************************************************************************
【函数名称】SetVector
【函数功能】通过数组设置向量的分量
【参数】const array<T, N>& AComponents，分量数组
【返回值】无
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T, size_t N>
void Vector<T, N>::SetVector(const array<T, N>& AComponents) {
    for (size_t i = 0; i < N; i++) {
        m_Components[i] = AComponents[i];
    }
}

#endif /* Vector.hpp */