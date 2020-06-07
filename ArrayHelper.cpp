//
// Created by Hrayr on 5/31/2020.
//
#include "types/String.h"
#include "ArrayHelper.h"

static bool ArrayHelper::resize(String *&f, long long size = 1) {
    if (size < 1) {
        throw "size should be more than 0";
    }

    String *tmp;
    long long tmp_size = 0;
    for (; f[tmp_size] != nullptr; ++tmp_size) {}
    tmp = new String[tmp_size + size + 1];
    for (long long i = 0; i < tmp_size; ++i) {
        tmp[i] = f[i];
    }
    for (long long i = 0; i <= size; ++i) {
        tmp[tmp_size + i] = nullptr;
    }
    delete[] f;
    f = new String[tmp_size + size + 1];
    for (long long i = 0; i <= tmp_size + size; ++i) {
        f[i] = tmp[i];
    }
    return true;
}

bool ArrayHelper::resize(struct column *f, long long int size) {
    if (size < 1) {
        throw "size should be more than 0";
    }

    struct column *tmp;
    long long tmp_size = 0;
    for (; f[tmp_size] != nullptr; ++tmp_size) {}
    tmp = new column[tmp_size + size + 1];
    for (long long i = 0; i < tmp_size; ++i) {
        tmp[i] = f[i];
    }
    for (long long i = 0; i <= size; ++i) {
        tmp[tmp_size + i] = nullptr;
    }
    delete[] f;
    f = new column[tmp_size + size + 1];
    for (long long i = 0; i <= tmp_size + size; ++i) {
        f[i] = tmp[i];
    }
    return true;
}
