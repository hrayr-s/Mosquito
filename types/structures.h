//
// Created by Hrayr on 6/1/2020.
//

#ifndef DATABASE_STRUCTURES_H
#define DATABASE_STRUCTURES_H


struct column {
    String *name;
    int type;
    long long size;

    struct column operator=(nullptr_t s) {
        name = nullptr;
        type = NULL;
        size = NULL;
        return *this;
    }

    bool operator==(nullptr_t s) {
        return this->name == nullptr;
    }

};

#endif //DATABASE_STRUCTURES_H
