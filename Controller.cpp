/*************************************************************************
【文件名】Controller.cpp
【功能模块和目的】控制器类的实现
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
// Controller类的头文件
#include "Controller.hpp"
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
// vector操作所属头文件
#include <algorithm>
#include <functional>

using namespace std;

// m_pInstance初始化为nullptr
shared_ptr<Controller> Controller::m_pInstance = nullptr;

//----------------------------------------------------------------------
// 非静态Setter
//----------------------------------------------------------------------

/*************************************************************************
【函数名称】LoadModelFromFile
【函数功能】从文件中导入指定模型
【参数】const string& FileName, 文件名
         Model3D& AModel, 模型
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】2024/8/12 谭雯心 增加了从文件中导入模型可能抛出的异常
*************************************************************************/
Controller::Res Controller::LoadModelFromFile(
    const string& FileName, Model3D& AModel) {
    // 创建Model3D_OBJ_Importer对象
    Model3D_OBJ_Importer Importer;
    string Extension;
    // 获取文件扩展名，若不支持该文件类型，返回FILE_NOT_SUPPORTED
    try {
        Extension = Importer.GetExtension(FileName);
    } 
    catch (...) {
        return Res::FILE_NOT_SUPPORTED;
    }
    // 若不是.obj文件，返回FILE_NOT_SUPPORTED
    if (Extension != "obj") {
        return Res::FILE_NOT_SUPPORTED;
    }
    // 尝试从文件中导入模型，若失败，返回FILE_NOT_AVAILABLE
    try {
        Importer.LoadFromFile(FileName, AModel);
    } 
    catch (...) {
        return Res::FILE_NOT_AVAILABLE;
    }
    return Res::OK;
}
/*************************************************************************
【函数名称】LoadModelFromFile
【函数功能】从文件中导入指定位置的模型
【参数】const string& FileName, 文件名
       size_t ModelIndex, 模型位置
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】2024/8/12 谭雯心 增加了从文件中导入模型可能抛出的异常
*************************************************************************/
Controller::Res Controller::LoadModelFromFile(
    const string& FileName, size_t ModelIndex) {
    // 若Index超出范围找不到指定模型，返回MODEL_NOT_FOUND
    if (ModelIndex >= m_pModel.size()) {
        return Res::MODEL_NOT_FOUND;
    }
    return LoadModelFromFile(FileName, *m_pModel[ModelIndex]);
}
/*************************************************************************
【函数名称】LoadModelFromFile
【函数功能】从文件中导入当前模型
【参数】const string& FileName, 文件名
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::LoadModelFromFile(const string& FileName) {
    return LoadModelFromFile(FileName, m_ullCurrentModelIndex);
}
/*************************************************************************
【函数名称】SaveModelToFile
【函数功能】将模型导出到文件
【参数】const string& FileName, 文件名
       const Model3D& AModel, 模型
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::SaveModelToFile(
    const string& FileName, const Model3D& AModel) {
    // 创建Model3D_OBJ_Exporter对象
    Model3D_OBJ_Exporter Exporter;
    string Extension;
    // 获取文件扩展名，若不支持该文件类型，返回FILE_NOT_SUPPORTED
    try {
        Extension = Exporter.GetExtension(FileName);
    } 
    catch (...) {
        return Res::FILE_NOT_SUPPORTED;
    }
    // 若不是.obj文件，返回FILE_NOT_SUPPORTED
    if (Extension != "obj") {
        return Res::FILE_NOT_SUPPORTED;
    }
    // 尝试将模型导入到文件，若失败，返回FILE_NOT_AVAILABLE
    try {
        Exporter.SaveToFile(FileName, AModel);
    } 
    catch (...) {
        return Res::FILE_NOT_AVAILABLE;
    }
    return Res::OK;
}
/*************************************************************************
【函数名称】SaveModelToFile
【函数功能】将指定位置模型导出到文件
【参数】const string& FileName, 文件名
       size_t ModelIndex, 模型位置
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::SaveModelToFile(
    const string& FileName, size_t ModelIndex) {
    // 若ModelIndex超出范围找不到指定模型，返回MODEL_NOT_FOUND
    if (ModelIndex < m_pModel.size()) {
        return SaveModelToFile(FileName, *m_pModel[ModelIndex]);
    }
    return Res::MODEL_NOT_FOUND;
}
/*************************************************************************
【函数名称】SaveModelToFile
【函数功能】将当前模型导出到文件
【参数】const string& FileName, 文件名
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::SaveModelToFile(const string& FileName) {
    return SaveModelToFile(FileName, m_ullCurrentModelIndex);
}
/*************************************************************************
【函数名称】CreateModel
【函数功能】创建模型并设置为当前模型
【参数】无
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】2024/8/10 谭雯心 修改了创建模型的逻辑
*************************************************************************/
Controller::Res Controller::CreateModel() {
    // 创建模型并添加到模型列表
    m_pModel.push_back(shared_ptr<Model3D>(new Model3D()));
    // 设置当前模型为新创建的模型
    m_ullCurrentModelIndex = m_pModel.size() - 1;
    return Res::OK;
}
/*************************************************************************
【函数名称】AddModel
【函数功能】向指定位置添加模型
【参数】const Model3D& AModel, 要添加的模型
       size_t ModelIndex, 模型位置
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】2024/8/12 谭雯心 修正了修改m_ullCurrentModelIndex的逻辑
*************************************************************************/
Controller::Res Controller::AddModel(
    const Model3D& AModel, size_t ModelIndex) {
    // 创建新的Model3D对象
    shared_ptr<Model3D> pModel = make_shared<Model3D>(AModel);
    // 若Index超出范围找不到指定模型，返回MODEL_NOT_FOUND
    if (ModelIndex < m_pModel.size()) {
        m_pModel.insert(m_pModel.begin() + ModelIndex, pModel);
    } 
    else {
        m_pModel.push_back(pModel);
    }
    // 若ModelIndex小于当前模型位置，当前模型位置加1
    if (ModelIndex < m_ullCurrentModelIndex) {
        m_ullCurrentModelIndex++;
    }
    return Res::OK;
}
/*************************************************************************
【函数名称】AddModel
【函数功能】向模型列表添加模型
【参数】const Model3D& AModel, 要添加的模型
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::AddModel(const Model3D& AModel) {
    return AddModel(AModel, m_pModel.size());
}
/*************************************************************************
【函数名称】RemoveModel
【函数功能】从指定位置删除模型
【参数】size_t ModelIndex, 模型位置
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::RemoveModel(size_t ModelIndex) {
    // 若ModelIndex超出范围找不到指定模型，返回MODEL_NOT_FOUND
    if (ModelIndex < m_pModel.size()) {
        // 删除指定位置模型
        m_pModel.erase(m_pModel.begin() + ModelIndex);
        // 若ModelIndex小于当前模型位置，当前模型位置减1
        if (ModelIndex < m_ullCurrentModelIndex) {
            m_ullCurrentModelIndex--;
        }
        return Res::OK;
    }
    return Res::MODEL_NOT_FOUND;
}
/*************************************************************************
【函数名称】SetCurrentModel
【函数功能】设置指定位置为当前模型
【参数】size_t Index, 模型位置
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::SetCurrentModel(size_t ModelIndex) {
    // 若Index超出范围找不到指定模型，返回MODEL_NOT_FOUND
    if (ModelIndex >= m_pModel.size()) {
        return Res::MODEL_NOT_FOUND;
    }
    m_ullCurrentModelIndex = ModelIndex;
    return Res::OK;
}
/*************************************************************************
【函数名称】AddFace
【函数功能】向指定模型中添加面
【参数】const Face3D& AFace, 要添加的面
       const Model3D& AModel, 指定模型
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::AddFace(
    const Face3D& AFace, const Model3D& AModel) {
    // 遍历模型列表, 若找到指定模型，向该模型中添加面
    for (auto it = m_pModel.begin(); it != m_pModel.end(); ++it) {
        if (**it == AModel) {
            // 若面已存在，返回FACE_ALREADY_EXISTS
            try {
                (*it)->AddFace(AFace);
            } 
            catch (...) {
                return Res::FACE_ALREADY_EXISTS;
            }
            return Res::OK;
        }
    }
    // 若未找到指定模型，返回MODEL_NOT_FOUND
    return Res::FACE_NOT_FOUND;
}
/*************************************************************************
【函数名称】AddFace
【函数功能】向指定位置的模型中添加面
【参数】const Face3D& AFace, 要添加的面
       size_t Index, 模型位置
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::AddFace(
    const Face3D& AFace, size_t ModelIndex) {
    // 若Index超出范围找不到指定模型，返回MODEL_NOT_FOUND
    if (ModelIndex < m_pModel.size()) {
        // 若面已存在，返回FACE_ALREADY_EXISTS
        try {
            m_pModel[ModelIndex]->AddFace(AFace);
        } 
        catch (...) {
            return Res::FACE_ALREADY_EXISTS;
        }
        return Res::OK;
    }
    return Res::MODEL_NOT_FOUND;
}
/*************************************************************************
【函数名称】AddFace
【函数功能】向当前模型中添加面(通过三个点坐标)
【参数】const double x1, const double y1, const double z1,
       const double x2, const double y2, const double z2,
       const double x3, const double y3, const double z3,
       表示三个点坐标
       size_t Index, 模型位置
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::AddFace(
    const double x1, const double y1,
    const double z1, const double x2,
    const double y2, const double z2,
    const double x3, const double y3,
    const double z3, size_t ModelIndex) {
    // 创建三个点
    Point3D Point1(x1, y1, z1);
    Point3D Point2(x2, y2, z2);
    Point3D Point3(x3, y3, z3);
    // 若存在相同点，返回POINT_DUPLICATED
    if (Point1 == Point2 || Point1 == Point3 || Point2 == Point3) {
        return Res::POINT_DUPLICATED;
    }
    if (ModelIndex < m_pModel.size()) {
        // 若面已存在，返回FACE_ALREADY_EXISTS
        try {
            m_pModel[ModelIndex]->AddFace(
                Point3D(x1, y1, z1), 
                Point3D(x2, y2, z2), 
                Point3D(x3, y3, z3));
        } 
        catch (...) {
            return Res::FACE_ALREADY_EXISTS;
        }
        return Res::OK;
    }
    // 若Index超出范围找不到指定模型，返回MODEL_NOT_FOUND
    return Res::MODEL_NOT_FOUND;
}
/*************************************************************************
【函数名称】AddFace
【函数功能】向当前模型中添加面(通过三个点坐标)
【参数】const double x1, const double y1, const double z1,
       const double x2, const double y2, const double z2,
       const double x3, const double y3, const double z3,
       表示三个点坐标
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::AddFace(
    const double x1, const double y1,
    const double z1, const double x2,
    const double y2, const double z2,
    const double x3, const double y3,
    const double z3) {
    return AddFace(x1, y1, z1, x2, y2, z2, x3, y3, z3, m_ullCurrentModelIndex);
}
/*************************************************************************
【函数名称】AddFace
【函数功能】向当前模型中添加面
【参数】const Face3D& AFace, 要添加的面
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::AddFace(const Face3D& AFace) {
    // 若面已存在，返回FACE_ALREADY_EXISTS
    try {
        m_pModel[m_ullCurrentModelIndex]->AddFace(AFace);
    } 
    catch (...) {
        return Res::FACE_ALREADY_EXISTS;
    }
    return Res::OK;
}
/*************************************************************************
【函数名称】RemoveFace
【函数功能】从指定模型中删除面
【参数】const Face3D& AFace, 要删除的面
       const Model3D& AModel, 指定模型
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::RemoveFace(
    const Face3D& AFace, const Model3D& AModel) {
    for (auto it = m_pModel.begin(); it != m_pModel.end(); ++it) {
        // 若找到指定模型，从该模型中删除面
        if (**it == AModel) {
            (*it)->RemoveFace(AFace);
            return Res::OK;
        }
    }
    // 若未找到指定模型，返回MODEL_NOT_FOUND
    return Res::FACE_NOT_FOUND;
}
/*************************************************************************
【函数名称】RemoveFace
【函数功能】从指定位置的模型中删除面
【参数】size_t ModelIndex, 模型位置
       size_t FaceIndex, 面位置
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::RemoveFace(size_t ModelIndex, size_t FaceIndex) {
    // 若Index超出范围找不到指定模型，返回MODEL_NOT_FOUND
    if (ModelIndex >= m_pModel.size()) {
        return Res::MODEL_NOT_FOUND;
    }
    // 若Index超出范围找不到指定面，返回FACE_NOT_FOUND
    if (FaceIndex >= m_pModel[ModelIndex]->Faces().size()) {
        return Res::FACE_NOT_FOUND;
    }
    m_pModel[ModelIndex]->RemoveFace(
        *m_pModel[ModelIndex]->Faces()[FaceIndex]);
    return Res::OK;
}
/*************************************************************************
【函数名称】RemoveFace
【函数功能】从当前模型中删除面
【参数】size_t FaceIndex, 面位置
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::RemoveFace(size_t FaceIndex) {
    // 若Index超出范围找不到指定面，返回FACE_NOT_FOUND
    if (FaceIndex >= m_pModel[m_ullCurrentModelIndex]->Faces().size()) {
        return Res::FACE_NOT_FOUND;
    }
    // 从当前模型中删除面
    m_pModel[m_ullCurrentModelIndex]->RemoveFace(
        *m_pModel[m_ullCurrentModelIndex]->Faces()[FaceIndex]);
    return Res::OK;
}
/*************************************************************************
【函数名称】AddLine
【函数功能】向指定模型中添加线
【参数】const Line3D& ALine, 要添加的线
       const Model3D& AModel, 指定模型
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::AddLine(
    const Line3D& ALine, const Model3D& AModel) {
    // 遍历模型列表, 若找到指定模型，向该模型中添加线
    for (auto it = m_pModel.begin(); it != m_pModel.end(); ++it) {
        if (**it == AModel) {
            (*it)->AddLine(ALine);
            return Res::OK;
        }
    }
    // 若未找到指定模型，返回MODEL_NOT_FOUND
    return Res::MODEL_NOT_FOUND;
}
/*************************************************************************
【函数名称】AddLine
【函数功能】向指定位置的模型中添加线
【参数】const Line3D& ALine, 要添加的线
       size_t ModelIndex, 模型位置
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::AddLine(const Line3D& ALine, size_t ModelIndex) {
    if (ModelIndex < m_pModel.size()) {
        // 若线已存在，返回LINE_ALREADY_EXISTS
        try {
            m_pModel[ModelIndex]->AddLine(ALine);
        } 
        catch (...) {
            return Res::LINE_ALREADY_EXISTS;
        }
        return Res::OK;
    }
    // 若ModelIndex超出范围找不到指定模型，返回MODEL_NOT_FOUND
    return Res::MODEL_NOT_FOUND;
}
/*************************************************************************
【函数名称】AddLine
【函数功能】向当前模型中添加线(通过两个点坐标)
【参数】const double x1, const double y1, const double z1,
       const double x2, const double y2, const double z2,
       表示两个点坐标
       size_t ModelIndex, 模型位置
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::AddLine(
    const double x1, const double y1,
    const double z1, const double x2,
    const double y2, const double z2,
    size_t ModelIndex) {
    if (ModelIndex < m_pModel.size()) {
        // 若线已存在，返回LINE_ALREADY_EXISTS
        try {
            m_pModel[ModelIndex]->AddLine(
                Point3D(x1, y1, z1), Point3D(x2, y2, z2));
        } 
        catch (...) {
            return Res::LINE_ALREADY_EXISTS;
        }
        return Res::OK;
    }
    // 若ModelIndex超出范围找不到指定模型，返回MODEL_NOT_FOUND
    return Res::MODEL_NOT_FOUND;
}
/*************************************************************************
【函数名称】AddLine
【函数功能】向当前模型中添加线(通过两个点坐标)
【参数】const double x1, const double y1, const double z1,
       const double x2, const double y2, const double z2,
       表示两个点坐标
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::AddLine(
    const double x1, const double y1,
    const double z1, const double x2,
    const double y2, const double z2) {
    return AddLine(x1, y1, z1, x2, y2, z2, m_ullCurrentModelIndex);
}
/*************************************************************************
【函数名称】AddLine
【函数功能】向当前模型中添加线
【参数】const Line3D& ALine, 要添加的线
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::AddLine(const Line3D& ALine) {
    // 若线已存在，返回LINE_ALREADY_EXISTS
    try {
        m_pModel[m_ullCurrentModelIndex]->AddLine(ALine);
    } 
    catch (...) {
        return Res::LINE_ALREADY_EXISTS;
    }
    return Res::OK;
}
/*************************************************************************
【函数名称】RemoveLine
【函数功能】从指定模型中删除线
【参数】const Line3D& ALine, 要删除的线
       const Model3D& AModel, 指定模型
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::RemoveLine(
    const Line3D& ALine, const Model3D& AModel) {
    // 遍历模型列表, 若找到指定模型，从该模型中删除线
    for (auto it = m_pModel.begin(); it != m_pModel.end(); ++it) {
        if (**it == AModel) {
            (*it)->RemoveLine(ALine);
            return Res::OK;
        }
    }
    // 若未找到指定模型，返回MODEL_NOT_FOUND
    return Res::LINE_NOT_FOUND;
}
/*************************************************************************
【函数名称】RemoveLine
【函数功能】从指定位置的模型中删除线
【参数】size_t ModelIndex, 模型位置
       size_t LineIndex, 线位置
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::RemoveLine(size_t ModelIndex, size_t LineIndex) {
    // 若Index超出范围找不到指定模型，返回MODEL_NOT_FOUND
    if (ModelIndex >= m_pModel.size()) {
        return Res::MODEL_NOT_FOUND;
    }
    // 若Index超出范围找不到指定线，返回LINE_NOT_FOUND
    if (LineIndex >= m_pModel[ModelIndex]->Lines().size()) {
        return Res::LINE_NOT_FOUND;
    }
    m_pModel[ModelIndex]->RemoveLine(
        *m_pModel[ModelIndex]->Lines()[LineIndex]);
    return Res::OK;
}
/*************************************************************************
【函数名称】RemoveLine
【函数功能】从当前模型中删除线
【参数】size_t LineIndex, 线位置
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::RemoveLine(size_t LineIndex) {
    // 若Index超出范围找不到指定线，返回LINE_NOT_FOUND
    if (LineIndex >= m_pModel[m_ullCurrentModelIndex]->Lines().size()) {
        return Res::LINE_NOT_FOUND;
    }
    m_pModel[m_ullCurrentModelIndex]->RemoveLine(
        *m_pModel[m_ullCurrentModelIndex]->Lines()[LineIndex]);
    return Res::OK;
}
/*************************************************************************
【函数名称】ChangeFacePoint
【函数功能】修改指定模型指定面中的指定点
【参数】size_t ModelIndex, 模型位置
       size_t FaceIndex, 面位置
       size_t PointIndex, 点位置
       const Point3D& NewPoint, 新点坐标
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】2024/8/12 谭雯心 增加了可能抛出的异常
*************************************************************************/
Controller::Res Controller::ChangeFacePoint(
    size_t ModelIndex, 
    size_t FaceIndex,
    size_t PointIndex,
    const Point3D& NewPoint) {
    // 若ModelIndex超出范围找不到指定模型，返回MODEL_NOT_FOUND
    if (ModelIndex >= m_pModel.size()) {
        return Res::MODEL_NOT_FOUND;
    }
    // 若FaceIndex超出范围找不到指定面，返回FACE_NOT_FOUND
    if (FaceIndex >= m_pModel[ModelIndex]->Faces().size()) {
        return Res::FACE_NOT_FOUND;
    }
    // 若PointIndex超出范围找不到指定点，返回POINT_NOT_FOUND
    if (PointIndex >= 3) {
        return Res::POINT_NOT_FOUND;
    }
    // 创建新的Model3D对象
    Model3D AModel = *m_pModel[ModelIndex];
    // 若存在相同点，返回POINT_DUPLICATED
    try {
        AModel.ChangeFacePoint(*AModel.Faces()[FaceIndex], PointIndex,
                               NewPoint);
    } 
    catch (...) {
        return Res::POINT_DUPLICATED;
    }
    // 若修改点后的面已存在，返回FACE_ALREADY_EXISTS
    if (m_pModel[ModelIndex]->ContainFace(*AModel.Faces()[FaceIndex])) {
        return Res::FACE_ALREADY_EXISTS;
    } 
    else {
        // 若无异常则修改指定模型指定面中的指定点
        m_pModel[ModelIndex] = make_shared<Model3D>(AModel);
    }
    return Res::OK;
}
/*************************************************************************
【函数名称】ChangeFacePoint
【函数功能】修改指定模型指定面中的指定点
【参数】size_t ModelIndex, 模型位置
       size_t FaceIndex, 面位置
       size_t PointIndex, 点位置
       const double x, const double y, const double z, 新点坐标
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/13
【更改记录】
*************************************************************************/
Controller::Res Controller::ChangeFacePoint(
    size_t ModelIndex, 
    size_t FaceIndex,
    size_t PointIndex, 
    const double x,
    const double y, 
    const double z) {
    return ChangeFacePoint(
        ModelIndex, FaceIndex, PointIndex, Point3D(x, y, z));
}
/*************************************************************************
【函数名称】ChangeFacePoint
【函数功能】修改当前模型指定面中的指定点
【参数】size_t FaceIndex, 面位置
       size_t PointIndex, 点位置
       const Point3D& NewPoint, 新点坐标
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::ChangeFacePoint(
    size_t FaceIndex, 
    size_t PointIndex,
    const Point3D& NewPoint) {
    return ChangeFacePoint(
        m_ullCurrentModelIndex, FaceIndex, PointIndex, NewPoint);
}
/*************************************************************************
【函数名称】ChangeFacePoint
【函数功能】修改当前模型指定面中的指定点
【参数】size_t FaceIndex, 面位置
       size_t PointIndex, 点位置
       const double x, const double y, const double z, 新点坐标
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/13
【更改记录】
*************************************************************************/
Controller::Res Controller::ChangeFacePoint(
    size_t FaceIndex, 
    size_t PointIndex,
    const double x, 
    const double y,
    const double z) {
    return ChangeFacePoint(
        m_ullCurrentModelIndex, FaceIndex, PointIndex, Point3D(x, y, z));
}
/*************************************************************************
【函数名称】ChangeLinePoint
【函数功能】修改指定模型指定线中的指定点
【参数】size_t ModelIndex, 模型位置
       size_t LineIndex, 线位置
       size_t PointIndex, 点位置
       const Point3D& NewPoint, 新点坐标
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】2024/8/12 谭雯心 增加了可能抛出的异常
*************************************************************************/
Controller::Res Controller::ChangeLinePoint(
    size_t ModelIndex, 
    size_t LineIndex,
    size_t PointIndex,
    const Point3D& NewPoint) {
    // 若ModlIndex超出范围找不到指定模型，返回MODEL_NOT_FOUND
    if (ModelIndex >= m_pModel.size()) {
        return Res::MODEL_NOT_FOUND;
    }
    // 若LineIndex超出范围找不到指定线，返回LINE_NOT_FOUND
    if (LineIndex >= m_pModel[ModelIndex]->Lines().size()) {
        return Res::LINE_NOT_FOUND;
    }
    // 若PointIndex超出范围找不到指定点，返回POINT_NOT_FOUND
    if (PointIndex >= 2) {
        return Res::POINT_NOT_FOUND;
    }
    // 创建新的Model3D对象
    Model3D AModel = *m_pModel[ModelIndex];
    // 若存在相同点，返回POINT_DUPLICATED
    try {
        AModel.ChangeLinePoint(
            *AModel.Lines()[LineIndex], PointIndex, NewPoint);
    } 
    catch (...) {
        return Res::POINT_DUPLICATED;
    }
    // 若修改点后的线已存在，返回LINE_ALREADY_EXISTS
    if (m_pModel[ModelIndex]->ContainLine(*AModel.Lines()[LineIndex])) {
        return Res::LINE_ALREADY_EXISTS;
    } 
    else {
        m_pModel[ModelIndex] = make_shared<Model3D>(AModel);
    }
    return Res::OK;
}
/*************************************************************************
【函数名称】ChangeLinePoint
【函数功能】修改指定模型指定线中的指定点
【参数】size_t ModelIndex, 模型位置
       size_t LineIndex, 线位置
       size_t PointIndex, 点位置
       const double x, const double y, const double z, 新点坐标
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/13
【更改记录】
*************************************************************************/
Controller::Res Controller::ChangeLinePoint(
    size_t ModelIndex, 
    size_t LineIndex,
    size_t PointIndex, 
    const double x,
    const double y, 
    const double z) {
    return ChangeLinePoint(
        ModelIndex, LineIndex, PointIndex, Point3D(x, y, z));
}
/*************************************************************************
【函数名称】ChangeLinePoint
【函数功能】修改当前模型指定线中的指定点
【参数】size_t LineIndex, 线位置
       size_t PointIndex, 点位置
       const Point3D& NewPoint, 新点坐标
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::ChangeLinePoint(
    size_t LineIndex, 
    size_t PointIndex,
    const Point3D& NewPoint) {
    return ChangeLinePoint(
        m_ullCurrentModelIndex, LineIndex, PointIndex, NewPoint);
}
/*************************************************************************
【函数名称】ChangeLinePoint
【函数功能】修改当前模型指定线中的指定点
【参数】size_t LineIndex, 线位置
       size_t PointIndex, 点位置
       const Point3D& NewPoint, 新点坐标
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/13
【更改记录】
*************************************************************************/
Controller::Res Controller::ChangeLinePoint(
    size_t LineIndex, 
    size_t PointIndex,
    const double x, 
    const double y,
    const double z) {
    return ChangeLinePoint(LineIndex, PointIndex, Point3D(x, y, z));
}
/*************************************************************************
【函数名称】ClearFaces
【函数功能】清空指定模型中的面
【参数】const Model3D& AModel, 指定模型
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::ClearFaces(const Model3D& AModel) {
    for (auto it = m_pModel.begin(); it != m_pModel.end(); ++it) {
        if (**it == AModel) {
            (*it)->ClearFaces();
            return Res::OK;
        }
    }
    // 若遍历未找到指定模型，返回MODEL_NOT_FOUND
    return Res::MODEL_NOT_FOUND;
}
/*************************************************************************
【函数名称】ClearFaces
【函数功能】清空指定位置模型中的面
【参数】size_t Index, 模型位置
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::ClearFaces(size_t ModelIndex) {
    if (ModelIndex < m_pModel.size()) {
        m_pModel[ModelIndex]->ClearFaces();
        return Res::OK;
    }
    // 若ModelIndex超出范围找不到指定模型，返回MODEL_NOT_FOUND
    return Res::MODEL_NOT_FOUND;
}
/*************************************************************************
【函数名称】ClearFaces
【函数功能】清空当前模型中的面
【参数】无
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::ClearFaces() {
    m_pModel[m_ullCurrentModelIndex]->ClearFaces();
    return Res::OK;
}
/*************************************************************************
【函数名称】ClearLines
【函数功能】清空指定模型中的线
【参数】const Model3D& AModel, 指定模型
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::ClearLines(const Model3D& AModel) {
    for (auto it = m_pModel.begin(); it != m_pModel.end(); ++it) {
        if (**it == AModel) {
            (*it)->ClearLines();
            return Res::OK;
        }
    }
    // 若遍历未找到指定模型，返回MODEL_NOT_FOUND
    return Res::MODEL_NOT_FOUND;
}
/*************************************************************************
【函数名称】ClearLines
【函数功能】清空指定位置模型中的线
【参数】size_t Index, 模型位置
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::ClearLines(size_t ModelIndex) {
    if (ModelIndex < m_pModel.size()) {
        m_pModel[ModelIndex]->ClearLines();
        return Res::OK;
    }
    // 若ModelIndex超出范围找不到指定模型，返回MODEL_NOT_FOUND
    return Res::MODEL_NOT_FOUND;
}
/*************************************************************************
【函数名称】ClearLines
【函数功能】清空当前模型中的线
【参数】无
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::ClearLines() {
    m_pModel[m_ullCurrentModelIndex]->ClearLines();
    return Res::OK;
}
/*************************************************************************
【函数名称】Clear
【函数功能】清空指定模型中的所有内容
【参数】const Model3D& AModel, 指定模型
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::Clear(const Model3D& AModel) {
    for (auto it = m_pModel.begin(); it != m_pModel.end(); ++it) {
        if (**it == AModel) {
            (*it)->Clear();
            return Res::OK;
        }
    }
    // 若遍历未找到指定模型，返回MODEL_NOT_FOUND
    return Res::MODEL_NOT_FOUND;
}
/*************************************************************************
【函数名称】Clear
【函数功能】清空指定位置模型中的所有内容
【参数】size_t Index, 模型位置
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::Clear(size_t ModelIndex) {
    if (ModelIndex < m_pModel.size()) {
        m_pModel[ModelIndex]->Clear();
        return Res::OK;
    }
    // 若ModelIndex超出范围找不到指定模型，返回MODEL_NOT_FOUND
    return Res::MODEL_NOT_FOUND;
}
/*************************************************************************
【函数名称】Clear
【函数功能】清空当前模型中的所有内容
【参数】无
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::Clear() {
    m_pModel[m_ullCurrentModelIndex]->Clear();
    return Res::OK;
}
/*************************************************************************
【函数名称】ChangeName
【函数功能】修改指定模型的名称
【参数】size_t ModelIndex, 模型位置
       const string& NewName, 新名称
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::ChangeName(
    size_t ModelIndex, const string& NewName) {
    if (ModelIndex < m_pModel.size()) {
        m_pModel[ModelIndex]->Name = NewName;
        return Res::OK;
    }
    // 若ModelIndex超出范围找不到指定模型，返回MODEL_NOT_FOUND
    return Res::MODEL_NOT_FOUND;
}
/*************************************************************************
【函数名称】ChangeName
【函数功能】修改当前模型的名称
【参数】const string& NewName, 新名称
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::ChangeName(const string& NewName) {
    return ChangeName(m_ullCurrentModelIndex, NewName);
}
/*************************************************************************
【函数名称】ChangeDescription
【函数功能】修改指定模型的注释
【参数】size_t ModelIndex, 模型位置
       const string& NewDescription, 新注释
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::ChangeDescription(
    size_t ModelIndex, const string& NewDescription) {
    if (ModelIndex < m_pModel.size()) {
        m_pModel[ModelIndex]->Description = NewDescription;
        return Res::OK;
    }
    // 若ModelIndex超出范围找不到指定模型，返回MODEL_NOT_FOUND
    return Res::MODEL_NOT_FOUND;
}
/*************************************************************************
【函数名称】ChangeDescription
【函数功能】修改指定模型的注释
【参数】const string& NewDescription, 新注释
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::ChangeDescription(const string& NewDescription) {
    return ChangeDescription(m_ullCurrentModelIndex, NewDescription);
}

//---------------------------------------------------------------------
// 静态成员函数
//---------------------------------------------------------------------

/*************************************************************************
【函数名称】GetInstance
【函数功能】获取Controller类的唯一实例
【参数】无
【返回值】shared_ptr<Controller>类型，Controller类的唯一实例
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
shared_ptr<Controller> Controller::GetInstance() {
    if (m_pInstance == nullptr) {
        m_pInstance = shared_ptr<Controller>(new Controller());
    }
    return m_pInstance;
}

//---------------------------------------------------------------------
// 非静态Getter成员函数
//---------------------------------------------------------------------

/*************************************************************************
【函数名称】ControllerResStr const
【函数功能】返回ControllerRes枚举类型的字符串
【参数】ControllerRes Res
【返回值】const string&
【开发者及日期】谭雯心 2024/8/9
【更改记录】2024/8/12 谭雯心 修改了将ControllerRes枚举类转为字符串的逻辑
*************************************************************************/
const string& Controller::ControllerResStr(ControllerRes Res) const {
    // ControllerRes枚举类型的字符串
    static const string ResStr[] = {"OK",
                                    "FILE_NOT_SUPPORTED",
                                    "FILE_NOT_AVAILABLE",
                                    "FILE_NOT_CLOSED",
                                    "POINT_DUPLICATED",
                                    "POINT_NOT_FOUND",
                                    "FACE_ALREADY_EXISTS",
                                    "FACE_NOT_FOUND",
                                    "LINE_ALREADY_EXISTS",
                                    "LINE_NOT_FOUND",
                                    "MODEL_ALREADY_EXISTS",
                                    "MODEL_NOT_FOUND",
                                    "UNKNOWN_TYPE"};
    return ResStr[static_cast<size_t>(Res)];
}
/*************************************************************************
【函数名称】ListALLModelInfo
【函数功能】列出所有模型统计信息
【参数】ModelInfoList& InfoList, 模型统计信息列表
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::ListALLModelInfo(ModelInfoList& InfoList) const {
    // 清空模型统计信息列表
    InfoList.clear();
    // 遍历模型列表，调用ListModelInfo函数存储所有模型统计信息
    for (size_t i = 0; i < m_pModel.size(); i++) {
        ListModelInfo(i, InfoList[i]);
    }
    return Res::OK;
}
/*************************************************************************
【函数名称】ListModelInfo
【函数功能】列出指定位置模型统计信息
【参数】size_t ModelIndex, 模型位置
       ModelInfo& Info, 模型统计信息
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】2024/8/10 谭雯心 修改了获取模型信息的方式
*************************************************************************/
Controller::Res Controller::ListModelInfo(
    size_t ModelIndex, ModelInfo& Info) const {
    // 若ModelIndex在模型列表范围内，调用Model3D类的相关函数获取模型统计信息
    if (ModelIndex < m_pModel.size()) {
        Info.Name = m_pModel[ModelIndex]->Name;
        Info.FaceCount = m_pModel[ModelIndex]->GetFaceCount();
        Info.LineCount = m_pModel[ModelIndex]->GetLineCount();
        Info.PointCount = m_pModel[ModelIndex]->GetPointCount();
        Info.ElementCount = m_pModel[ModelIndex]->GetElementCount();
        Info.Area = m_pModel[ModelIndex]->Area();
        Info.Length = m_pModel[ModelIndex]->Length();
        Info.Volume = m_pModel[ModelIndex]->BoundingBoxVolume();
        return Res::OK;
    }
    // 若ModelIndex超出范围找不到指定模型，返回MODEL_NOT_FOUND
    return Res::MODEL_NOT_FOUND;
}
/*************************************************************************
【函数名称】ListModelInfo
【函数功能】列出当前模型统计信息
【参数】ModelInfo& Info, 模型统计信息
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::ListModelInfo(ModelInfo& Info) const {
    return ListModelInfo(m_ullCurrentModelIndex, Info);
}
/*************************************************************************
【函数名称】ListFaceInfo
【函数功能】列出指定位置模型中所有Face3D的信息
【参数】size_t ModelIndex, 模型位置
       FaceInfoList& Info, 面信息列表
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::ListFaceInfo(
    size_t ModelIndex, FaceInfoList& InfoList) const {
    // 若ModelIndex超出范围找不到指定模型，返回MODEL_NOT_FOUND
    if (ModelIndex >= m_pModel.size()) {
        return Res::MODEL_NOT_FOUND;
    }
    InfoList.clear();
    for (auto Face : m_pModel[ModelIndex]->Faces()) {
        FaceInfo AFaceInfo;
        for (size_t i = 0; i < 3; i++) {
            // 将Face3D中的点坐标存入FaceInfo中
            AFaceInfo.Points[i].x = Face->Points[i].X;
            AFaceInfo.Points[i].y = Face->Points[i].Y;
            AFaceInfo.Points[i].z = Face->Points[i].Z;
        }
        AFaceInfo.Area = Face->Area();
        InfoList.push_back(AFaceInfo);
    }
    return Res::OK;
}
/*************************************************************************
【函数名称】ListFaceInfo
【函数功能】列出当前模型中所有Face3D的信息
【参数】FaceInfoList& Info, 面信息列表
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::ListFaceInfo(FaceInfoList& InfoList) const {
    return ListFaceInfo(m_ullCurrentModelIndex, InfoList);
}
/*************************************************************************
【函数名称】ListLineInfo
【函数功能】列出指定位置模型中所有Line3D的信息
【参数】size_t ModelIndex, 模型位置
       LineInfoList& Info, 线信息列表
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::ListLineInfo(
    size_t ModelIndex, LineInfoList& InfoList) const {
    if (ModelIndex < m_pModel.size()) {
        InfoList.clear();
        for (auto Line : m_pModel[ModelIndex]->Lines()) {
            LineInfo ALineInfo;
            for (size_t i = 0; i < 2; i++) {
                // 将Line3D中的点坐标存入LineInfo中
                ALineInfo.Points[i].x = Line->Points[i].X;
                ALineInfo.Points[i].y = Line->Points[i].Y;
                ALineInfo.Points[i].z = Line->Points[i].Z;
            }
            ALineInfo.Length = Line->Length();
            InfoList.push_back(ALineInfo);
        }
        return Res::OK;
    }
    // 若ModelIndex超出范围找不到指定模型，返回MODEL_NOT_FOUND
    return Res::MODEL_NOT_FOUND;
}
/*************************************************************************
【函数名称】ListLineInfo
【函数功能】列出当前模型中所有Line3D的信息
【参数】LineInfoList& Info, 线信息列表
【返回值】Controller::Res枚举类型
【开发者及日期】谭雯心 2024/8/9
【更改记录】
*************************************************************************/
Controller::Res Controller::ListLineInfo(LineInfoList& InfoList) const {
    return ListLineInfo(m_ullCurrentModelIndex, InfoList);
}
