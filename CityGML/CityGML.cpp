
#include <iostream>
#include <fstream>
#include <string>
#include "CityGML.h"
#include <vector>
#include <direct.h>


using namespace std;

int main() {

    string filePath = "./";
    vector<string> fileList = getFileList(filePath);
    if (fileList.empty()) {
        cout << "GML files not found." << "\n" << "Hit any Key." << endl;
        cin.get();
        return 0;
    }

    for (auto& inFileName : fileList) {

        cout << inFileName << endl;
        
        const int n = 8;
        string target[n] = {// Old URLs
            "http://www.kantei.go.jp/jp/singi/tiiki/toshisaisei/itoshisaisei/iur/uro/1.4",
            "http://www.kantei.go.jp/jp/singi/tiiki/toshisaisei/itoshisaisei/iur/urf/1.4",
            "http://www.kantei.go.jp/jp/singi/tiiki/toshisaisei/itoshisaisei/iur/urg/1.4",
            "http://www.kantei.go.jp/jp/singi/tiiki/toshisaisei/itoshisaisei/iur/urt/1.4",
            "http://www.kantei.go.jp/jp/singi/tiiki/toshisaisei/itoshisaisei/iur/schemas/uro/1.4/urbanObject.xsd",
            "http://www.kantei.go.jp/jp/singi/tiiki/toshisaisei/itoshisaisei/iur/schemas/urf/1.4/urbanFunction.xsd",
            "http://www.kantei.go.jp/jp/singi/tiiki/toshisaisei/itoshisaisei/iur/schemas/urg/1.4/statisticalGrid.xsd",
            "http://www.kantei.go.jp/jp/singi/tiiki/toshisaisei/itoshisaisei/iur/schemas/urt/1.4/publicTransit.xsd",
        };
        string order[n] = { // New URLs
            "https://www.chisou.go.jp/tiiki/toshisaisei/itoshisaisei/iur/uro/1.5",
            "https://www.chisou.go.jp/tiiki/toshisaisei/itoshisaisei/iur/urf/1.5",
            "https://www.chisou.go.jp/tiiki/toshisaisei/itoshisaisei/iur/urg/1.5",
            "https://www.chisou.go.jp/tiiki/toshisaisei/itoshisaisei/iur/urt/1.5",
            "https://www.chisou.go.jp/tiiki/toshisaisei/itoshisaisei/iur/schemas/uro/1.5/urbanObject.xsd",
            "https://www.chisou.go.jp/tiiki/toshisaisei/itoshisaisei/iur/schemas/urf/1.5/urbanFunction.xsd",
            "https://www.chisou.go.jp/tiiki/toshisaisei/itoshisaisei/iur/schemas/urg/1.5/statisticalGrid.xsd",
            "https://www.chisou.go.jp/tiiki/toshisaisei/itoshisaisei/iur/schemas/urt/1.5/publicTransit.xsd",
        };

        //input
        ifstream ifs(inFileName);
      
        //output
        const char *outPath = "./output/";
        if (_mkdir(outPath) == 0)
                printf("Make directory %s \n", outPath);
        ofstream ofs(outPath + getFileName(inFileName));
        
        //initialize
        string data = {};
        string buf = {};

        //replace
        while (!ifs.eof()) {
            getline(ifs, buf);
            buf = replaceStr(buf, target, order, n);
            data += buf + "\n";
        }
        //cout << data << endl;

        //write, close files 
        ifs.close();
        ofs << data;
        ofs.close();
    }
    return 0;
}