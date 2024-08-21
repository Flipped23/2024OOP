/*************************************************************************
【文件名】Set.hpp
【功能模块和目的】定义集合类模板，存储T类型元素，实现集合的基本操作
【开发者及日期】谭雯心 2024/8/5
【更改记录】2024/8/12 谭雯心 修改抛出异常类型和添加元素列表的逻辑
*************************************************************************/
#ifndef SET_HPP
#define SET_HPP

// Group所属头文件
#include "Group.hpp"
// size_t所属头文件
#include <cstddef>
// initializer_list所属头文件
#include <initializer_list>
// find所属头文件
#include <algorithm>
// numeric_limits所属头文件
#include <limits>

using namespace std;

/*************************************************************************
【类名】Set
【功能】存储T类型元素的集合类模板(元素不可重复)，继承自Group类模板，实现集合的基本操作
【接口说明】
    默认构造函数
    带参构造函数
    拷贝构造函数
    赋值运算符重载
    虚析构函数
    添加元素override（不可重复）
    添加元素列表override（不可重复）
    插入元素override（不可重复）
    删除已存在元素override
    删除指定位置元素override
    修改元素override（不可重复）
    交集的赋值运算符&=重载
    并集的赋值运算符|=重载
    并集的赋值运算符+=重载
    补集的赋值运算符-=重载(在A中但不在B中的元素)
    补集的赋值运算符/=重载(在B中但不在A中的元素)
    对称差的赋值运算符^=重载(在A或B中但不在A且B中的元素)
    静态：判断元素是否在集合中
    交集的运算符&重载
    并集的运算符|重载
    并集的运算符+重载
    补集的运算符-重载(在A中但不在B中的元素)
    补集的运算符/重载(在B中但不在A中的元素)
    对称差的运算符^重载(在A或B中但不在A且B中的元素)
    判断是否相等的运算符==重载
    判断是否不等的运算符!=重载
【开发者及日期】谭雯心 2024/8/5
【更改记录】2024/8/12 谭雯心 修改抛出异常类型和添加元素列表的逻辑
*************************************************************************/

template <typename T>
class Set : public Group<T> {
public:
    //-------------------------------------------------------------------------
    // 必要的构造、析构、拷贝、赋值运算符重载函数
    //-------------------------------------------------------------------------
    // 默认构造函数
    Set(size_t MaxSize = numeric_limits<size_t>::max());
    // 带参构造函数
    Set(initializer_list<T> List,
        size_t MaxSize = numeric_limits<size_t>::max());
    // 拷贝构造函数
    Set(const Set<T>& ASet);
    // 赋值运算符重载
    Set<T>& operator=(const Set<T>& ASet);
    // 虚析构函数
    virtual ~Set() = default;
    //-------------------------------------------------------------------------
    // 非静态Setter成员函数
    //-------------------------------------------------------------------------
    //添加元素override（不可重复）
    void Add(T AElement) override;
    //添加元素列表override（不可重复）
    void Add(initializer_list<T> List) override;
    //插入元素override（不可重复）
    void Insert(T AElement, size_t Index) override;
    //删除已存在元素override
    void Remove(T AElement) override;
    //删除指定位置元素override
    void Remove(size_t Index) override;
    //修改元素override（不可重复）
    void Change(T AElement, size_t Index) override;
    //交集的赋值运算符&=重载
    Set<T> operator&=(const Set<T>& ASet);
    //并集的赋值运算符|=重载
    Set<T> operator|=(const Set<T>& ASet);
    //并集的赋值运算符+=重载
    Set<T> operator+=(const Set<T>& ASet);
    //补集的-=运算符重载(在A中但不在B中的元素)
    Set<T> operator-=(const Set<T>& ASet);
    //补集的/=运算符重载(在B中但不在A中的元素)
    Set<T> operator/=(const Set<T>& ASet);
    //对称差的^=运算符重载(在A或B中但不在A且B中的元素)
    Set<T> operator^=(const Set<T>& ASet);
    //-------------------------------------------------------------------------
    // 静态成员函数
    //-------------------------------------------------------------------------
    //判断元素是否在集合中
    static bool Contains(const Set<T>& ASet, T AElement);
    //-------------------------------------------------------------------------
    // 非静态Getter成员函数
    //-------------------------------------------------------------------------
    //交集
    Set<T> Intersection(const Set<T>& ASet) const;
    //交集的运算符&重载
    Set<T> operator&(const Set<T>& ASet) const;
    //并集
    Set<T> Union(const Set<T>& ASet) const;
    //并集的运算符|重载
    Set<T> operator|(const Set<T>& ASet) const;
    //并集的运算符+重载
    Set<T> operator+(const Set<T>& ASet) const;
    //补集的-运算符重载（在A中但不在B中的元素）
    Set<T> operator-(const Set<T>& ASet) const;
    //补集的/运算符重载（在B中但不在A中的元素）
    Set<T> operator/(const Set<T>& ASet) const;
    //补集的…^运算符重载（在A或B中但不在A且B中的元素）
    Set<T> operator^(const Set<T>& ASet) const;
    //判断是否相等的运算符==重载
    bool operator==(const Set<T>& ASet) const;
    //判断是否不等的运算符!=重载
    bool operator!=(const Set<T>& ASet) const;
    // 判断元素是否在集合中
    bool Contains(T AElement) const;
};

