//
// Created by Hrayr on 6/8/2020.
//

#include "String.h"
#include "structures.h"
#include "../ArrayHelper.h"
#include "../command/Parser.h"
#include <iostream>
#define ll_SIZE sizeof(long long)

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

table::table(String name, char *raw) {
    this->name = new String(name);
    char col_count = raw[0];
    this->columns = new column[col_count + 1];
    this->cols_count = col_count;
    this->data = nullptr;

    // Remember {col_count}^1 + {raw_structure_size}^8 +
    // {shift in/begin 0x0D '\15'}^1

    long long raw_structure_size = 0;
    memcpy(&raw_structure_size, raw + 1, ll_SIZE);
    long long byte_pos = 1 + ll_SIZE;
    char tmp_col_type = -1;
    long long tmp_col_size = 0;
    char *tmp_col_name;
    long long tmp_col_name_length = 0;
    String tmp_raw_col;
    String *raw_columns = new String[col_count];

    for (char i = 0; i < col_count; ++i) {
        // Check begin of raw structure | First byte is 0x0D
        if (raw[byte_pos++] != '\15') {
            throw "Structure file of a table " + name + " is corrupted!";
        }
        // Second byte is column type
        tmp_col_type = raw[byte_pos++];
        // From third to 10th is long long type of number - Column size
        memcpy(&tmp_col_size, raw + byte_pos, ll_SIZE);
        byte_pos += ll_SIZE;

        // Calculate column name string length
        tmp_col_name_length = 0;
        for (long long j = byte_pos; raw[j] != '\0'; ++j) {
            ++tmp_col_name_length;
        }
        // Column name including ``: so size becomes length  length("``") + length('\0')
        // `{col_name}` {type}({size})
        tmp_col_name = new char[tmp_col_name_length + 2 + String::size(Parser::getColumnTypeName(tmp_col_type)) +
                                (tmp_col_type == TYPE_VARCHAR ? String::parse(tmp_col_size).length() + 2 : 0) + 1];
        tmp_col_name[0] = '`';
        memcpy(tmp_col_name + 1, raw + byte_pos, tmp_col_name_length);
        tmp_col_name[tmp_col_name_length + 1] = '`';
        tmp_col_name[tmp_col_name_length + 2] = ' ';
        tmp_col_name[tmp_col_name_length + 3] = '\0';
        tmp_raw_col = String::concat(tmp_col_name, Parser::getColumnTypeName(tmp_col_type));
        if (tmp_col_type == TYPE_VARCHAR) {
            tmp_raw_col += "(";
            tmp_raw_col += String::parse(tmp_col_size);
            tmp_raw_col += ")";
        }

        byte_pos += tmp_col_name_length + 1;

        // Check end of raw structure | Last byte is 0x0C
        if (raw[byte_pos] != '\14') {
            throw "Structure file of a table " + name + " is corrupted!";
        }
        raw_columns[i] = new String(tmp_raw_col);
        this->columns[i] = new column(tmp_raw_col);
        byte_pos++;
    }
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