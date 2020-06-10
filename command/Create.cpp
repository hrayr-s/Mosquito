//
// Created by Hrayr on 5/30/2020.
//

#include "../types/String.h"
#include "../types/structures.h"
#include "../ArrayHelper.h"
#include "Parser.h"
#include "Create.h"
#include "../DB.h"

bool Create::resetVariables() {
    delete[] this->tb;
    this->tb = nullptr;
    return true;
}

struct table *Create::parse_table(String table_name, String *raw) {
    this->tb = new table(table_name, raw);
    return this->tb;
}

Create::Create() {
    this->tb = nullptr;
}

void Create::run(String query) {
    this->resetVariables();
    String table_name = Parser::getTable(query);
    long long begin_cols = query.search("(");
    long long end_cols = query.search(")", 0, true);
    long long *items = query.searchAll((char *) ",", begin_cols);
    long long col_count = ArrayHelper::count(items) + 1;
    String *raw_cols = new String[col_count + 1];
    raw_cols[col_count] = nullptr;
    raw_cols[0] = query.cut(begin_cols, items[0] - 1 - begin_cols).trim();
    long long i = 1;
    for (; items[i] != NULL; ++i) {
        raw_cols[i] = query.cut(items[i - 1], items[i] - 1 - items[i - 1]).trim();
    }
    raw_cols[i] = query.cut(items[i - 1], end_cols - items[i - 1] + 1).trim();
    this->parse_table(table_name, raw_cols);
    DB::getInstance()->setTableStructure(this->tb);
    DB::getInstance()->saveTable(*this->tb->name);
}