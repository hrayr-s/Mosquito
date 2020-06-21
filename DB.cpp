//
// Created by Hrayr on 5/30/2020.
//

#include "types/String.h"
#include "types/structures.h"
#include "DB.h"
#include "FileManager.h"

DB *DB::instance = nullptr;


DB::DB() {
    this->table_count = 0;
    this->_table_data = new char *[1];
    this->_table_structure = new char *[1];
    this->table_structure = new table[1];
    this->tables = new String[1];
    for (int i = 0; i < 1; ++i) {
        this->_table_data[i] = nullptr;
        this->_table_structure[i] = nullptr;
        this->table_structure[i] = nullptr;
        this->tables[i] = nullptr;
    }
}

DB *DB::getInstance() {
    if (DB::instance == nullptr) {
        DB::instance = new DB;
    }
    return DB::instance;
}

DB::~DB() {
    // On program exit or anyway when DB class deconstruct will be called
    // save data into files
    this->save_tables();
    // then delete variables
    delete[] _table_data;
    delete[] _table_structure;
    delete[] tables;
}

bool DB::resize(long long size) {
    if (size < 1) {
        return false;
    }
    char **tmp = new char *[this->table_count];
    long long tmp_size = 0;
    // Copy _table_data into tmp
    for (long long i = 0; i < this->table_count; ++i) {
        tmp_size = String::size(this->_table_data[i]);
        tmp[i] = new char[tmp_size + 1];
        memcpy(tmp[i], this->_table_data[i], tmp_size);
        tmp[i][tmp_size] = '\0';
    }
    delete[] this->_table_data;
    this->_table_data = new char *[this->table_count + size + 1]; // +1 to set the end(nullptr) of array
    // copy stored data back from tmp to tables_data
    for (long long i = 0; i < this->table_count; ++i) {
        tmp_size = String::size(tmp[i]);
        this->_table_data[i] = new char[tmp_size + 1];
        memcpy(this->_table_data[i], tmp[i], tmp_size);
        this->_table_data[i][tmp_size] = '\0';
    }
    long long i = 0;
    if (this->table_count == 0) {
        i = 1;
    }
    for (; i <= size; ++i) {
        this->_table_data[this->table_count + i] = nullptr;
    }
    delete[] tmp;

    // Copy _table_structure into tmp
    tmp = new char *[this->table_count];
    for (i = 0; i < this->table_count; ++i) {
        tmp_size = String::size(this->_table_structure[i]);
        tmp[i] = new char[tmp_size + 1];
        memcpy(tmp[i], this->_table_structure[i], tmp_size);
        tmp[i][tmp_size] = '\0';
    }
    delete[] this->_table_structure;
    this->_table_structure = new char *[this->table_count + size + 1]; // +1 to set the end(nullptr) of array
    // copy stored data back from tmp to tables_data
    for (i = 0; i < this->table_count; ++i) {
        tmp_size = String::size(tmp[i]);
        this->_table_structure[i] = new char[tmp_size + 1];
        memcpy(this->_table_structure[i], tmp[i], tmp_size);
        this->_table_structure[i][tmp_size] = '\0';
    }
    i = 0;
    if (this->table_count == 0) {
        i = 1;
    }
    for (; i <= size; ++i) {
        this->_table_structure[this->table_count + i] = nullptr;
    }
    delete[] tmp;

    // Copy tables into tmp
    String *tmp_tables = new String[this->table_count];
    for (i = 0; i < this->table_count; ++i) {
        tmp_tables[i] = new String(tables[i].getContent());
    }
    delete[] this->tables;
    this->tables = new String[this->table_count + size + 1]; // +1 to set the end(nullptr) of array
    // copy stored data back from tmp to tables_data
    for (i = 0; i < this->table_count; ++i) {
        this->tables[i] = new String(tmp_tables[i].getContent());
    }
    i = 0;
    if (this->table_count == 0) {
        i = 1;
    }
    for (; i <= size; ++i) {
        this->tables[this->table_count + i] = nullptr;
    }
    delete[] tmp_tables;

    struct table *tmp_tables_structs = new table[this->table_count];
    for (i = 0; i < this->table_count; ++i) {
        tmp_tables_structs[i] = this->table_structure[i];
    }
    delete[] this->table_structure;
    this->table_structure = new table[this->table_count + size + 1]; // +1 to set the end(nullptr) of array
    // copy stored data back from tmp to tables_data
    for (i = 0; i < this->table_count; ++i) {
        this->table_structure[i] = tmp_tables_structs[i];
    }
    i = 0;
    if (this->table_count == 0) {
        i = 1;
    }
    for (; i <= size; ++i) {
        this->table_structure[this->table_count + i] = nullptr;
    }
    delete[] tmp_tables_structs;

    return true;
}

bool DB::check_table_loaded(String table_name) {
    return this->get_table_index(table_name) != -1;
}

long long DB::get_table_index(String table_name) {
    if (this->table_count == 0) {
        return -1;
    }
    return String::searchInArray(this->tables, table_name.getContent());
}

