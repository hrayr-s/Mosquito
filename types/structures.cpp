//
// Created by Hrayr on 6/8/2020.
//

#include "structures.h"
#include "String.h"
#include "../ArrayHelper.h"
#include "../command/Parser.h"
#include <iostream>
#include "../DB.h"
#define ll_SIZE sizeof(long long)

using namespace std;

/** BEGIN COLUMN STRUCTURE */
column::column() {
    this->name = nullptr;
    this->size = NULL;
    this->type = NULL;
    this->data = nullptr;
    this->rows_count = NULL;
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
    this->data = nullptr;
    this->rows_count = 0;
}

struct column column::operator=(String raw_col) {
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
    this->data = nullptr;
    this->rows_count = 0;
    return *this;
}

struct column column::operator=(nullptr_t s) {
    name = nullptr;
    type = NULL;
    size = NULL;
    this->data = nullptr;
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
    this->data = pColumn->data;
    this->rows_count = pColumn->rows_count;
}

bool column::insert(String var) {
    ArrayHelper::resize(this->data, 1);
    long long val;
    char *val_ch;
    switch (this->type) {
        case TYPE_INT:
            val = var.parseToInt();
            this->data[this->rows_count] = new long long;
            memcpy(this->data[this->rows_count++], &val, ll_SIZE);
            break;
        case TYPE_VARCHAR:
            val_ch = new char[this->size + 1];
            memcpy(val_ch, var.getContent(), var.length() + 1);
            for (long long i = var.length(); i <= this->size; ++i) {
                val_ch[i] = '\0';
            }
            this->data[this->rows_count] = new char[this->size + 1];
            memcpy(this->data[this->rows_count], val_ch + 1, var.length() - 2);
            for (long long i = var.length() - 2; i <= this->size; ++i) {
                ((char *) this->data[this->rows_count])[i] = '\0';
            }
            this->rows_count++;
            delete[] val_ch;
            break;
        case TYPE_TEXT:
            this->data[this->rows_count] = new char[var.length()];
            memcpy(this->data[this->rows_count++], var.getContent() + 1, var.length() - 2);
            ((char *) this->data[this->rows_count])[var.length() - 1] = '\0';
            break;
        default:
            return false;
    }
    return true;
}

bool column::remove_last_added() {
    delete[] this->data[--this->rows_count];
    this->data[this->rows_count] = nullptr;
    return false;
}

bool column::checkVar(String var) {
    switch (this->type) {
        case TYPE_INT:
            if (!var.isNumber()) {
                String err("Given Value \"");
                err += var;
                err += "\" size should not be greater than ";
                err += String::parse(this->size);
                err += "!";
                throw err.getContent();
            }
            return true;
        case TYPE_VARCHAR:
            if (this->size < (var.size() - 2)) {
                String err("Given Value ");
                err += var;
                err += " size should not be greater than ";
                err += String::parse(this->size);
                err += "!";
                throw err.getContent();
            }
        case TYPE_TEXT:
            if (var[0] != '\'' || var[var.length() - 1] != '\'') {
                String err("Given Value  is not a VARCHAR VALUE!");
                throw err.getContent();
            }
            return true;
    }
    return true;
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
        this->columns[i] = tmp_raw_col;
        byte_pos++;
    }
}

struct table table::operator=(nullptr_t s) {
    this->name = nullptr;
    this->columns = nullptr;
    this->cols_count = NULL;
    this->data = nullptr;
    this->flushed = NULL;
    return *this;
}

struct table table::operator=(table *tb) {
    this->name = new String;
    *this->name = *tb->name;
    if (this->cols_count != NULL && this->cols_count > 0) {
        delete[] this->columns;
        delete[] this->data;
    }
    this->columns = new column[tb->cols_count];
    for (char i = 0; i < tb->cols_count; ++i) {
        this->columns[i] = new column(
                tb->columns[i]); // This assignment is not copying data from pointer | just creates another pointer
    }
    this->cols_count = tb->cols_count;
    long long data_size = tb->getDataSize();
    if (data_size > 0) {
        this->data = new char[data_size];
        memcpy(this->data, tb->data, data_size);
    } else {
        this->data = new char[1];
        this->data[0] = NULL;
    }
    this->flushed = tb->flushed;
    return *this;
}

bool table::operator==(nullptr_t s) const {
    return this->name == nullptr;
}

bool table::operator!=(nullptr_t s) const {
    return this->name != nullptr;
}

bool table::setTableData(char *raw) {
    if (raw == nullptr || raw[0] == '\0') {
        this->data = new char[1];
        this->data[0] = '\0';
        return true;
    }
    long long size = 0;
    // First 8 bytes contains whole size of a raw data
    // So lets get it
    memcpy(&size, raw, ll_SIZE);
    this->data = new char[size];
    memcpy(this->data, raw, size);
    // And take the 8 bytes so we will get data size
    this->flushed = true;
    return true;
}

bool table::insert(String raw) {
    String *data = raw.split(",");
    char i = 0;
    for (; data[i] != nullptr; ++i) {
        data[i] = data[i].trim();
        this->columns[i].checkVar(data[i]);
    }
    i = 0;
    try {
        for (; data[i] != nullptr; ++i) {
            this->columns[i].insert(data[i]);
        }
        DB::getInstance()->flush(*this->name);
    } catch (char *s) {
        --i;
        for (; i >= 0; --i) {
            columns[i].remove_last_added();
        }
        throw s;
    }
    this->flushed = false;
    return true;
}

char *table::getTableVoidData() {
    delete[] this->data;

    long long data_size = ll_SIZE;

    // First we need to calculate size of a future raw data
    for (long long i = 0; i < this->columns[0].rows_count; ++i) {
        for (char j = 0; j < this->cols_count; ++j) {
            switch (this->columns[j].type) {
                case TYPE_INT:
                    data_size += ll_SIZE;
                    break;
                case TYPE_VARCHAR:
                    data_size += this->columns[j].size;
                    break;
                case TYPE_TEXT:
                    data_size += String((char *) this->columns[j].data[i]).length();
                    break;
            }
            data_size += 1; // Column separator 0x1E
        }
        data_size += 1; // Row separator 0x1D
    }

    this->data = new char[data_size];
    long long posx = 0;
    memcpy(this->data, &data_size, ll_SIZE);
    posx += ll_SIZE;
    // Lets copy all data and construct the raw formatted data for a table data file
    long long tmp_size = 0;
    char *tmp_str;
    for (long long i = 0; i < this->columns[0].rows_count; ++i) {
        this->data[posx++] = 0x1D; // Row separator 0x1D
        for (char j = 0; j < this->cols_count; ++j) {
            switch (this->columns[j].type) {
                case TYPE_INT:
                    memcpy(this->data + posx, this->columns[j].data[i], ll_SIZE);
                    posx += ll_SIZE;
                    break;
                case TYPE_VARCHAR:
                    memcpy(this->data + posx, this->columns[j].data[i], this->columns[j].size);
                    posx += this->columns[j].size;
                    break;
                case TYPE_TEXT:
                    tmp_str = (char *) this->columns[j].data[i];
                    tmp_size = String::size(tmp_str);
                    memcpy(this->data + posx, this->columns[j].data[i], tmp_size);
                    posx += tmp_size;
                    break;
            }
            this->data[posx++] = 0x1E; // Column separator 0x1E
        }
    }

    this->flushed = true;
    return this->data;
}

long long table::getDataSize() {
    if (this->data == nullptr) {
        return 0;
    }
    long long data_size = 0;
    memcpy(&data_size, this->data, ll_SIZE);
    return data_size;
}
/** END TABLE STRUCTURE */