#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

bool remarks(const string& path, const string& remark) {
    string iniFilePath = path + "\\desktop.ini";

    SetFileAttributesA(iniFilePath.c_str(), FILE_ATTRIBUTE_NORMAL);

    ifstream iniFileIn(iniFilePath);
    string content;
    bool shellClassInfoFound = false;
    bool infoTipFound = false;

    if (iniFileIn.is_open()) {
        string line;
        while (getline(iniFileIn, line)) {
            if (line == "[.ShellClassInfo]") {
                shellClassInfoFound = true;
            }
            if (shellClassInfoFound && line.find("InfoTip=") == 0) {
                line = "InfoTip=" + remark;
                infoTipFound = true;
            }
            content += line + "\n";
        }
        iniFileIn.close();
    } else {
        // 如果文件不存在，初始化content
        content = "[.ShellClassInfo]\n";
        content += "InfoTip=" + remark + "\n";
        shellClassInfoFound = true;
        infoTipFound = true;
    }

    // 如果存在.ShellClassInfo节但没有InfoTip键，则追加InfoTip键
    if (shellClassInfoFound && !infoTipFound) {
        content += "InfoTip=" + remark + "\n";
    }

    // 如果没有找到.ShellClassInfo节，则追加该节和InfoTip键
    if (!shellClassInfoFound) {
        content += "[.ShellClassInfo]\n";
        content += "InfoTip=" + remark + "\n";
    }

    // 将内容写回文件
    ofstream iniFileOut(iniFilePath);
    if (!iniFileOut.is_open()) {
        cerr << "无法打开文件进行写入。" << endl;
        return false;
    }
    iniFileOut << content;
    iniFileOut.close();

    // 设置文件和文件夹属性
    SetFileAttributesA(iniFilePath.c_str(), FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM);
    SetFileAttributesA(path.c_str(), FILE_ATTRIBUTE_SYSTEM);

    return true;
}

string toPath(const string& input) {  
    string output;  
    for (char c : input) {  
        if (c == '\\') output += "\\\\";
        else output += c; 
    }  
    return output;  
}  

int main(int argc, char* argv[]) {

    string folderPath;
    string remark;

    if (argc == 1) {
        cout << "请输入要备注的文件夹路径：";
        getline(cin, folderPath);
        folderPath = toPath(folderPath);
    } else if (argc == 2) {
        folderPath = toPath(argv[1]);
    } else {
        return -1;
    }

    cout << "备注：";
    getline(cin, remark);

    if (!remarks(folderPath, remark)) {
        system("pause");
    }

    return 0;
}