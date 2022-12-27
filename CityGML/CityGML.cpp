
#include <iostream>
#include <fstream>
#include <string>
#include "CityGML.h"
#include <vector>
#include <direct.h>
#include <jni.h>


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

    // JVMオプション
    JNIEnv* env;
    JavaVM* jvm;
    JavaVMOption options[1];
    options[0].optionString = const_cast < char*> ("-Djava.class.path=./lib/citygml-tools-2.0.0-rc.1.jar");
    JavaVMInitArgs vm_args;
    vm_args.version = JNI_VERSION_1_8;
    vm_args.options = options;
    vm_args.nOptions = 1;

    // JVMの初期化、起動
    int res = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
    if (res) {
        cout << "Can't create JavaVM \n" << res << endl;
        return 1;
        }


    // クラス検索
    jclass cls = env->FindClass("%APP_HOME%\lib\citygml-tools-2.0.0-rc.1.jar");
    if (cls == 0) {
        cout << "Can't find class" << endl;
        return 1;
    }

    // クラス情報をインスタンス化するために<init>メソッドのメソッドIDを取得
    jmethodID cns = env->GetMethodID(cls, "<init>", "()V");
    if (cns == NULL) {
        cout << "Can't get <init> method." << endl;
        return 1;
    }
    jobject obj = env->NewObject(cls, cns);





    //JavaVMの終了
    res = jvm->DestroyJavaVM();
    if (res) {
        cout << "Can't destroy JavaVM \n" << res << endl;
    }


    return 0;
}