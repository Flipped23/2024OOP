/*************************************************************************
【文件名】Viewer.hpp
【功能模块和目的】定义Viewer类，表示用户界面
【开发者及日期】谭雯心 2024/8/10
【更改记录】
*************************************************************************/
#ifndef VIEWER_HPP
#define VIEWER_HPP

// string所属头文件
#include <string>
// Controller所属头文件
#include "Controller.hpp"
using namespace std;

/*************************************************************************
【类名】Viewer
【功能】定义Viewer类，表示用户界面
【接口说明】
    默认构造函数
    虚析构函数
    主菜单
    选择当前模型菜单
    创建模型菜单
    导入模型菜单
    导出模型菜单
    删除模型菜单
    编辑模型菜单
    添加面菜单
    添加线菜单
    删除面菜单
    删除线菜单
    编辑面上的点菜单
    编辑线上的点菜单
    修改模型名称菜单
    修改模型注释菜单
    查看模型信息菜单
    查看面信息菜单
    查看线信息菜单
【开发者及日期】谭雯心 2024/8/10
【更改记录】
*************************************************************************/
class Viewer {
public:
    //---------------------------------------------------------------------------------
    // 必要的构造、析构函数
    //---------------------------------------------------------------------------------
    // 默认构造函数
    Viewer();
    // 拷贝构造函数
    Viewer(const Viewer& AViewer) = delete;
    // 赋值运算符
    Viewer& operator=(const Viewer& AViewer) = delete;
    // 析构函数
    virtual ~Viewer() = default;

protected:
    //---------------------------------------------------------------------------------
    // 受保护的成员函数
    //---------------------------------------------------------------------------------
    // 主菜单
    virtual string MainMenu();
    // 选择在模型菜单
    virtual string SelectModelMenu();
    // 创建模型菜单
    virtual string CreateModelMenu();
    // 导入模型菜单
    virtual string LoadModelMenu();
    // 导出模型菜单
    virtual string SaveModelMenu();
    // 删除模型菜单
    virtual string RemoveModelMenu();
    // 编辑模型菜单
    virtual string EditModelMenu();
    // 添加面菜单
    virtual string AddFaceMenu();
    // 添加线菜单
    virtual string AddLineMenu();
    // 删除面菜单
    virtual string RemoveFaceMenu();
    // 删除线菜单
    virtual string RemoveLineMenu();
    // 编辑面菜单
    virtual string EditFacePointMenu();
    // 编辑线菜单
    virtual string EditLinePointMenu();
    // 修改模型名称菜单
    virtual string EditModelNameMenu();
    // 修改模型注释菜单
    virtual string EditModelDescriptionMenu();
    // 查看模型信息菜单
    virtual string ListModelInfoMenu();
    // 查看面信息菜单
    virtual string ListFaceInfoMenu();
    // 查看线信息菜单
    virtual string ListLineInfoMenu();
};

#endif /* Viewer.hpp */