//
// Created by Hrayr on 6/11/2020.
//

#include <iostream>
#include "types/String.h"

using namespace std;

int main() {
    String s;
    double f = 0;
    cout << "Input number: ";
    cin >> f;
    cout << "Input text: ";
    cin >> s;
    cout << endl;
    cout << s + f;
    return 0;
}