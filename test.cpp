//
// Created by Hrayr on 6/11/2020.
//

#include <iostream>

using namespace std;

int main() {
    FILE *f;
    f = fopen("hell.txt", "w");
    fwrite("Hell Yeah", sizeof("Hell Yeah"), 1, f);
    fflush(f);
    fclose(f);
    return 0;
}