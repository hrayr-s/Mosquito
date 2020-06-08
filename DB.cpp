//
// Created by Hrayr on 5/30/2020.
//

#include "types/String.h"
#include "DB.h"
#include "FileManager.h"

DB *DB::instance = nullptr;


DB::DB() {
    this->table_count = 0;
    this->table_data = new char *[1];
    this->table_structure = new char *[1];
    this->tables = new String *[1];
    for (int i = 0; i < 1; ++i) {
        this->table_data[i] = nullptr;
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

bool DB::resize(long long size) {
    if (size < 1) {
        return false;
    }
    char **tmp = new char *[this->table_count];
    long long tmp_size = 0;
    // Copy table_data into tmp
    for (long long i = 0; i < table_count; ++i) {
        tmp_size = String::size(this->table_data[i]);
        tmp[i] = new char[tmp_size + 1];
        memcpy(tmp[i], this->table_data[i], tmp_size);
        tmp[i][tmp_size] = '\0';
    }
    delete[] this->table_data;
    this->table_data = new char *[this->table_count + size + 1]; // +1 to set the end(nullptr) of array
    // copy stored data back from tmp to tables_data
    for (long long i = 0; i < table_count; ++i) {
        tmp_size = String::size(tmp[i]);
        this->table_data[i] = new char[tmp_size + 1];
        memcpy(this->table_data[i], tmp[i], tmp_size);
        this->table_data[i][tmp_size] = '\0';
    }
    for (long long i = 0; i <= size; ++i) {
        this->table_data[table_count + i] = nullptr;
    }
    delete[] tmp;

    // Copy table_structure into tmp
    tmp = new char *[this->table_count];
    for (long long i = 0; i < table_count; ++i) {
        tmp_size = String::size(this->table_structure[i]);
        tmp[i] = new char[tmp_size + 1];
        memcpy(tmp[i], this->table_structure[i], tmp_size);
        tmp[i][tmp_size] = '\0';
    }
    delete[] this->table_structure;
    this->table_structure = new char *[this->table_count + size + 1]; // +1 to set the end(nullptr) of array
    // copy stored data back from tmp to tables_data
    for (long long i = 0; i < table_count; ++i) {
        tmp_size = String::size(tmp[i]);
        this->table_structure[i] = new char[tmp_size + 1];
        memcpy(this->table_structure[i], tmp[i], tmp_size);
        this->table_structure[i][tmp_size] = '\0';
    }
    for (long long i = 0; i <= size; ++i) {
        this->table_structure[table_count + i] = nullptr;
    }
    delete[] tmp;

    // Copy tables into tmp
    String **tmp_tables = new String *[this->table_count];
    for (long long i = 0; i < table_count; ++i) {
        tmp_tables[i] = new String(tables[i]->getContent());
    }
    delete[] this->tables;
    this->tables = new String *[this->table_count + size + 1]; // +1 to set the end(nullptr) of array
    // copy stored data back from tmp to tables_data
    for (long long i = 0; i < table_count; ++i) {
        this->tables[i] = new String(tmp_tables[i]->getContent());
    }
    for (long long i = 0; i <= size; ++i) {
        this->tables[table_count + i] = nullptr;
    }
    delete[] tmp_tables;

    return true;
}

bool DB::check_table_loaded(String *table_name) {
    return this->get_table_index(table_name) != -1;
}

long long DB::get_table_index(String *table_name) {
    return String::searchInArray(this->tables, table_name->getContent());
}

bool DB::load_table(String *table_name, bool force) {
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
    if (f.load(String::concat((char *) table_name, (char *) ".data.db"), (char *) "r").getError() ==
        FileManager::FILE_NOT_FOUND ||
        f.load(String::concat((char *) table_name, (char *) ".structure.db"), (char *) "r").getError() ==
        FileManager::FILE_NOT_FOUND) {
        return false;
    }
    // because we already loaded structure file last lets work with that one first
    // Resize current arrays adding one more empty cell
    this->resize(1);
    long long file_size = f.size();
    this->table_structure[index] = new char[file_size + 1];
    this->table_structure[index] = f.read();
    this->table_structure[index][file_size] = '\0';

    // Load table data
    f.load(String::concat((char *) table_name, (char *) ".data.db"), (char *) "r");
    file_size = f.size();
    this->table_data[index] = new char[file_size + 1];
    this->table_data[index] = f.read();
    this->table_data[index][file_size] = '\0';

    // save table name
    this->tables[index] = new String((char *) table_name);

    return true;
}

char *DB::get_table_data(String *table_name) {
    load_table(table_name);
    long long index = table_name->searchInArray(this->tables);
    return this->table_data[index];
}

char *DB::get_table_structure(String *table_name) {
    load_table(table_name);
    long long index = table_name->searchInArray(this->tables);
    return (char *) this->table_data[index];
}

bool DB::save_table_data(String *table_name) {
    FileManager f;
    f.load(String::concat((char *) table_name, (char *) ".data.db"), (char *) "w");
    f.write(this->get_table_data(table_name));
    return true;
}

bool DB::save_table_structure(String *table_name) {
    FileManager f;
    f.load(String::concat((char *) table_name, (char *) ".structure.db"), (char *) "w");
    f.write(this->get_table_data(table_name));
    return true;
}

bool DB::save_tables() {
    for (long long i = 0; i < this->table_count; ++i) {
        this->saveTable(tables[i]);
    }
    return true;
}

char **DB::getTable(String *table_name) {
    char **tmp = new char *[2];
    tmp[0] = get_table_structure(table_name);
    tmp[1] = get_table_data(table_name);
    return tmp;
}

bool DB::saveTable(String *table_name) {
    this->save_table_data(table_name);
    this->save_table_structure(table_name);
    return true;
}