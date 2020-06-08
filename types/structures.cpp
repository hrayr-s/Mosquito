//
// Created by Hrayr on 6/8/2020.
//

#include "structures.h"

struct column column::operator=(nullptr_t s) {
    name = nullptr;
    type = NULL;
    size = NULL;
    return *this;
}

bool column::operator==(nullptr_t s) {
    return this->name == nullptr;
}

bool column::operator!=(nullptr_t s) {
    return this->name != nullptr;
}