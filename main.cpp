#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#define TOKEN_IDENTIFIER "I"
#define TOKEN_NUMBER  "N"
#define TOKEN_VARIABLE "V"
#define TOKEN_FUNCTION "F"
#define TOKEN_INT "n"
#define TOKEN_IF "i"
#define TOKEN_ELSE "e"
#define TOKEN_DO "d"
#define TOKEN_UNTIL "u"
#define TOKEN_THEN "t"
#define TOKEN_READ "r"
#define TOKEN_DISPLAY "d"
#define TOKEN_DISPLAYLINE "D"
#define TOKEN_RETURN "R"
#define TOKEN_EQUAL "="
#define TOKEN_NOTEQUAL "!="
#define TOKEN_LESS "<"
#define TOKEN_LESSEQUAL "<="
#define TOKEN_GREATER ">"
#define TOKEN_GREATEREQUAL ">="
#define TOKEN_COMMA ","
#define TOKEN_COLON ":"
#define TOKEN_SEMICOLON ";"
#define TOKEN_DOLLAR "$"
#define TOKEN_OPENPARANTHESIS "("
#define TOKEN_CLOSEPARANTHESIS ")"
#define TOKEN_PLUS "+"
#define TOKEN_MINUS "-"
#define TOKEN_DIVIDE "/"
#define TOKEN_MULTIPLY "*"
#define TOKEN_MODULUS "%"

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