bool DB::load_table(String table_name, bool force) {
    long long index = 0;
    if (check_table_loaded(table_name)) {
        if (!force) {
            return true;
        }
        index = this->get_table_index(table_name);
    } else {
        index = this->table_count;
    }
    FileManager f;
    if (f.load(String::concat((char *) table_name, (char *) ".data.db"), (char *) "r")->getError() ==
        FileManager::FILE_NOT_FOUND ||
        f.load(String::concat((char *) table_name, (char *) ".structure.db"), (char *) "r")->getError() ==
        FileManager::FILE_NOT_FOUND) {
        return false;
    }
    // because we already loaded structure file last lets work with that one first
    // Resize current arrays adding one more empty cell
    this->resize(1);
    long long file_size = f.size();
    this->_table_structure[index] = new char[file_size + 1];
    this->_table_structure[index] = f.read();
    this->_table_structure[index][file_size] = '\0';
    this->table_structure[index] = new table(table_name, this->_table_structure[index]);

    // Load table data
    f.load(String::concat((char *) table_name, (char *) ".data.db"), (char *) "r");
    file_size = f.size();
    this->_table_data[index] = new char[file_size + 1];
    this->_table_data[index] = f.read();
    this->_table_data[index][file_size] = '\0';
    this->table_structure[index].setTableData(this->_table_data[index]);

    // save table name
    this->tables[index] = new String(table_name.getContent());
    this->table_count++;
    return true;
}

char *DB::get_table_data(String table_name) {
    load_table(table_name);
    long long index = table_name.searchInArray(this->tables);
    return this->_table_data[index];
}

char *DB::get_table_structure(String table_name) {
    load_table(table_name);
    long long index = table_name.searchInArray(this->tables);
    return this->_table_structure[index];
}

bool DB::save_table_data(String table_name) {
    FileManager f(String::concat((char *) table_name, (char *) ".data.db"), (char *) "w");
    char *data = this->get_table_data(table_name);
    long long size = 0;
    memcpy(&size, data, sizeof(long long));
    f.write(data, size);
    return true;
}

bool DB::save_table_structure(String table_name) {
    FileManager f;
    f.load(String::concat((char *) table_name, (char *) ".structure.db"), (char *) "w");
    long long *size = new long long();
    *size = 0;
    char *struct_data = this->get_table_structure(table_name);
    memcpy(size, &struct_data[1], sizeof(long long));
    f.write(struct_data, *size);
    return true;
}

bool DB::save_tables() {
    for (long long i = 0; i < this->table_count; ++i) {
        this->saveTable(tables[i]);
    }
    return true;
}

char **DB::getTable(String table_name) {
    if (!this->check_table_exists(table_name)) {
        throw "Table does not exists";
    }
    char **tmp = new char *[2];
    tmp[0] = get_table_structure(table_name);
    tmp[1] = get_table_data(table_name);
    return tmp;
}

bool DB::saveTable(String table_name) {
    this->save_table_data(table_name);
    this->save_table_structure(table_name);
    return true;
}

bool DB::check_table_exists(String table_name) {
    FileManager f(table_name + ".structure.db");
    // If there is no structure of this table then it does not exists
    return f.getError() != FileManager::FILE_NOT_FOUND && f.read()[0] != '\0';
}

bool DB::setTableStructure(struct table *tb) {
    if (tb == nullptr) {
        return false;
    }

    if (this->check_table_exists(*tb->name)) {
        throw "Table Already Exists. You can't edit an existing table structure";
    }

    this->resize(1);

    this->tables[this->table_count] = new String(tb->name->getContent());
    long long tmp_size = String::size(tb->data);
    if (tb->data != nullptr) {
        this->_table_data[this->table_count] = new char[tmp_size + 1];
        memcpy(this->_table_data[this->table_count], tb->data, tmp_size);
        this->_table_data[this->table_count][tmp_size] = '\0';
    } else {
        this->_table_data[this->table_count] = nullptr;
    }
    char *structure;
    // 1 byte of columns count and 8 bytes (sizeof(long long)) of a structure size
    long long struct_size = 1 + sizeof(long long);

    for (char i = 0; i < tb->cols_count; ++i) {
        struct_size += 1 + 1 + sizeof(long long) + tb->columns[i].name->size() + 1 + 1;
    }
    structure = new char[struct_size];
    structure[0] = tb->cols_count;
    memcpy(&structure[1], &struct_size, sizeof(long long));
    char *tmp;
    long long previous_col_size = sizeof(long long) + 1, cur_col_size = 0;
    for (char i = 0; i < tb->cols_count; ++i) {
        cur_col_size = 1 + 1 + sizeof(long long) + tb->columns[i].name->size() + 1 + 1;
        tmp = new char[cur_col_size];
        tmp[0] = '\15'; // Shift in column
        tmp[1] = tb->columns[i].type;
        memcpy(&tmp[2], &tb->columns[i].size, sizeof(long long));
        memcpy(&tmp[2 + sizeof(long long)], tb->columns[i].name->getContent(),
               sizeof(char) * tb->columns[i].name->size());
        tmp[cur_col_size - 2] = '\0'; // end of column name string
        tmp[cur_col_size - 1] = '\14'; // Shift out column
        memcpy(&structure[previous_col_size], tmp, cur_col_size);
        previous_col_size += cur_col_size;
        delete[] tmp;
    }
    this->_table_structure[this->table_count] = new char[struct_size];
    memcpy(this->_table_structure[this->table_count], structure, struct_size);
    this->table_count++;
    return true;
}

struct table *DB::getTableStructure(String table_name) {
    this->load_table(table_name);
    long long table_index = this->get_table_index(table_name);
    return &this->table_structure[table_index];
}

bool DB::flush(String table_name) {
    long long index = this->get_table_index(table_name);
    this->_table_data[index] = this->table_structure[index].getTableVoidData();
    this->saveTable(table_name);
    return true;
}

