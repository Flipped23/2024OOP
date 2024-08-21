#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, const char * argv[]) {
    string FileName = "D:\\twx\\OOP\\Final_Assignment\\cube.obj";
    //try to open file
    ifstream File(FileName);
    //can't open
    if (!File.is_open()) {
        throw string("Can't open/create for loading, file: " + FileName);
    }
    //for '#','g','v','l','f'
    char Tag;
    char Temp;
    string Comment;
    string Name;
    double xVal{0};
    double yVal{0};
    double zVal{0};
    unsigned int Index1{0};
    unsigned int Index2{0};
    unsigned int Index3{0};
    while(!File.eof()){
        File >> Tag;
        //drop space
        File.get();
        switch (Tag) {
            case '#':
                getline(File, Comment);
                cout << Comment << endl;
                break;
            case 'g':
                getline(File, Name);
                cout << Name << endl;
                break;
            case 'v':
                File >> xVal >> yVal >> zVal;
                cout << xVal << ' ' << yVal << ' ' << zVal << endl;
                //drop enter
                File.get();
                break;
            case 'l':
                File >> Index1 >> Index2;
                cout << Index1 << ' ' << Index2 << endl;
                //drop enter
                File.get();
                break;
            case 'f':
                File >> Index1 >> Index2 >> Index3;
                cout << Index1 << ' ' << Index2 << ' ' << Index3 << endl;
                //drop enter
                File.get();
        }
    }
    return 0;
}
