//
// Created by Hrayr on 6/1/2020.
//

#ifndef DATABASE_STRUCTURES_H
#define DATABASE_STRUCTURES_H

#include "String.h"
#include "../command/Parser.h"

struct column {
public:
    String *name;
    int type;
    long long size;

    column() {

    }

    ~column() {

    }

    struct column operator=(nullptr_t s) {
        name = nullptr;
        type = NULL;
        size = NULL;
        return *this;
    }

    bool operator==(nullptr_t s) {
        return this->name == nullptr;
    }

    bool operator!=(nullptr_t s) {
        return this->name != nullptr;
    }

    struct column operator=(String &col) {
        this->name = new String(Parser::getColumnName(col));
        this->type = Parser::getType(col);

    }

};

#endif //DATABASE_STRUCTURES_H
