//
// Created by Hrayr on 6/1/2020.
//

#ifndef DATABASE_STRUCTURES_H
#define DATABASE_STRUCTURES_H

class String;

#include <cstddef>

struct column {
    String *name;
    int type;
    long long size;

    struct column operator=(nullptr_t s);

    bool operator==(nullptr_t s);

    bool operator!=(nullptr_t s);

};

#endif //DATABASE_STRUCTURES_H
