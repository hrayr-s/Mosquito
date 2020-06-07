//
// Created by Hrayr on 5/31/2020.
//

#ifndef DATABASE_ARRAYHELPER_H
#define DATABASE_ARRAYHELPER_H

#include "types/String.h"
#include "types/structures.h"

class ArrayHelper {
public:
    static bool resize(String *&f, long long size = 1);

    static bool resize(struct column *columns, long long size = 1);

    static bool resize(long long *&f, long long size = 1) {
        if (size < 1) {
            throw "size should be more than 0";
        }

        long long *tmp;
        long long tmp_size = 0;
        for (; f[tmp_size] != NULL; ++tmp_size) {}
        tmp = new long long[size + 1];
        for (long long i = 0; i < size; ++i) {
            tmp[i] = f[i];
        }
        tmp[size + 1] = NULL;
        delete[] f;
        f = new long long[size + 1];
        for (long long i = 0; i <= size; ++i) {
            f[i] = tmp[i];
        }
        return true;
    }
};


#endif //DATABASE_ARRAYHELPER_H
