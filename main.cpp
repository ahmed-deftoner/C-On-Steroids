#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<string> raw;

static void lex(){
    for (auto item : raw) {
        for (int j = 0; j < item.length(); ++j){
            if(item[j]==' ' || item[j]=='\t')
                continue;
            else if(item[j]=='\n')
                break;
        }
    }
}

int main(int argc, char *argv[]){
    if(argc != 2){
        cout << "Not enough arguments \n";
        return 1;
    }
    fstream file;
    string fileName = argv[1];
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
             raw.push_back(line);
        }
        file.close();
    }
    for(auto it = raw.begin(); it != raw.end(); it++){
        cout<<*it<<endl;
    }
    return 0;
}