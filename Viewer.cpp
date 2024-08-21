/*************************************************************************
【文件名】Viewer.cpp
【功能模块和目的】定义Viewer类的成员函数
【开发者及日期】谭雯心 2024/8/10
【更改记录】
*************************************************************************/
// 包含Viewer.hpp头文件
#include "Viewer.hpp"
// 包含Controller.hpp头文件
#include "Controller.hpp"
// cin, cout所属头文件
#include <iostream>
// numeric_limits所属头文件
#include <limits>
// shared_ptr所属头文件
#include <memory>
// string, stoi所属头文件
#include <string>
// size_t所属头文件
#include <cstddef>

using namespace std;

// 使用using声明Controller::Res枚举类型别名
using Res = Controller::Res;

//---------------------------------------------------------------------------------
// 必要的构造、析构函数
//---------------------------------------------------------------------------------

/*************************************************************************
【函数名称】Viewer
【函数功能】构造函数，显示主菜单
【参数】无
【返回值】无
【开发者及日期】谭雯心 2024/8/10
【更改记录】
*************************************************************************/
Viewer::Viewer() { 
    // 显示主菜单
    cout << MainMenu() << endl; 
}
/*************************************************************************
【函数名称】MainMenu
【函数功能】显示主菜单
【参数】无
【返回值】string
【开发者及日期】谭雯心 2024/8/10
【更改记录】
*************************************************************************/
string Viewer::MainMenu() {
    string Selection;
    cout << "==========WELCOME TO THE MODEL VIEWER==========" << endl;
    // 当用户输入不合法时，循环显示主菜单
    while (Selection != "1" && Selection != "2" && Selection != "3"
        && Selection != "4" && Selection != "5" && Selection != "6"
        && Selection != "7" && Selection != "8" && Selection != "9" 
        && Selection != "0") {
        cout << "----------MAIN MENU----------" << endl;
        cout << "1. Create Model" << endl;
        cout << "2. Select Model" << endl;
        cout << "3. Load Model" << endl;
        cout << "4. Save Model" << endl;
        cout << "5. Remove Model" << endl;
        cout << "6. Edit the Current Model" << endl;
        cout << "7. List Models Information" << endl;
        cout << "8. List Faces Information" << endl;
        cout << "9. List Lines Information" << endl;
        cout << "0. Exit" << endl;
        cout << "Please select an option: (0-9): ";
        getline(cin, Selection);
        // 根据用户选择的选项，调用相应的函数
        switch (Selection[0]) {
            case '1' :
                cout << CreateModelMenu() << endl;
                break;
            case '2' :
                cout << SelectModelMenu() << endl;
                break;
            case '3' :
                cout << LoadModelMenu() << endl;
                break;
            case '4' :
                cout << SaveModelMenu() << endl;
                break;
            case '5' :
                cout << RemoveModelMenu() << endl;
                break;
            case '6' :
                cout << EditModelMenu() << endl;
                break;
            case '7' :
                cout << ListModelInfoMenu() << endl;
                break;
            case '8' :
                cout << ListFaceInfoMenu() << endl;
                break;
            case '9' :
                cout << ListLineInfoMenu() << endl;
                break;
            case '0' :
                // 退出程序
                cout << "Are you sure to exit? (Y/N): ";
                Selection.clear();
                getline(cin, Selection);
                if (Selection == "Y" || Selection == "y") {
                    return "EXIT";
                }
                break;
            default :
                continue;
        }
        Selection.clear();
    }
    return "";
}
/*************************************************************************
【函数名称】SelectModelMenu
【函数功能】显示选择当前模型菜单
【参数】无
【返回值】string
【开发者及日期】谭雯心 2024/8/10
【更改记录】2024/8/12 谭雯心 修改了键入q或Q时返回主菜单的逻辑
*************************************************************************/
string Viewer::SelectModelMenu() {
    // 获取Controller类的唯一实例
    shared_ptr<Controller> pController = Controller::GetInstance();
    string Selection;
    // 当用户选择不返回主菜单时，循环显示选择当前模型菜单
    while (Selection != "Y" && Selection != "y") {
        cout << "----------SELECT MODEL----------" << endl;
        // 如果Controller类中没有模型，提示用户先创建模型
        if (pController->Models.size() == 0) {
            cout << "No model can be selected, "
                << "please create a model first!" << endl;
            return "";
        }
        cout << "Please input the selected model index(enter q to quit): (0-"
            << pController->Models.size() - 1 << "): ";
        string Index;
        cin >> Index;
        if (Index == "q" || Index == "Q") {
            return "";
        }
        // 清空输入缓冲区
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // 如果用户选择的模型已经是当前模型，提示用户
        if (pController->CurrentModelIndex 
            == static_cast<size_t>(stoi(Index))) {
            cout << "Model[" << Index
                << "] is already selected as current model!" << endl;
        } 
        else {
            // 设置当前模型
            Res res =
                pController->SetCurrentModel(static_cast<size_t>(stoi(Index)));
            // 如果设置失败，提示用户
            if (res != Res::OK) {
                cout << pController->ControllerResStr(res) << endl;
            } 
            else {
                cout << "Model[" << Index
                    << "] is selected as current model successfully!" << endl;
            }
        }
        Selection.clear();
        // 当用户输入不合法时，循环提示用户返回主菜单
        while (Selection != "Y" && Selection != "y" 
            && Selection != "N" && Selection != "n") {
            cout << "Back to main menu? (Y/N): ";
            getline(cin, Selection);
            if (Selection == "Y" || Selection == "y") {
                cout << "----------BACK TO MAIN MENU----------" << endl;
            }
        }
    }
    return "";
}
/*************************************************************************
【函数名称】CreateModelMenu
【函数功能】显示创建模型菜单
【参数】无
【返回值】string
【开发者及日期】谭雯心 2024/8/10
【更改记录】
*************************************************************************/
string Viewer::CreateModelMenu() {
    // 获取Controller类的唯一实例
    shared_ptr<Controller> pController = Controller::GetInstance();
    string Selection;
    // 当用户选择继续创建模型时，循环显示创建模型菜单
    while (Selection != "N" && Selection != "n") {
        cout << "----------CREATE MODEL----------" << endl;
        Res res = pController->CreateModel();
        // 如果创建模型失败，提示用户
        if (res != Res::OK) {
            cout << pController->ControllerResStr(res) << endl;
        } 
         {
            cout << "1 empty model has been created and selected successfully!"
                << endl;
            cout << "The current model is M[" 
                << pController->CurrentModelIndex << "]" << endl;
        }
        Selection.clear();
        // 当用户输入不合法时，循环提示用户是否继续创建模型
        while (Selection != "Y" && Selection != "y"
            && Selection != "N" && Selection != "n") {
            cout << "Do you want to create another model? (Y/N): ";
            getline(cin, Selection);
            if (Selection == "N" || Selection == "n") {
                cout << "----------BACK TO MAIN MENU----------" << endl;
            }
        }
    }
    return "";
}
/*************************************************************************
【函数名称】LoadModelMenu
【函数功能】显示导入模型菜单
【参数】无
【返回值】string
【开发者及日期】谭雯心 2024/8/10
【更改记录】2024/8/12 谭雯心 修改了键入q或Q时返回主菜单的逻辑
*************************************************************************/
string Viewer::LoadModelMenu() {
    // 获取Controller类的唯一实例
    shared_ptr<Controller> pController = Controller::GetInstance();
    string Selection;
    // 当用户选择继续导入模型时，循环显示导入模型菜单
    while (Selection != "N" && Selection != "n") {
        cout << "----------LOAD MODEL----------" << endl;
        // 如果没有选择当前模型，提示用户先选择当前模型
        if (pController->CurrentModelIndex == numeric_limits<size_t>::max()) {
            cout << "No model has been selected as current model, "
                << "please select a model first!" << endl;
            return "";
        }
        cout << "Please input the the file to be loaded (enter q to quit): ";
        string FileName;
        getline(cin, FileName);
        // 如果用户输入q或Q，返回主菜单
        if (FileName == "q" || FileName == "Q") {
            return "";
        }
        // 导入模型
        Res res = pController->LoadModelFromFile(FileName);
        // 如果导入模型失败，提示用户
        if (res != Res::OK) {
            cout << pController->ControllerResStr(res) << endl;
        } 
        else {
            cout << "Model loaded successfully!" << endl;
        }
        Selection.clear();
        while (Selection != "Y" && Selection != "y" 
            && Selection != "N" && Selection != "n") {
            cout << "Do you want to load another model? (Y/N): ";
            getline(cin, Selection);
            if (Selection == "N" || Selection == "n") {
                cout << "----------BACK TO MAIN MENU----------" << endl;
            }
        }
    }
    return "";
}
/*************************************************************************
【函数名称】SaveModelMenu
【函数功能】显示导出模型菜单
【参数】无
【返回值】string
【开发者及日期】谭雯心 2024/8/10
【更改记录】2024/8/12 谭雯心 修改了键入q或Q时返回主菜单的逻辑
*************************************************************************/
string Viewer::SaveModelMenu() {
    // 获取Controller类的唯一实例
    shared_ptr<Controller> pController = Controller::GetInstance();
    string Selection;
    // 当用户选择继续导出模型时，循环显示导出模型菜单
    while (Selection != "N" && Selection != "n") {
        cout << "----------SAVE MODEL----------" << endl;
        // 若用户没有选择当前模型，提示用户先选择当前模型
        if (pController->CurrentModelIndex == numeric_limits<size_t>::max()) {
            cout << "No model has been selected as current model, "
                << "please select a model first!" << endl;
            return "";
        }
        cout << "Please input the file name(enter q to quit): ";
        string FileName;
        getline(cin, FileName);
        // 如果用户输入q或Q，返回主菜单
        if (FileName == "q" || FileName == "Q") {
            return "";
        }
        // 将当前模型导出到文件
        Res res = pController->SaveModelToFile(FileName);
        // 如果导出模型失败，提示用户
        if (res != Res::OK) {
            cout << pController->ControllerResStr(res) << endl;
        } 
        else {
            cout << "Model saved successfully!" << endl;
        }
        Selection.clear();
        // 当用户输入不合法时，循环提示用户是否继续导出模型
        while (Selection != "Y" && Selection != "y"
            && Selection != "N" && Selection != "n") {
            cout << "Do you want to save another model? (Y/N): ";
            getline(cin, Selection);
            if (Selection.empty()) {
                continue;
            }
            if (Selection == "N" || Selection == "n") {
                cout << "----------BACK TO MAIN MENU----------" << endl;
            }
        }
    }
    return "";
}
/*************************************************************************
【函数名称】RemoveModelMenu
【函数功能】显示删除模型菜单
【参数】无
【返回值】string
【开发者及日期】谭雯心 2024/8/10
【更改记录】2024/8/12 谭雯心 修改了键入q或Q时返回主菜单的逻辑
*************************************************************************/
string Viewer::RemoveModelMenu() {
    // 获取Controller类的唯一实例
    shared_ptr<Controller> pController = Controller::GetInstance();
    string Selection;
    // 当用户选择继续删除模型时，循环显示删除模型菜单
    while (Selection != "N" && Selection != "n") {
        cout << "----------REMOVE MODEL----------" << endl;
        // 如果Controller类中没有模型，提示用户先创建模型
        if (pController->Models.size() == 0) {
            cout << "No model can be removed, " 
                << "please create a model first!" << endl;
            return "";
        }
        // 让用户选择删除的模型的索引
        cout << "Please input the removed model index(enter q to quit): (0-"
            << pController->Models.size() - 1 << "): ";
        string Index;
        cin >> Index;
        if (Index == "q" || Index == "Q") {
            return "";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Res res = pController->RemoveModel(static_cast<size_t>(stoi(Index)));
        if (res != Res::OK) {
            cout << pController->ControllerResStr(res) << endl;
        } 
        else {
            cout << "Model removed successfully!" << endl;
        }
        Selection.clear();
        while (Selection != "Y" && Selection != "y"
            && Selection != "N" && Selection != "n") {
            cout << "Do you want to remove another model? (Y/N): ";
            getline(cin, Selection);
            if (Selection == "N" || Selection == "n") {
                cout << "----------BACK TO MAIN MENU----------" << endl;
            }
        }
    }
    return "";
}
/*************************************************************************
【函数名称】EditModelMenu
【函数功能】显示编辑模型菜单
【参数】无
【返回值】string
【开发者及日期】谭雯心 2024/8/10
【更改记录】2024/8/12 谭雯心 修改了键入q或Q时返回主菜单的逻辑
*************************************************************************/
string Viewer::EditModelMenu() {
    // 获取Controller类的唯一实例
    shared_ptr<Controller> pController = Controller::GetInstance();
    string Selection;
    // 当用户输入不合法时，循环显示编辑模型菜单
    while (Selection != "1" && Selection != "2" && Selection != "3" 
        && Selection != "4" && Selection != "5" && Selection != "6" 
        && Selection != "7" && Selection != "8" && Selection != "9") {
        cout << "----------EDIT MODEL----------" << endl;
        // 如果没有选择当前模型，提示用户先选择当前模型
        if (pController->CurrentModelIndex == numeric_limits<size_t>::max()) {
            cout << "No model has been selected as current model, "
                << "please select a model first!" << endl;
            return "";
        }
        cout << "Model[" << pController->CurrentModelIndex
             << "] is the current model" << endl;
        cout << "1. Add Face" << endl;
        cout << "2. Add Line" << endl;
        cout << "3. Remove Face" << endl;
        cout << "4. Remove Line" << endl;
        cout << "5. Edit points in Face" << endl;
        cout << "6. Edit points in Line" << endl;
        cout << "7. Edit Model Name" << endl;
        cout << "8. Edit Model Description" << endl;
        cout << "9. Back to main menu" << endl;
        cout << "Please select an option(enter q to quit): (1-9): ";
        getline(cin, Selection);
        // 如果用户输入q或Q，返回主菜单
        if (Selection == "q" || Selection == "Q") {
            return "";
        }
        // 根据用户选择的选项，调用相应的函数
        switch (Selection[0]) {
            case '1' :
                cout << AddFaceMenu() << endl;
                break;
            case '2' :
                cout << AddLineMenu() << endl;
                break;
            case '3' :
                cout << RemoveFaceMenu() << endl;
                break;
            case '4' :
                cout << RemoveLineMenu() << endl;
                break;
            case '5' :
                cout << EditFacePointMenu() << endl;
                break;
            case '6' :
                cout << EditLinePointMenu() << endl;
                break;
            case '7' :
                cout << EditModelNameMenu() << endl;
                break;
            case '8' :
                cout << EditModelDescriptionMenu() << endl;
                break;
            case '9' :
                cout << "Are you sure to back to main menu? (Y/N): ";
                Selection.clear();
                getline(cin, Selection);
                if (Selection == "Y" || Selection == "y") {
                    return "EXIT";
                }
                break;
            // 如果用户输入不合法，输出"UNKNOWN"提示用户
            default :
                cout << "UNKNOWN" << endl;
        }
        Selection.clear();
    }
    return "";
}
/*************************************************************************
【函数名称】AddFaceMenu
【函数功能】显示添加面菜单
【参数】无
【返回值】string
【开发者及日期】谭雯心 2024/8/10
【更改记录】
*************************************************************************/
string Viewer::AddFaceMenu() {
    // 获取Controller类的唯一实例
    shared_ptr<Controller> pController = Controller::GetInstance();
    string Selection;
    // 当用户选择继续添加面时，循环显示添加面菜单
    while (Selection != "N" && Selection != "n") {
        cout << "----------ADD FACE----------" << endl;
        // 如果没有选择当前模型，提示用户先选择当前模型
        if (pController->CurrentModelIndex == numeric_limits<size_t>::max()) {
            cout << "No model has been selected as current model, "
                << "please select a model first!" << endl;
            return "";
        }
        // 让用户输入面的三个点的坐标
        double X1;
        double Y1;
        double Z1;
        double X2;
        double Y2;
        double Z2;
        double X3;
        double Y3;
        double Z3;
        cout << "The three points of the new face are: " << endl;
        cout << "Point 1: " << endl;
        cout << "X: ";
        cin >> X1;
        cout << "Y: ";
        cin >> Y1;
        cout << "Z: ";
        cin >> Z1;
        cout << "Point 2: " << endl;
        cout << "X: ";
        cin >> X2;
        cout << "Y: ";
        cin >> Y2;
        cout << "Z: ";
        cin >> Z2;
        cout << "Point 3: " << endl;
        cout << "X: ";
        cin >> X3;
        cout << "Y: ";
        cin >> Y3;
        cout << "Z: ";
        cin >> Z3;
        // 清空输入缓冲区
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Res res = pController->AddFace(X1, Y1, Z1, X2, Y2, Z2, X3, Y3, Z3);
        // 如果添加面失败，提示用户
        if (res != Res::OK) {
            cout << pController->ControllerResStr(res) << endl;
        } 
        else {
            cout << "Face added successfully!" << endl;
        }
        Selection.clear();
        while (Selection != "Y" && Selection != "y" 
            && Selection != "N" && Selection != "n") {
            cout << "Do you want to add another face? (Y/N): ";
            getline(cin, Selection);
            if (Selection == "N" || Selection == "n") {
                cout << "----------BACK TO MAIN MENU----------" << endl;
            }
        }
    }
    return "";
}
/*************************************************************************
【函数名称】AddLineMenu
【函数功能】显示添加线菜单
【参数】无
【返回值】string
【开发者及日期】谭雯心 2024/8/10
【更改记录】
*************************************************************************/
string Viewer::AddLineMenu() {
    // 获取Controller类的唯一实例
    shared_ptr<Controller> pController = Controller::GetInstance();
    string Selection;
    // 当用户选择继续添加线时，循环显示添加线菜单
    while (Selection != "N" && Selection != "n") {
        cout << "----------ADD LINE----------" << endl;
        // 如果Controller类中没有模型，提示用户先创建模型
        if (pController->CurrentModelIndex == numeric_limits<size_t>::max()) {
            cout << "No model has been selected as current model, "
                << "please select a model first!" << endl;
            return "";
        }
        // 让用户输入线的两个点的坐标
        double X1;
        double Y1;
        double Z1;
        double X2;
        double Y2;
        double Z2;
        cout << "The two points of the line are: " << endl;
        cout << "Point 1: " << endl;
        cout << "X: ";
        cin >> X1;
        cout << "Y: ";
        cin >> Y1;
        cout << "Z: ";
        cin >> Z1;
        cout << "Point 2: " << endl;
        cout << "X: ";
        cin >> X2;
        cout << "Y: ";
        cin >> Y2;
        cout << "Z: ";
        cin >> Z2;
        // 清空输入缓冲区
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Res res = pController->AddLine(X1, Y1, Z1, X2, Y2, Z2);
        // 如果添加线失败，提示用户
        if (res != Res::OK) {
            cout << pController->ControllerResStr(res) << endl;
        } 
        else {
            cout << "Line added successfully!" << endl;
        }
        Selection.clear();
        while (Selection != "Y" && Selection != "y" 
            && Selection != "N" && Selection != "n") {
            cout << "Do you want to add another line? (Y/N): ";
            getline(cin, Selection);
            if (Selection == "N" || Selection == "n") {
                cout << "----------BACK TO MAIN MENU----------" << endl;
            }
        }
    }
    return "";
}
/*************************************************************************
【函数名称】RemoveFaceMenu
【函数功能】显示删除面菜单
【参数】无
【返回值】string
【开发者及日期】谭雯心 2024/8/10
【更改记录】
*************************************************************************/
string Viewer::RemoveFaceMenu() {
    // 获取Controller类的唯一实例
    shared_ptr<Controller> pController = Controller::GetInstance();
    string Selection;
    // 当用户选择继续删除面时，循环显示删除面菜单
    while (Selection != "N" && Selection != "n") {
        // 创建面信息列表，用于存储面信息
        Controller::FaceInfoList InfoList;
        // 获取当前模型的面信息
        pController->ListFaceInfo(pController->CurrentModelIndex, InfoList);
        cout << "----------REMOVE FACE----------" << endl;
        // 如果没有选择当前模型，提示用户先选择当前模型
        if (pController->CurrentModelIndex == numeric_limits<size_t>::max()) {
            cout << "No model has been selected as current model, "
                << "please select a model first!" << endl;
            return "";
        }
        cout << "Model[" << pController->CurrentModelIndex
            << "] is the current model" << endl;
        // 如果当前模型中不存在面，提示用户先添加面
        if (InfoList.size() == 0) {
            cout << "No face can be removed, please add a face first!" << endl;
            return "";
        }
        cout << "Please input the face index to be removed: (0-"
            << InfoList.size() - 1 << "): ";
        size_t Index;
        cin >> Index;
        // 清空输入缓冲区
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Res res = pController->RemoveFace(Index);
        // 如果删除面失败，提示用户
        if (res != Res::OK) {
            cout << pController->ControllerResStr(res) << endl;
        } 
        else {
            cout << "Face removed successfully!" << endl;
        }
        Selection.clear();
        while (Selection != "Y" && Selection != "y" 
            && Selection != "N" && Selection != "n") {
            cout << "Do you want to remove another face? (Y/N): ";
            getline(cin, Selection);
            if (Selection == "N" || Selection == "n") {
                cout << "----------BACK TO MAIN MENU----------" << endl;
            }
        }
    }
    return "";
}
/*************************************************************************
【函数名称】RemoveLineMenu
【函数功能】显示删除线菜单
【参数】无
【返回值】string
【开发者及日期】谭雯心 2024/8/10
【更改记录】
*************************************************************************/
string Viewer::RemoveLineMenu() {
    // 获取Controller类的唯一实例
    shared_ptr<Controller> pController = Controller::GetInstance();
    string Selection;
    while (Selection != "N" && Selection != "n") {
        // 创建线信息列表，用于存储线信息
        Controller::LineInfoList InfoList;
        // 获取当前模型的线信息
        pController->ListLineInfo(pController->CurrentModelIndex, InfoList);
        cout << "----------REMOVE LINE----------" << endl;
        // 如果没有选择当前模型，提示用户先选择当前模型
        if (pController->CurrentModelIndex == numeric_limits<size_t>::max()) {
            cout << "No model has been selected as current model, "
                << "please select a model first!" << endl;
            return "";
        }
        // 如果当前模型中不存在线，提示用户先添加线
        if (InfoList.size() == 0) {
            cout << "No line can be removed, please add a line first!" << endl;
            return "";
        }
        cout << "Model[" << pController->CurrentModelIndex
            << "] is the current model" << endl;
        cout << "Please input the removed line index: (0-"
            << InfoList.size() - 1 << "): ";
        size_t Index;
        cin >> Index;
        // 清空输入缓冲区
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        Res res = pController->RemoveLine(Index);
        // 如果删除线失败，提示用户
        if (res != Res::OK) {
            cout << pController->ControllerResStr(res) << endl;
        } 
        else {
            cout << "Line removed successfully!" << endl;
        }
        Selection.clear();
        while (Selection != "Y" && Selection != "y"
            && Selection != "N" && Selection != "n") {
            cout << "Do you want to remove another line? (Y/N): ";
            getline(cin, Selection);
            if (Selection == "N" || Selection == "n") {
                cout << "----------BACK TO MAIN MENU----------" << endl;
            }
        }
    }
    return "";
}
/*************************************************************************
【函数名称】EditFacePointMenu
【函数功能】显示编辑面点菜单
【参数】无
【返回值】string
【开发者及日期】谭雯心 2024/8/10
【更改记录】2024/8/11 谭雯心 修改了当模型中不存在面时的提示
*************************************************************************/
string Viewer::EditFacePointMenu() {
    // 获取Controller类的唯一实例
    shared_ptr<Controller> pController = Controller::GetInstance();
    string Selection;
    // 创建面信息列表，用于存储面信息
    Controller::FaceInfoList InfoList;
    while (Selection != "N" && Selection != "n") {
        pController->ListFaceInfo(pController->CurrentModelIndex, InfoList);
        cout << "----------EDIT FACE POINT----------" << endl;
        // 如果没有选择当前模型，提示用户先选择当前模型
        if (pController->CurrentModelIndex == numeric_limits<size_t>::max()) {
            cout << "No model has been selected as current model, "
                << "please select a model first!" << endl;
            return "";
        }
        cout << "Model[" << pController->CurrentModelIndex
            << "] is the current model" << endl;
        // 如果当前模型中不存在面，提示用户先添加面
        if (InfoList.size() == 0) {
            cout << "No face can be edited, please add a face first!" << endl;
            return "";
        }
        cout << "Please input the edited face index: (0-" 
            << InfoList.size() - 1 << "): ";
        size_t Index;
        cin >> Index;
        // 若用户输入的面的索引超出范围，提示用户
        if (Index > InfoList.size() - 1) {
            cout << "Face index out of range" << endl;
            continue;
        }
        // 显示选择的面的三个点的坐标
        cout << "The points in Face[" << Index << "] are: " << endl;
        for (size_t i = 0; i < 3; i++) {
            cout << "Point[" << i << "]: " << "(" 
                << InfoList[Index].Points[i].x << ", " 
                << InfoList[Index].Points[i].y << ", "
                << InfoList[Index].Points[i].z << ")" << endl;
        }
        // 让用户输入要编辑的点的索引
        cout << "Please input the edited point index: ";
        size_t PointIndex;
        cin >> PointIndex;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // 若用户输入的点的索引超出范围，提示用户
        if (PointIndex > 2) {
            cout << "Point index out of range" << endl;
            continue;
        }
        double X;
        double Y;
        double Z;
        cout << "The new point is: " << endl;
        cout << "X: ";
        cin >> X;
        cout << "Y: ";
        cin >> Y;
        cout << "Z: ";
        cin >> Z;
        Res res = pController->ChangeFacePoint(Index, PointIndex, X, Y, Z);
        // 如果编辑面点失败，提示用户
        if (res != Res::OK) {
            cout << pController->ControllerResStr(res) << endl;
        } 
        else {
            cout << "Face point edited successfully!" << endl;
        }
        Selection.clear();
        while (Selection != "Y" && Selection != "y"
            && Selection != "N" && Selection != "n") {
            cout << "Do you want to edit another face point? (Y/N): ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, Selection);
            if (Selection == "N" || Selection == "n") {
                cout << "----------BACK TO MAIN MENU----------" << endl;
            }
        }
    }
    return "";
}
/*************************************************************************
【函数名称】EditLinePointMenu
【函数功能】显示编辑线点菜单
【参数】无
【返回值】string
【开发者及日期】谭雯心 2024/8/10
【更改记录】2024/8/11 谭雯心 修改了当模型中不存在线时的提示
*************************************************************************/
string Viewer::EditLinePointMenu() {
    // 获取Controller类的唯一实例
    shared_ptr<Controller> pController = Controller::GetInstance();
    string Selection;
    // 创建线信息列表，用于存储线信息
    Controller::LineInfoList InfoList;
    
    // 当用户选择继续编辑线点时，循环显示编辑线点菜单
    while (Selection != "N" && Selection != "n") {
        // 获取当前模型的线信息
        pController->ListLineInfo(pController->CurrentModelIndex, InfoList);
        cout << "----------EDIT LINE POINT----------" << endl;
        if (pController->CurrentModelIndex == numeric_limits<size_t>::max()) {
            cout << "No model has been selected as current model, "
                << "please select a model first!" << endl;
            return "";
        }
        cout << "Model[" << pController->CurrentModelIndex
            << "] is the current model" << endl;
        // 如果当前模型中不存在线，提示用户先添加线
        if (InfoList.size() == 0) {
            cout << "No line can be edited, please add a line first!" << endl;
            return "";
        }
        cout << "Please input the edited line index: (0-" 
            << InfoList.size() - 1 << "): ";
        size_t Index;
        cin >> Index;
        // 若用户输入的线的索引超出范围，提示用户
        if (Index > InfoList.size() - 1) {
            cout << "Line index out of range" << endl;
            continue;
        }
        // 显示选择的线的两个点的坐标
        cout << "The points in Line[" << Index << "] are: " << endl;
        for (size_t i = 0; i < 2; i++) {
            cout << "Point[" << i << "]: " << "(" 
                << InfoList[Index].Points[i].x << ", " 
                << InfoList[Index].Points[i].y << ", "
                << InfoList[Index].Points[i].z << ")" << endl;
        }
        cout << "Please input the edited point index: ";
        size_t PointIndex;
        cin >> PointIndex;
        // 清空输入缓冲区
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // 若用户输入的点的索引超出范围，提示用户
        if (PointIndex > 1) {
            cout << "Point index out of range" << endl;
            continue;
        }
        double X;
        double Y;
        double Z;
        cout << "The new point is: " << endl;
        cout << "X: ";
        cin >> X;
        cout << "Y: ";
        cin >> Y;
        cout << "Z: ";
        cin >> Z;
        Res res = pController->ChangeLinePoint(Index, PointIndex, X, Y, Z);
        // 如果编辑线点失败，提示用户
        if (res != Res::OK) {
            cout << pController->ControllerResStr(res) << endl;
        } 
        else {
            cout << "Line point edited successfully!" << endl;
        }
        Selection.clear();
        while (Selection != "Y" && Selection != "y"
            && Selection != "N" && Selection != "n") {
            cout << "Do you want to edit another line point? (Y/N): ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, Selection);
            if (Selection == "N" || Selection == "n") {
                cout << "----------BACK TO MAIN MENU----------" << endl;
            }
        }
    }
    return "";
}
/*************************************************************************
【函数名称】ListModelInfoMenu
【函数功能】显示列出模型信息菜单
【参数】无
【返回值】string
【开发者及日期】谭雯心 2024/8/10
【更改记录】
*************************************************************************/
string Viewer::ListModelInfoMenu() {
    // 获取Controller类的唯一实例
    shared_ptr<Controller> pController = Controller::GetInstance();
    string Selection;
    // 当用户选择不回到主菜单时，循环显示列出模型信息菜单
    while (Selection != "Y" && Selection != "y") {
        cout << "----------LIST MODEL INFORMATION----------" << endl;
        // 如果用户没有选择当前模型，提示用户先选择当前模型
        if (pController->CurrentModelIndex == numeric_limits<size_t>::max()) {
            cout << "No model has been selected as current model, "
                << "please select a model first!" << endl;
            return "";
        }
        // 创建Info，用于存储模型信息
        Controller::ModelInfo Info;
        // 获取模型信息
        Res res = pController->ListModelInfo(Info);
        // 如果获取模型信息失败，提示用户
        if (res != Res::OK) {
            cout << pController->ControllerResStr(res) << endl;
        } 
        else {
            // 显示模型信息
            cout << "Model[" 
                << pController->CurrentModelIndex << "]: " << endl;
            cout << "Name: " << Info.Name << endl;
            cout << "Element Count: " << Info.ElementCount << endl;
            cout << "Face Count: " << Info.FaceCount << endl;
            cout << "Line Count: " << Info.LineCount << endl;
            cout << "Point Count: " << Info.PointCount << endl;
            cout << "Area: " << Info.Area << endl;
            cout << "Length: " << Info.Length << endl;
            cout << "Bounding Box Volume: " << Info.Volume << endl;
        }
        // 清空Selection
        Selection.clear();
        while (Selection != "Y" && Selection != "y"
            && Selection != "N" && Selection != "n") {
            cout << "Back to main menu? (Y/N): ";
            getline(cin, Selection);
            if (Selection == "Y" || Selection == "y") {
                cout << "----------BACK TO MAIN MENU----------" << endl;
            }
        }
    }
    return "";
}
/*************************************************************************
【函数名称】ListFaceInfoMenu
【函数功能】显示列出面信息菜单
【参数】无
【返回值】string
【开发者及日期】谭雯心 2024/8/10
【更改记录】
*************************************************************************/
string Viewer::ListFaceInfoMenu() {
    // 获取Controller类的唯一实例
    shared_ptr<Controller> pController = Controller::GetInstance();
    string Selection;
    // 当用户选择不回到主菜单时，循环显示列出面信息菜单
    while (Selection != "Y" && Selection != "y") {
        cout << "----------LIST FACE INFORMATION----------" << endl;
        // 如果没有选择当前模型，提示用户先选择当前模型
        if (pController->CurrentModelIndex == numeric_limits<size_t>::max()) {
            cout << "No model has been selected as current model, "
                << "please select a model first!" << endl;
            return "";
        }
        // 创建InfoList，用于存储面信息
        Controller::FaceInfoList InfoList;
        // 获取面信息
        Res res = pController->ListFaceInfo(InfoList);
        // 如果获取面信息失败，提示用户
        if (res != Res::OK) {
            cout << pController->ControllerResStr(res) << endl;
        } 
        else {
            cout << "There are " << InfoList.size() << " faces in model["
                << pController->CurrentModelIndex << "]: " << endl;
            // 显示面中的Point3D信息
            for (size_t i = 0; i < InfoList.size(); i++) {
                cout << "Face[" << i << "]: " << endl;
                cout << "Point 0: ("
                    << InfoList[i].Points[0].x << ", " 
                    << InfoList[i].Points[0].y << ", "
                    << InfoList[i].Points[0].z << ")" << endl;
                cout << "Point 1: ("
                    << InfoList[i].Points[1].x << ", " 
                    << InfoList[i].Points[1].y << ", "
                    << InfoList[i].Points[1].z << ")" << endl;
                cout << "Point 2: ("
                    << InfoList[i].Points[2].x << ", " 
                    << InfoList[i].Points[2].y << ", "
                    << InfoList[i].Points[2].z << ")" << endl;
                cout << "Area: " << InfoList[i].Area << endl;
            }
        }
        Selection.clear();
        while (Selection != "Y" && Selection != "y"
            && Selection != "N" && Selection != "n") {
            cout << "Back to main menu? (Y/N): ";
            getline(cin, Selection);
            if (Selection == "Y" || Selection == "y") {
                cout << "----------BACK TO MAIN MENU----------" << endl;
            }
        }
    }
    return "";
}
/*************************************************************************
【函数名称】ListLineInfoMenu
【函数功能】显示列出线信息菜单
【参数】无
【返回值】string
【开发者及日期】谭雯心 2024/8/10
【更改记录】
*************************************************************************/
string Viewer::ListLineInfoMenu() {
    // 获取Controller类的唯一实例
    shared_ptr<Controller> pController = Controller::GetInstance();
    string Selection;
    // 当用户选择不回到主菜单时，循环显示列出线信息菜单
    while (Selection != "Y" && Selection != "y") {
        cout << "----------LIST LINE INFORMATION----------" << endl;
        // 如果没有选择当前模型，提示用户先选择当前模型
        if (pController->CurrentModelIndex == numeric_limits<size_t>::max()) {
            cout << "No model has been selected as current model, "
                << "please select a model first!" << endl;
            return "";
        }
        // 创建InfoList，用于存储线信息
        Controller::LineInfoList InfoList;
        // 获取线信息
        Res res = pController->ListLineInfo(InfoList);
        // 如果获取线信息失败，提示用户
        if (res != Res::OK) {
            cout << pController->ControllerResStr(res) << endl;
        } 
        else {
            // 显示线中的Point3D信息
            cout << "There are " << InfoList.size() << " lines in model["
                << pController->CurrentModelIndex << "]: " << endl;
            for (size_t i = 0; i < InfoList.size(); i++) {
                cout << "Line[" << i << "]: " << endl;
                cout << "Point 0: ("
                    << InfoList[i].Points[0].x << ", " 
                    << InfoList[i].Points[0].y << ", "
                    << InfoList[i].Points[0].z << ")" << endl;
                cout << "Point 1: ("
                    << InfoList[i].Points[1].x << ", " 
                    << InfoList[i].Points[1].y << ", "
                    << InfoList[i].Points[1].z << ")" << endl;
                cout << "Length: " << InfoList[i].Length << endl;
            }
        }
        Selection.clear();
        while (Selection != "Y" && Selection != "y"
            && Selection != "N" && Selection != "n") {
            cout << "Back to main menu? (Y/N): ";
            getline(cin, Selection);
            if (Selection == "Y" || Selection == "y") {
                cout << "----------BACK TO MAIN MENU----------" << endl;
            }
        }
    }
    return "";
}

/*************************************************************************
【函数名称】EditModelNameMenu
【函数功能】显示编辑模型名称菜单
【参数】无
【返回值】string
【开发者及日期】谭雯心 2024/8/14
【更改记录】
*************************************************************************/
string Viewer::EditModelNameMenu() {
    // 获取Controller类的唯一实例
    shared_ptr<Controller> pController = Controller::GetInstance();
    string Selection;
    // 当用户选择不回到主菜单时，循环显示编辑模型名称菜单
    while (Selection != "Y" && Selection != "y") {
        cout << "----------EDIT MODEL NAME----------" << endl;
        // 如果没有选择当前模型，提示用户先选择当前模型
        if (pController->CurrentModelIndex == numeric_limits<size_t>::max()) {
            cout << "No model has been selected as current model, "
                << "please select a model first!" << endl;
            return "";
        }
        cout << "Model[" << pController->CurrentModelIndex
            << "] is the current model" << endl;
        cout << "Please input the new model name: ";
        string Name;
        getline(cin, Name);
        Res res = pController->ChangeName(Name);
        // 如果编辑模型名称失败，提示用户
        if (res != Res::OK) {
            cout << pController->ControllerResStr(res) << endl;
        } 
        else {
            cout << "Model name edited successfully!" << endl;
        }
        Selection.clear();
        while (Selection != "Y" && Selection != "y" 
            && Selection != "N" && Selection != "n") {
            cout << "Back to Edit Model Menu? (Y/N): ";
            getline(cin, Selection);
            if (Selection == "Y" || Selection == "y") {
                cout << "----------BACK TO MAIN MENU----------" << endl;
            }
        }
    }
    return "";
}
/*************************************************************************
【函数名称】EditModelDescriptionMenu
【函数功能】显示编辑模型描述菜单
【参数】无
【返回值】string
【开发者及日期】谭雯心 2024/8/14
【更改记录】
*************************************************************************/
string Viewer::EditModelDescriptionMenu() {
    // 获取Controller类的唯一实例
    shared_ptr<Controller> pController = Controller::GetInstance();
    string Selection;
    // 当用户选择不回到主菜单时，循环显示编辑模型描述菜单
    while (Selection != "Y" && Selection != "y") {
        cout << "----------EDIT MODEL DESCRIPTION----------" << endl;
        // 如果没有选择当前模型，提示用户先选择当前模型
        if (pController->CurrentModelIndex == numeric_limits<size_t>::max()) {
            cout << "No model has been selected as current model, "
                << "please select a model first!" << endl;
            return "";
        }
        cout << "Model[" << pController->CurrentModelIndex
            << "] is the current model" << endl;
        cout << "Please input the new model description: ";
        string Description;
        getline(cin, Description);
        Res res = pController->ChangeDescription(Description);
        // 如果编辑模型描述失败，提示用户
        if (res != Res::OK) {
            cout << pController->ControllerResStr(res) << endl;
        } 
        else {
            cout << "Model description edited successfully!" << endl;
        }
        Selection.clear();
        while (Selection != "Y" && Selection != "y" 
            && Selection != "N" && Selection != "n") {
            cout << "Back to Edit Model Menu? (Y/N): ";
            getline(cin, Selection);
            if (Selection == "Y" || Selection == "y") {
                cout << "----------BACK TO MAIN MENU----------" << endl;
            }
        }
    }
    return "";
}
