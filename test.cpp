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
    void **ss = new void *[5];
    ss[0] = malloc(s.length() + 1);
    ss[1] = malloc(sizeof(long long));
    memcpy(ss[0], s, s.length() + 1);
    memcpy(ss[1], &f, sizeof(long long));
    s = "";
    void *t = ss[1];
    char *tmps = (char *) t;
    char tmp;
    for (int i = 0; i < sizeof(long long); ++i) {
        tmp = tmps[i];
        s += (double) (tmp);
    }
    cout << s;
    return 0;
}