
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include "CityGML.h"

using namespace std;
namespace fs = std::filesystem;

vector<string> getFileList(string filePath)
{
    vector<string> fileList;
    string ext = ".gml";
    for (const fs::directory_entry& x : fs::recursive_directory_iterator(filePath)) {
        if (x.path().extension() == ext)
            //cout << x.path() << endl;
            fileList.push_back(x.path().string());
    }
    return fileList;
}


string getFileName(const string path)
{
    size_t pos1;
    pos1 = path.rfind('\\');
    if (pos1 != string::npos) {
        return path.substr(pos1 + 1, path.size() - pos1 - 1);
    }
    pos1 = path.rfind('/');
    if (pos1 != string::npos) {
        return path.substr(pos1 + 1, path.size() - pos1 - 1);
    }
    return path;
}
