#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector>
using namespace std;

int main(int argc, char *argv[]){
    if(argc != 2){
        cout << "Not enough arguments \n";
        return 1;
    }
    fstream file;
    string fileName = argv[1];
    vector<string> lines;
    string line;
    int pos = fileName.find(".");
    string sub = fileName.substr(pos + 1);
    if(sub != "cos"){
        cout << "File must be .cos extension!\n";
        return 2;
    }
    file.open(argv[1], ios::in);
    if (file.is_open()) {
        while ( getline (file, line) ) {
             lines.push_back(line);
        }
        file.close();
    }
    for(auto it = lines.begin(); it != lines.end(); it++){
        cout<<*it<<endl;
    }
    return 0;
}