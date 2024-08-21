/*************************************************************************
【文件名】Controller.hpp
【功能模块和目的】定义Controller类，作为整个系统的控制器
【开发者及日期】谭雯心 2024/8/9
【更改记录】2024/8/10 谭雯心 修改了获取模型信息的逻辑
           2024/8/11 谭雯心 增加了将ControllerRes转换为字符串的函数接口
*************************************************************************/
#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

// Face3D所属头文件
#include "Face3D.hpp"
// Line3D所属头文件
#include "Line3D.hpp"
// Model3D所属头文件
#include "Model3D.hpp"
// Point3D所属头文件
#include "Point3D.hpp"
// Model3D_OBJ_Exporter所属头文件
#include "Model3D_OBJ_Exporter.hpp"
// Model3D_OBJ_Importer所属头文件
#include "Model3D_OBJ_Importer.hpp"
// numeric_limits所属头文件
#include <limits>
// shared_ptr所属头文件
#include <memory>
// string所属头文件
#include <string>
// vector所属头文件
#include <vector>
// size_t所属头文件
#include <cstddef>

using namespace std;

/*************************************************************************
【类名】Controller
【功能】定义Controller类，作为整个系统的控制器
【接口说明】
    枚举类型Res，表示Controller的返回值
    非静态成员函数ControllerResStr，将ControllerRes转换为字符串
    虚析构函数
    静态成员函数GetInstance，获取Controller的唯一实例
    非静态成员函数LoadModelFromFile，从文件中导入指定模型
    非静态成员函数LoadModelFromFile，从文件中导入当前模型
    非静态成员函数SaveModelToFile，将指定模型导出到文件
    非静态成员函数SaveModelToFile，将当前模型导出到文件
    非静态成员函数CreateModel，创建模型并设置为当前模型
    非静态成员函数AddModel，向指定位置添加模型
    非静态成员函数AddModel，向当前位置添加模型
    非静态成员函数RemoveModel，删除指定位置模型
    非静态成员函数SetCurrentModel，设置指定位置的模型为当前模型
    非静态成员函数AddFace，向指定模型中添加面
    非静态成员函数AddFace，向当前模型中添加面
    非静态成员函数RemoveFace，从指定模型中删除面
    非静态成员函数RemoveFace，从当前模型中删除面
    非静态成员函数AddLine，向指定模型中添加线
    非静态成员函数AddLine，向当前模型中添加线
    非静态成员函数RemoveLine，从指定模型中删除线
    非静态成员函数RemoveLine，从当前模型中删除线
    非静态成员函数ChangeFacePoint，修改指定模型指定面中的指定点
    非静态成员函数ChangeFacePoint，修改当前模型指定面中的指定点
    非静态成员函数ChangeLinePoint，修改指定模型指定线中的指定点
    非静态成员函数ChangeLinePoint，修改当前模型指定线中的指定点
    非静态成员函数ClearFaces，清空指定模型中的面
    非静态成员函数ClearFaces，清空当前模型中的面
    非静态成员函数ClearLines，清空指定模型中的线
    非静态成员函数ClearLines，清空当前模型中的线
    非静态成员函数Clear，清空指定模型中的所有内容
    非静态成员函数Clear，清空当前模型中的所有内容
    非静态成员函数ListALLModelInfo，列出全部模型统计信息
    非静态成员函数ListModelInfo，列出指定位置模型统计信息
    非静态成员函数ListModelInfo，列出当前模型统计信息
    非静态成员函数ListFaceInfo，列出指定位置模型中所有Face3D的信息
    非静态成员函数ListFaceInfo，列出当前模型中所有Face3D的信息
    非静态成员函数ListLineInfo，列出指定位置模型中所有Line3D的信息
    非静态成员函数ListLineInfo，列出当前模型中所有Line3D的信息
【开发者及日期】谭雯心 2024/8/9
【更改记录】2024/8/10 谭雯心 修改了获取模型信息的逻辑
           2024/8/11 谭雯心 增加了将ControllerRes转换为字符串的函数接口
*************************************************************************/
class Controller {
public:
    //----------------------------------------------------------------
    // 公有的内嵌类，用于存储数据
    //----------------------------------------------------------------
    // 枚举类型，表示Controller的返回值
    enum class ControllerRes {
        OK = 0,
        FILE_NOT_SUPPORTED,
        FILE_NOT_AVAILABLE,
        FILE_NOT_CLOSED,
        POINT_DUPLICATED,
        POINT_NOT_FOUND,
        FACE_ALREADY_EXISTS,
        FACE_NOT_FOUND,
        LINE_ALREADY_EXISTS,
        LINE_NOT_FOUND,
        MODEL_ALREADY_EXISTS,
        MODEL_NOT_FOUND,
        UNKNOWN_TYPE
    };
    // PointInfo结构体，用于存储点信息
    struct PointInfo {
        // Point的三个坐标
        double x;
        double y;
        double z;
    };
    // ModelInfo结构体，用于存储模型信息
    struct ModelInfo {
        // 模型名称
        string Name;
        // 模型中面的数量
        size_t FaceCount;
        // 模型中线的数量
        size_t LineCount;
        // 模型中点的数量
        size_t PointCount;
        // 模型中元素的数量（面+线）
        size_t ElementCount;
        // 模型面的总面积
        double Area;
        // 模型中线的总长度
        double Length;
        // 包围盒的体积
        double Volume;
    };
    // FaceInfo结构体，用于存储面信息
    struct FaceInfo {
        // 面的三个点信息
        PointInfo Points[3];
        // 面的面积
        double Area;
    };
    // LineInfo结构体，用于存储线信息
    struct LineInfo {
        // 线的两个点信息
        PointInfo Points[2];
        // 线的长度
        double Length;
    };
    // 使用using语句简化名称
    using Res = ControllerRes;
    using ModelInfoList = vector<ModelInfo>;
    using FaceInfoList = vector<FaceInfo>;
    using LineInfoList = vector<LineInfo>;

private:
    //----------------------------------------------------------------
    // 私有的构造函数，用于实现单例模式
    //----------------------------------------------------------------
    // 禁止外界调用默认构造函数
    Controller() = default;
    // 禁止外界调用拷贝构造函数
    Controller(const Controller& Source) = delete;
    // 禁止外界调用赋值运算符
    Controller& operator=(const Controller& Source) = delete;
    //----------------------------------------------------------------
    // 私有静态成员
    //----------------------------------------------------------------
    // Controller的唯一实例
    static shared_ptr<Controller> m_pInstance;
    //----------------------------------------------------------------
    // 私有非静态成员
    //----------------------------------------------------------------
    // 全部模型指针
    vector<shared_ptr<Model3D>> m_pModel{};
    // 当前模型索引, 初始化为最大值
    size_t m_ullCurrentModelIndex{numeric_limits<size_t>::max()};
    
public:
    //----------------------------------------------------------------
    // 析构函数
    //----------------------------------------------------------------
    // 虚析构函数
    virtual ~Controller() = default;
    //----------------------------------------------------------------
    // 非静态Setter成员函数
    //----------------------------------------------------------------
    // 从文件中导入指定模型
    Res LoadModelFromFile(const string& FileName, Model3D& AModel);
    // 从文件中导入指定模型（根据模型位置）
    Res LoadModelFromFile(const string& FileName, size_t ModelIndex);
    // 从文件中导入当前模型
    Res LoadModelFromFile(const string& FileName);
    // 将指定模型导出到文件
    Res SaveModelToFile(const string& FileName, const Model3D& AModel);
    // 将指定模型导出到文件(根据模型位置)
    Res SaveModelToFile(const string& FileName, size_t ModelIndex);
    // 将当前模型导出到文件
    Res SaveModelToFile(const string& FileName);
    // 创建模型并设置为当前模型
    Res CreateModel();
    // 向指定位置添加模型
    Res AddModel(const Model3D& AModel, size_t ModelIndex);
    // 向当前位置添加模型
    Res AddModel(const Model3D& AModel);
    // 删除指定位置模型
    Res RemoveModel(size_t ModelIndex);
    // 设置指定位置的模型为当前模型
    Res SetCurrentModel(size_t ModelIndex);
    // 向指定模型中添加面
    Res AddFace(const Face3D& AFace, const Model3D& AModel);
    // 向指定位置的模型中添加面
    Res AddFace(const Face3D& AFace, size_t ModelIndex);
    // 向当前模型中添加面
    Res AddFace(const Face3D& AFace);
    // 向指定位置的模型中添加面(通过三个点坐标)
    Res AddFace(
        const double x1, const double y1, const double z1,
        const double x2, const double y2, const double z2,
        const double x3, const double y3, const double z3,
        size_t ModelIndex);
    // 向当前模型中添加面(通过三个点坐标)
    Res AddFace(
        const double x1, const double y1, const double z1,
        const double x2, const double y2, const double z2,
        const double x3, const double y3, const double z3);
    // 从指定模型中删除面
    Res RemoveFace(const Face3D& AFace, const Model3D& AModel);
    // 从指定位置的模型中删除面
    Res RemoveFace(size_t ModelIndex, size_t FaceIndex);
    // 从当前模型中删除指定位置的面
    Res RemoveFace(size_t FaceIndex);
    // 向指定模型中添加线
    Res AddLine(const Line3D& ALine, const Model3D& AModel);
    // 向指定位置的模型中添加线
    Res AddLine(const Line3D& ALine, size_t ModelIndex);
    // 向指定位置的模型中添加线(通过两个点坐标)
    Res AddLine(
        const double x1, const double y1, const double z1,
        const double x2, const double y2, const double z2,
        size_t ModelIndex);
    // 向当前模型中添加线
    Res AddLine(const Line3D& ALine);
    // 向当前模型中添加线(通过两个点坐标)
    Res AddLine(
        const double x1, const double y1, const double z1,
        const double x2, const double y2, const double z2);
    // 从指定模型中删除线
    Res RemoveLine(const Line3D& ALine, const Model3D& AModel);
    // 从指定位置的模型中删除线
    Res RemoveLine(size_t ModelIndex, size_t LineIndex);
    // 从当前模型中删除线
    Res RemoveLine(size_t LineIndex);
    // 修改指定模型指定面中的指定点
    Res ChangeFacePoint(
        size_t ModelIndex, 
        size_t FaceIndex, 
        size_t PointIndex,
        const Point3D& NewPoint);
    // 修改指定模型指定面中的指定点
    Res ChangeFacePoint(
        size_t ModelIndex, 
        size_t FaceIndex, 
        size_t PointIndex,
        const double x, const double y, const double z);
    // 修改当前模型指定面中的指定点
    Res ChangeFacePoint(
        size_t FaceIndex, 
        size_t PointIndex,
        const Point3D& NewPoint);
    // 修改当前模型指定面中的指定点
    Res ChangeFacePoint(
        size_t FaceIndex, 
        size_t PointIndex,
        const double x, const double y, const double z);
    // 修改指定模型指定线中的指定点
    Res ChangeLinePoint(
        size_t ModelIndex, 
        size_t LineIndex, 
        size_t PointIndex,
        const Point3D& NewPoint);
    // 修改指定模型指定线中的指定点
    Res ChangeLinePoint(
        size_t ModelIndex, 
        size_t LineIndex, 
        size_t PointIndex,
        const double x, const double y, const double z);
    // 修改当前模型指定线中的指定点
    Res ChangeLinePoint(
        size_t LineIndex, 
        size_t PointIndex,
        const Point3D& NewPoint);
    // 修改当前模型指定线中的指定点
    Res ChangeLinePoint(
        size_t LineIndex, 
        size_t PointIndex,
        const double x, const double y, const double z);
    // 清空指定模型中的面
    Res ClearFaces(const Model3D& AModel);
    // 清空指定位置模型中的面
    Res ClearFaces(size_t Index);
    // 清空当前模型中的面
    Res ClearFaces();
    // 清空指定模型中的线
    Res ClearLines(const Model3D& AModel);
    // 清空指定位置模型中的线
    Res ClearLines(size_t Index);
    // 清空当前模型中的线
    Res ClearLines();
    // 清空指定模型中的所有内容
    Res Clear(const Model3D& AModel);
    // 清空指定位置模型中的所有内容
    Res Clear(size_t Index);
    // 清空当前模型中的所有内容
    Res Clear();
    // 修改指定模型名称
    Res ChangeName(size_t Index, const string& NewName);
    // 修改当前模型名称
    Res ChangeName(const string& NewName);
    // 修改指定模型注释
    Res ChangeDescription(size_t Index, const string& NewDescription);
    // 修改当前模型注释
    Res ChangeDescription(const string& NewDescription);
    //----------------------------------------------------------------
    // 静态Getter成员函数
    //----------------------------------------------------------------
    // GetInstance()获取Controller的唯一实例
    static shared_ptr<Controller> GetInstance();
    //----------------------------------------------------------------
    // 非静态Getter数据成员
    //----------------------------------------------------------------
    // vector<shared_ptr<Model3D>> Models，用于存储全部模型指针
    const vector<shared_ptr<Model3D>>& Models{m_pModel};
    // size_t CurrentModelIndex，用于存储当前模型索引
    const size_t& CurrentModelIndex{m_ullCurrentModelIndex};
    //----------------------------------------------------------------
    // 非静态成员函数
    //----------------------------------------------------------------
    // 将ControllerRes转换为字符串
    const string& ControllerResStr(ControllerRes Res) const;
    // 列出全部模型统计信息
    Res ListALLModelInfo(ModelInfoList& InfoList) const;
    // 列出指定位置模型统计信息
    Res ListModelInfo(size_t ModelIndex, ModelInfo& Info) const;
    // 列出当前模型统计信息
    Res ListModelInfo(ModelInfo& Info) const;
    // 列出指定位置模型中所有Face3D的信息
    Res ListFaceInfo(size_t ModelIndex, FaceInfoList& Info) const;
    // 列出当前模型中所有Face3D的信息
    Res ListFaceInfo(FaceInfoList& InfoList) const;
    // 列出指定位置模型中所有Line3D的信息
    Res ListLineInfo(size_t ModelIndex, LineInfoList& Info) const;
    // 列出当前模型中所有Line3D的信息
    Res ListLineInfo(LineInfoList& InfoList) const;
};

#endif /* Controller.hpp */