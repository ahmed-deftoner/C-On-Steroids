#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char *argv[]){
    fstream file;
    string line;
    file.open(argv[1], ios::in);
    if (file.is_open()) {
        while ( getline (file, line) ) {
             cout << line << '\n';
        }
        file.close();
    }
    cout <<"hello\n";
    return 0;
}