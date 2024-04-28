#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
using namespace std;
void listFiles(string dir) {
    DIR *dp;
    struct dirent *ep;
    dp = opendir(dir.c_str());
    if (dp!= NULL) {
        while ((ep = readdir(dp))!= NULL) {
            string filename = ep->d_name;
            struct stat st;
            stat((dir + "/" + filename).c_str(), &st);
            if (S_ISDIR(st.st_mode)) {
                cout << filename << "/" << endl;
            } else {
                cout << filename << endl;
            }
        }
        closedir(dp);
    } else {
        perror("Couldn't open the directory");
    }
}

void createDir(string dir) {
    string command = "md" + dir;
    system(command.c_str());
}
void copyFile(string src, string dest) {
    ifstream srcFile(src, ios::binary);
    ofstream destFile(dest, ios::binary);
    destFile << srcFile.rdbuf();
    srcFile.close();
    destFile.close();
}
void moveFile(string src, string dest) {
    copyFile(src, dest);
    string command = "rm " + src;
    system(command.c_str());
}

int main() {
    string currentDir = ".";
    while (true) {
        cout << "Current directory: " << currentDir << endl;
        cout << "Enter command (ls, mkdir, cp, mv, cd, exit): ";
        string command;
        cin >> command;
        if (command == "ls") {
            listFiles(currentDir);
        }
        else if (command == "mkdir") {
            cout << "Enter directory name: ";
            string dirName;
            cin >> dirName;
            createDir(currentDir + "/" + dirName);
        }
        else if (command == "cp") {
            cout << "Enter source file: ";
            string srcFile;
            cin >> srcFile;
            cout << "Enter destination file: ";
            string destFile;
            cin >> destFile;
            copyFile(currentDir + "/" + srcFile, currentDir + "/" + destFile);
        }
        else if (command == "mv") {
            cout << "Enter source file: ";
            string srcFile;
            cin >> srcFile;
            cout << "Enter destination file: ";
            string destFile;
            cin >> destFile;
            moveFile(currentDir + "/" + srcFile, currentDir + "/" + destFile);
        } 
        else if (command == "cd") {
            cout << "Enter directory: ";
            string dir;
            cin >> dir;
            currentDir += "/" + dir;
        }
        else if (command == "exit") {
            break;
        }
        else {
            cout << "Invalid command" << endl;
        }
    }
    return 0;
};
