/*************************************************************************
【文件名】Group.hpp
【功能模块和目的】定义Group类模板，存储T类型的元素
【开发者及日期】谭雯心 2024/8/4
【更改记录】2024/8/12 谭雯心 增加内嵌异常类的声明与实现
*************************************************************************/
#ifndef GROUP_HPP
#define GROUP_HPP

// vector所属头文件
#include <vector>
// vector操作所属头文件
#include <algorithm>
#include <functional>
// initializer_list所属头文件
#include <initializer_list>
// 异常类所属头文件
#include <stdexcept>
// size_t所属头文件
#include <cstddef>
// 流操作所属头文件
#include <iostream>
// numeric_limits所属头文件
#include <limits>

using namespace std;

// Group类模板的前置声明，以便在流输出运算符重载中使用
template <typename T>
class Group;

/*************************************************************************
【函数名称】operator<<
【函数功能】流插入运算符重载，输出向量
【参数】ostream& out，输出流；
       const Group<T>& AGroup，Group类对象
【返回值】ostream&，输出流
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
ostream& operator<<(ostream& out, const Group<T>& AGroup) {
    out << "{";
    for (size_t i = 0; i < AGroup.CountElement(); i++) {
        if (i != AGroup.CountElement() - 1) {
            out << AGroup[i] << ", ";
        } 
        else {
            out << AGroup[i];
        }
    }
    out << "}";
    return out;
}

/*************************************************************************
【类名】Group
【功能】定义Group类模板，存储T类型的元素
【接口说明】
    默认构造函数
    带参构造函数
    拷贝构造函数
    赋值运算符
    虚析构函数
    返回T类型元素的下标运算符重载
    判断是否相等的运算符重载
    判断是否不等的运算符重载
    查找元素的下标
    获取元素个数
    判断是否为空
    判断元素是否存在
    向末尾添加元素
    向末尾添加元素列表
    在指定位置插入元素
    删除指定元素
    删除指定位置的元素
    修改指定位置的元素
    清空元素
    流输出运算符重载
【开发者及日期】谭雯心 2024/8/4
【更改记录】2024/8/12 谭雯心 增加内嵌异常类的声明与实现
*************************************************************************/
template <typename T>
class Group {
public:
    //-------------------------------------------------------------------------
    // 内嵌异常类
    //-------------------------------------------------------------------------
    // 元素未找到异常类
    class ELEMENT_NOT_FOUND : public logic_error {
    public:
        ELEMENT_NOT_FOUND();
    };
    // 要添加元素时，元素已存在的异常类
    class ELEMENT_ALREADY_EXISTS : public logic_error {
    public:
        ELEMENT_ALREADY_EXISTS();
    };
    // 下标超出范围异常类
    class INDEX_ERROR : public out_of_range {
    public:
        INDEX_ERROR();
    };
    //-------------------------------------------------------------------------
    // 必要的构造、析构、拷贝、赋值运算符重载函数
    //-------------------------------------------------------------------------
    // 默认构造函数
    Group(size_t MaxElementCount = numeric_limits<size_t>::max());
    // 带参构造函数
    Group(initializer_list<T> List);
    // 拷贝构造函数
    Group(const Group<T>& AGroup) = default;
    // 赋值运算符
    Group& operator=(const Group<T>& AGroup) = default;
    // 虚析构函数
    virtual ~Group() = default;
    //-------------------------------------------------------------------------
    // 非静态Getter成员函数
    //-------------------------------------------------------------------------
    // 返回T类型元素的下标运算符重载
    T operator[](size_t Index) const;
    // 判断是否相等的运算符重载
    bool operator==(const Group<T>& AGroup) const;
    // 判断是否不等的运算符重载
    bool operator!=(const Group<T>& AGroup) const;
    // 查找元素的下标
    size_t Search(T AElement) const;
    // 获取元素个数
    size_t CountElement() const;
    // 获取元素数量上限
    size_t MaxElementCount() const;
    // 判断是否为空
    bool IsEmpty() const;
    // 判断元素是否存在
    bool Exist(T AElement) const;
    //-------------------------------------------------------------------------
    // 非静态Setter成员函数
    //-------------------------------------------------------------------------
    // 向末尾添加元素
    virtual void Add(T AElement);
    // 向末尾添加元素列表
    virtual void Add(initializer_list<T> List);
    // 向指定位置插入元素
    virtual void Insert(T AElement, size_t Index);
    // 删除指定元素
    virtual void Remove(T AElement);
    // 删除指定位置的元素
    virtual void Remove(size_t Index);
    // 修改指定位置的元素
    virtual void Change(T AElement, size_t Index);
    // 清空元素
    void Clear();
    // 友元函数，流插入运算符重载
    friend ostream& operator<< <T>(ostream& out, const Group<T>& AGroup);

private:
    // 存储元素的容器，vector类型
    vector<T> m_Elements;
    // 存储元素数量上限
    size_t m_MaxElementCount{numeric_limits<size_t>::max()};
};

