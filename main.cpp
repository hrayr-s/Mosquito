#include <iostream>
#include "FileManager.h"

using namespace std;

int main() {
    FileManager f("cmake_install.cmake");
    cout << f.read() << endl;
    return 0;
}
