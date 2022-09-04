#include <string>

using namespace std;

string replaceStr(string line, string *target, string *order, int n) {

    int i;
    for (i = 0; i < n; i++) {
        string::size_type pos = 0;
        while ((pos = line.find(target[i], pos)) != string::npos) {
            line.replace(pos, target[i].length(), order[i]);
            pos += order[i].length();
        }
    }
    return line;
}