//-------------------------------------------------------------------------
// 必要的构造、析构、拷贝、赋值运算符重载函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】Set
【函数功能】默认构造函数
【参数】size_t MaxSize
【返回值】无
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
template <typename T>
Set<T>::Set(size_t MaxSize) : Group<T>(MaxSize) {
}
/*************************************************************************
【函数名称】Set
【函数功能】带参构造函数，初始化集合
【参数】initializer_list<T> List
【返回值】无
【开发者及日期】谭雯心 2024/8/5
【更改记录】2024/8/12 谭雯心 修改抛出异常类型
*************************************************************************/
template <typename T>
Set<T>::Set(initializer_list<T> List, size_t MaxSize) : Group<T>(MaxSize) {
    //检查是否有重复元素，有则抛出异常
    for (auto it = List.begin(); it != List.end(); ++it) {
        if (find(List.begin(), it, *it) != it) {
            throw typename Group<T>::ELEMENT_ALREADY_EXISTS();
        }
        Group<T>::Add(*it);
    }
}
/*************************************************************************
【函数名称】Set
【函数功能】拷贝构造函数
【参数】const Set<T>& ASet
【返回值】无
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
Set<T>::Set(const Set<T>& ASet) : Group<T>(ASet) {
}
/*************************************************************************
【函数名称】operator=
【函数功能】重载赋值运算符，将一个集合赋值给另一个集合
【参数】const Set<T>& ASet
【返回值】Set<T>&，赋值后的集合 
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
Set<T>& Set<T>::operator=(const Set<T>& ASet) {
    // 若两个集合不同，调用基类赋值运算符
    if (this != &ASet) {
        Group<T>::operator=(ASet);
    }
    return *this;
}

//-------------------------------------------------------------------------
// 非静态Setter成员函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】Add
【函数功能】添加元素，不可重复
【参数】T AElement
【返回值】无
【开发者及日期】谭雯心 2024/8/5
【更改记录】2024/8/12 谭雯心 修改抛出异常类型
*************************************************************************/
template <typename T>
void Set<T>::Add(T AElement) {
    //检查是否有重复元素，有则抛出异常
    for (size_t i = 0; i < this->CountElement(); i++) {
        if((*this)[i] == AElement) {
            throw typename Group<T>::ELEMENT_ALREADY_EXISTS();
        }
    }
    Group<T>::Add(AElement);
}
/*************************************************************************
【函数名称】Add
【函数功能】添加元素列表，不可重复
【参数】initializer_list<T> List
【返回值】无
【开发者及日期】谭雯心 2024/8/5
【更改记录】2024/8/12 谭雯心 修改添加元素列表逻辑
*************************************************************************/
template <typename T>
void Set<T>::Add(initializer_list<T> List) {
    for (auto it = List.begin(); it != List.end(); ++it) {
        Add(*it);
    }
}
/*************************************************************************
【函数名称】Insert
【函数功能】插入元素，不可重复
【参数】T AElement, size_t Index
【返回值】无
【开发者及日期】谭雯心 2024/8/5
【更改记录】2024/8/12 谭雯心 修改抛出异常类型
*************************************************************************/
template <typename T>   
void Set<T>::Insert(T AElement, size_t Index) {
    for (size_t i = 0; i < this->CountElement(); i++) {
        if((*this)[i] == AElement) {
            throw typename Group<T>::ELEMENT_ALREADY_EXISTS();
        }
    }
    Group<T>::Insert(AElement, Index);
}
/*************************************************************************
【函数名称】Remove
【函数功能】删除已存在元素
【参数】T AElement
【返回值】无
【开发者及日期】谭雯心 2024/8/5
【更改记录】2024/8/12 谭雯心 修改抛出异常类型
*************************************************************************/
template <typename T>
void Set<T>::Remove(T AElement) {
    size_t i;
    for (i = 0; i < this->CountElement(); i++) {
        if ((*this)[i] == AElement) {
            Group<T>::Remove(i);
            break;
        }
    }
    if (i == this->CountElement()) {
        throw typename Group<T>::ELEMENT_NOT_FOUND();
    }
}
/*************************************************************************
【函数名称】Remove
【函数功能】删除指定位置元素
【参数】size_t Index
【返回值】无
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
template <typename T>
void Set<T>::Remove(size_t Index) {
    Group<T>::Remove(Index);
}
/*************************************************************************
【函数名称】Change
【函数功能】修改元素，不可重复
【参数】T AElement, size_t Index
【返回值】无
【开发者及日期】谭雯心 2024/8/5
【更改记录】2024/8/12 谭雯心 修改抛出异常类型
*************************************************************************/
template <typename T>
void Set<T>::Change(T AElement, size_t Index) {
    for (size_t i = 0; i < this->CountElement(); i++) {
        if((*this)[i] == AElement) {
            throw typename Group<T>::ELEMENT_ALREADY_EXISTS();
        }
    }
    Group<T>::Change(AElement, Index);
}
/*************************************************************************
【函数名称】operator&=
【函数功能】重载交集的赋值运算符&=，返回交集
【参数】const Set<T>& ASet
【返回值】Set<T>，交集
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
template <typename T>
Set<T> Set<T>::operator&=(const Set<T>& ASet) {
    *this = Intersection(ASet);
    return *this;
}
/*************************************************************************
【函数名称】operator|=
【函数功能】重载并集的赋值运算符|=，返回并集
【参数】const Set<T>& ASet
【返回值】Set<T>，并集
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
template <typename T>
Set<T> Set<T>::operator|=(const Set<T>& ASet) {
    *this = Union(ASet);
    return *this;
}
/*************************************************************************
【函数名称】operator+=
【函数功能】重载并集的赋值运算符+=，返回并集
【参数】const Set<T>& ASet
【返回值】Set<T>，并集
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
template <typename T>  
Set<T> Set<T>::operator+=(const Set<T>& ASet) {
    *this = Union(ASet);
    return *this;
}
/*************************************************************************
【函数名称】operator-=
【函数功能】重载补集的赋值运算符-=，返回补集(在A中但不在B中的元素)
【参数】const Set<T>& ASet
【返回值】Set<T>，补集(在A中但不在B中的元素)
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
template <typename T>
Set<T> Set<T>::operator-=(const Set<T>& ASet) {
    *this = *this - ASet;
    return this;
}
/*************************************************************************
【函数名称】operator/=
【函数功能】重载补集的赋值运算符/=，返回补集(在B中但不在A中的元素)
【参数】const Set<T>& ASet
【返回值】Set<T>，补集(在B中但不在A中的元素)
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
template <typename T>
Set<T> Set<T>::operator/=(const Set<T>& ASet) {
    *this = *this / ASet;
    return this;
}
/*************************************************************************
【函数名称】operator^=
【函数功能】重载补集的赋值运算符^=，返回对称差(在A或B中但不在A且B中的元素)
【参数】const Set<T>& ASet
【返回值】Set<T>，对称差(在A或B中但不在A且B中的元素)
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
template <typename T>
Set<T> Set<T>::operator^=(const Set<T>& ASet) {
    *this = *this ^ ASet;
    return this;
}

//-------------------------------------------------------------------------
// 静态成员函数
//------------------------------------------------------------------------- 

/*************************************************************************
【函数名称】Contains
【函数功能】判断元素是否在集合中
【参数】const Set<T>& ASet, T AElement
【返回值】bool，true表示存在，false表示不存在
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
template <typename T>
bool Set<T>::Contains(const Set<T>& ASet, T AElement) {
    for (size_t i = 0; i < ASet.CountElement(); i++) {
        if (ASet[i] == AElement) {
            return true;
        }
    }
    return false;
}

//-------------------------------------------------------------------------
// 非静态Getter成员函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】operator& const
【函数功能】重载交集的运算符&，返回交集
【参数】const Set<T>& ASet
【返回值】Set<T>，交集
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
template <typename T>
Set<T> Set<T>::operator&(const Set<T>& ASet) const {
    return Intersection(ASet);
}
/*************************************************************************
【函数名称】operator| const
【函数功能】重载并集的运算符|，返回交集
【参数】const Set<T>& ASet
【返回值】Set<T>，交集
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
template <typename T>
Set<T> Set<T>::operator|(const Set<T>& ASet) const {
    return Union(ASet);
}
/*************************************************************************
【函数名称】operator+ const
【函数功能】重载并集的运算符+，返回交集
【参数】const Set<T>& ASet
【返回值】Set<T>，交集
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
template <typename T>
Set<T> Set<T>::operator+(const Set<T>& ASet) const {
    return Union(ASet);
}
/*************************************************************************
【函数名称】operator- const
【函数功能】重载补集的运算符-，返回补集(在A中但不在B中的元素)
【参数】const Set<T>& ASet
【返回值】Set<T>，交集
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
template <typename T>
Set<T> Set<T>::operator-(const Set<T>& ASet) const {
    Set<T> result;
    for (size_t i = 0; i < this->CountElement(); i++) {
        if (!Contains(ASet, (*this)[i])) {
            result.Add((*this)[i]);
        }
    }
    return result;
}
/*************************************************************************
【函数名称】operator/ const
【函数功能】重载补集的运算符/，返回补集(在B中但不在A中的元素)
【参数】const Set<T>& ASet
【返回值】Set<T>，补集(在B中但不在A中的元素)
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
template <typename T>
Set<T> Set<T>::operator/(const Set<T>& ASet) const {
    Set<T> result;
    for (size_t i = 0; i < ASet.CountElement(); i++) {
        if (!Contains(*this, ASet[i])) {
            result.Add(ASet[i]);
        }
    }
}
/*************************************************************************
【函数名称】operator^ const
【函数功能】重载对称差的运算符^，返回对称差(在A或B中但不在A且B中的元素)
【参数】const Set<T>& ASet
【返回值】Set<T>，对称差(在A或B中但不在A且B中的元素)
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
template <typename T>
Set<T> Set<T>::operator^(const Set<T>& ASet) const {
    return Union(ASet) - Intersection(ASet);
}
/*************************************************************************
【函数名称】Intersection const
【函数功能】求交集
【参数】const Set<T>& ASet
【返回值】Set<T>，交集
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
template <typename T>
Set<T> Set<T>::Intersection(const Set<T>& ASet) const {
    Set<T> result;
    //遍历两个集合，找到相同元素
    for (size_t i = 0; i < this->CountElement(); i++) {
        for (size_t j = 0; j < ASet.CountElement(); j++) {
            if ((*this)[i] == ASet[j]) {
                result.Add((*this)[i]);
            }
        }
    }
    return result;
}
/*************************************************************************
【函数名称】Union const
【函数功能】求并集
【参数】const Set<T>& ASet
【返回值】Set<T>，并集
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
template <typename T>
Set<T> Set<T>::Union(const Set<T>& ASet) const {
    Set<T> result;
    //将两个集合的元素全部加入新集合
    for (size_t i = 0; i < this->CountElement(); i++) {
        if (!Contains(result, (*this)[i])) {
            result.Add((*this)[i]);
        }
    }
    for (size_t i = 0; i < ASet.CountElement(); i++) {
        if (!Contains(result, ASet[i])) {
            result.Add(ASet[i]);
        }
    }
    return result;
}
/*************************************************************************
【函数名称】operator==
【函数功能】重载判断是否相等的运算符==，判断两个集合是否相等
【参数】const Set<T>& ASet
【返回值】bool，true表示相等，false表示不相等
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
template <typename T>
bool Set<T>::operator==(const Set<T>& ASet) const {
    //先判断元素数量是否相等
    if (this->CountElement() != ASet.CountElement()) {
        return false;
    }
    //再判断元素是否相同（顺序不同算相同）
    for (size_t i = 0; i < this->CountElement(); i++) {
        if (!Contains(ASet, (*this)[i])) {
            return false;
        }
    }
    return true;
}
/*************************************************************************
【函数名称】operator!=
【函数功能】重载判断是否不等的运算符!=，判断两个集合是否不相等
【参数】const Set<T>& ASet
【返回值】bool，true表示不相等，false表示相等
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
template <typename T>
bool Set<T>::operator!=(const Set<T>& ASet) const {
    // 利用==运算符重载
    return !(*this == ASet);
}
/*************************************************************************
【函数名称】Contains
【函数功能】判断元素是否在集合中
【参数】T AElement
【返回值】bool，true表示存在，false表示不存在
【开发者及日期】谭雯心 2024/8/5
【更改记录】
*************************************************************************/
template <typename T>
bool Set<T>::Contains(T AElement) const {
    for (size_t i = 0; i < this->CountElement(); i++) {
        if ((*this)[i] == AElement) {
            return true;
        }
    }
    return false;
}

#endif /* Set.hpp */