//-------------------------------------------------------------------------
// 内嵌异常类
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】ELEMENT_NOT_FOUND
【函数功能】元素未找到异常类的构造函数
【参数】无
【返回值】无
【开发者及日期】谭雯心 2024/8/12
【更改记录】
*************************************************************************/
template <typename T>
Group<T>::ELEMENT_NOT_FOUND::ELEMENT_NOT_FOUND()
    : logic_error("Element not found.") {
    }
/*************************************************************************
【函数名称】ELEMENT_ALREADY_EXISTS
【函数功能】要添加元素时，元素已存在的异常类的构造函数
【参数】无
【返回值】无
【开发者及日期】谭雯心 2024/8/12
【更改记录】
*************************************************************************/
template <typename T>
Group<T>::ELEMENT_ALREADY_EXISTS::ELEMENT_ALREADY_EXISTS()
    : logic_error("Element already exists.") {
    }
/*************************************************************************
【函数名称】INDEX_ERROR
【函数功能】下标超出范围异常类的构造函数
【参数】无
【返回值】无
【开发者及日期】谭雯心 2024/8/12
【更改记录】
*************************************************************************/
template <typename T>
Group<T>::INDEX_ERROR::INDEX_ERROR()
    : out_of_range("Index out of range.") {
    }
//-------------------------------------------------------------------------
// 必要的构造、析构、拷贝、赋值运算符重载函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】Group
【函数功能】默认构造函数
【参数】size_t MaxPointCount，元素数量上限
【返回值】无
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
Group<T>::Group(size_t MaxElementCount) : m_MaxElementCount(MaxElementCount) {
}
/*************************************************************************
【函数名称】Group
【函数功能】带参构造函数，根据initializer_list初始化元素
【参数】initializer_list<T> List，初始化列表
【返回值】无
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
Group<T>::Group(initializer_list<T> List) {
    for (auto it = List.begin(); it != List.end(); ++it) {
        m_Elements.push_back(*it);
    }
}
/*************************************************************************
【函数名称】operator[] const
【函数功能】返回T类型元素的下标运算符重载
【参数】size_t Index，下标
【返回值】T类型元素
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
T Group<T>::operator[](size_t Index) const {
    return m_Elements[Index];
}
/*************************************************************************
【函数名称】operator== const
【函数功能】判断是否相等的运算符重载
【参数】const Group<T>& AGroup，Group类对象
【返回值】bool，相等返回true，否则返回false
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
bool Group<T>::operator==(const Group<T>& AGroup) const {
    // 若元素个数不同，返回false
    if (m_Elements.size() != AGroup.m_Elements.size()) {
        return false;
    }
    // 逐个比较元素
    for (size_t i = 0; i < m_Elements.size(); i++) {
        if (m_Elements[i] != AGroup.m_Elements[i]) {
            return false;
        }
    }
    return true;
}
/*************************************************************************
【函数名称】operator!= const
【函数功能】判断是否不等的运算符重载
【参数】const Group<T>& AGroup，Group类对象
【返回值】bool，不等返回true，否则返回false
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
bool Group<T>::operator!=(const Group<T>& AGroup) const {
    // 利用相等运算符重载
    return !(*this == AGroup);
}
/*************************************************************************
【函数名称】Search const
【函数功能】查找元素的下标
【参数】T AElement，元素
【返回值】若找到元素返回下标，否则返回-1
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
size_t Group<T>::Search(T AElement) const {
    for (size_t index = 0; index < m_Elements.size(); index++) {
        if (m_Elements[index] == AElement) {
            return index;
        }
    }
    // 若未找到元素，抛出异常
    throw ELEMENT_NOT_FOUND();
}
/*************************************************************************
【函数名称】CountElement const
【函数功能】统计元素个数
【参数】无
【返回值】元素个数
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
size_t Group<T>::CountElement() const {
    return m_Elements.size();
}
/*************************************************************************
【函数名称】MaxElementCount const
【函数功能】获取元素数量上限
【参数】无
【返回值】元素数量上限
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
size_t Group<T>::MaxElementCount() const {
    return m_MaxElementCount;
}
/*************************************************************************
【函数名称】IsEmpty const
【函数功能】判断是否为空
【参数】无
【返回值】bool, 空返回true，否则返回false
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
bool Group<T>::IsEmpty() const {
    return m_Elements.empty();
}
/*************************************************************************
【函数名称】Exist const
【函数功能】判断元素是否存在
【参数】T AElement，元素
【返回值】bool, 存在返回true，否则返回false
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
bool Group<T>::Exist(T AElement) const {
    for (size_t i = 0; i < m_Elements.size(); i++) {
        if (m_Elements[i] == AElement) {
            return true;
        }
    }
    return false;
}

//-------------------------------------------------------------------------
// 非静态Setter成员函数
//-------------------------------------------------------------------------

/*************************************************************************
【函数名称】Add
【函数功能】向末尾添加元素
【参数】T AElement，元素
【返回值】无
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
void Group<T>::Add(T AElement) {
    m_Elements.push_back(AElement);
}
/*************************************************************************
【函数名称】Add
【函数功能】向末尾添加元素列表
【参数】initializer_list<T> List，元素列表
【返回值】无
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
void Group<T>::Add(initializer_list<T> List) {
    for (auto it = List.begin(); it != List.end(); ++it) {
        m_Elements.push_back(*it);
    }
}
/*************************************************************************
【函数名称】Insert
【函数功能】在指定位置插入元素
【参数】T AElement，元素；
       size_t Index，位置
【返回值】无
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
void Group<T>::Insert(T AElement, size_t Index) {
    // 若位置超出范围，抛出异常
    if (Index >= m_Elements.size()) {
        throw INDEX_ERROR();
    }
    m_Elements.insert(m_Elements.begin() + Index, AElement);
}
/*************************************************************************
【函数名称】Remove
【函数功能】删除指定元素
【参数】T AElement，元素
【返回值】无
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
void Group<T>::Remove(T AElement) {
    size_t i;
    for (i = 0; i < m_Elements.size(); i++) {
        if (m_Elements[i] == AElement) {
            m_Elements.erase(m_Elements.begin() + i);
            break;
        }
    }
    // 若未找到元素，抛出异常
    if (i == m_Elements.size()) {
        throw ELEMENT_NOT_FOUND();
    }
}
/*************************************************************************
【函数名称】Remove
【函数功能】删除指定位置的元素
【参数】size_t Index，位置
【返回值】无
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
void Group<T>::Remove(size_t Index) {
    // 若位置超出范围，抛出异常
    if (Index >= m_Elements.size()) {
        throw INDEX_ERROR();
    }
    m_Elements.erase(m_Elements.begin() + Index);
}
/*************************************************************************
【函数名称】Change
【函数功能】修改指定位置的元素
【参数】T AElement，元素；
       size_t Index，位置
【返回值】无
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
void Group<T>::Change(T AElement, size_t Index) {
    // 若位置超出范围，抛出异常
    if (Index >= m_Elements.size()) {
        throw INDEX_ERROR();
    }
    m_Elements[Index] = AElement;
}
/*************************************************************************
【函数名称】Clear
【函数功能】清空元素
【参数】无
【返回值】无
【开发者及日期】谭雯心 2024/8/4
【更改记录】
*************************************************************************/
template <typename T>
void Group<T>::Clear() {
    m_Elements.clear();
}

#endif /* Group.hpp */