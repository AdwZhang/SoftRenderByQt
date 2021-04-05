#ifndef OBJMODEL_H
#define OBJMODEL_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;
class ObjModel
{
public:
    ObjModel(string file){
        cout << "Loading Model:" << file << endl;
        ifstream myfile("G:\\C++ project\\Read\\hello.txt");
//        ofstream outfile("G:\\C++ project\\Read\\out.txt", ios::app);
        string temp;
        if (!myfile.is_open())
        {
            cout << "未成功打开文件" << endl;
        }
        while(getline(myfile,temp))
        {
            for(int i = 0;i < temp.size(); i++){
            }
        }
        myfile.close();
        outfile.close();

    }

private:
    Vertex v;
    //Faces *face;
};

#endif // OBJMODEL_H
