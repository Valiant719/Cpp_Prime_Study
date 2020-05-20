#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    string out;
    for (int i = 0; i != argc; ++i){
        out += " ";
        out += argv[i];
    };
    cout << out << endl;
}