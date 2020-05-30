#include <iostream>
#include "FileManager.h"
#include "types/String.h"

using namespace std;

int main() {
    FileManager f("a.txt", "w");
    String s;
    cout << "Input your multiline text" << endl;
    cin >> s;
    try {
        f.write(s);
        cout << endl;
        cout << "Successfully wrote the content!" << endl;
        cout << "Exiting..." << endl;
    } catch (const char* msg) {
        cout << msg << endl;
    }
    return 0;
}
