//
// Created by Hrayr on 6/8/2020.
//

#include "String.h"
#include "structures.h"
#include "../ArrayHelper.h"
#include "../command/Parser.h"
#include <iostream>

using namespace std;

/** BEGIN COLUMN STRUCTURE */
column::column() {
    this->name = nullptr;
    this->size = NULL;
    this->type = NULL;
}

column::column(String raw_col) {
    this->name = new String(Parser::getColumnName(raw_col));
    this->type = Parser::getColumnType(raw_col);
    if (this->type == TYPE_INT) {
        this->size = 8;
    } else if (this->type == TYPE_TEXT) {
        this->size = NULL;
    } else if (this->type == TYPE_VARCHAR) {
        this->size = Parser::getColumnSize(raw_col);
    } else {
        throw "Unknown column type";
    }
    cout << Parser::getColumnTypeName(this->type) << *this->name << " has size " << this->size << endl;
}

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

column::column(column *pColumn) {
    this->name = pColumn->name;
    this->type = pColumn->type;
    this->size = pColumn->size;
}

/** END COLUMN STRUCTURE */

/** BEGIN TABLE STRUCTURE */
table::table() {
    this->name = nullptr;
    this->columns = nullptr;
    this->cols_count = NULL;
    this->data = nullptr;
}

table::table(String name, String *raw) {
    char size;
    size = ArrayHelper::count(raw);
    this->columns = new column[size + 1];
    for (long long i = 0; i < size; ++i) {
        this->columns[i] = new column(raw[i]);
    }
    this->cols_count = size;
    this->name = new String(name);
    this->data = nullptr;
}

struct table table::operator=(nullptr_t s) {
    this->name = nullptr;
    this->columns = nullptr;
    this->cols_count = NULL;
    this->data = nullptr;
    return *this;
}

bool table::operator==(nullptr_t s) const {
    return this->name == nullptr;
}

bool table::operator!=(nullptr_t s) const {
    return this->name != nullptr;
}
/** END TABLE STRUCTURE */