//
// Created by Hrayr on 5/30/2020.
//

#ifndef DATABASE_CREATE_H
#define DATABASE_CREATE_H

#include "../types/String.h"
#include <iostream>
#include "types/structures.h"
#include "ArrayHelper.cpp"

using namespace std;

class Create {
private:
    long long col_count;
    struct column *columns;

    bool resetVariables() {
        delete[] columns;
        columns = new column[1];
        columns[0] = nullptr;
        col_count = 0;

        return true;
    }

    struct column *parse_column(String raw) {
        struct column *s;
        unsigned long long size = 0;

        long long *items = raw.searchAll((char *) ",", (long long) 0);
        size = count(items) + 1;
        cout << size << " columns" << endl;
        s = new column[size + 1];
        String tmp;
        tmp = raw.cut(0, items[0]);

        s[0].name = new String(Parser::getColumnName(tmp));

        long long i = 1;
        for (; items[i] != NULL; ++i) {
            cout << raw.cut(items[i - 1], items[i] - items[i - 1]) << endl;

        }
        cout << raw.cut(items[i - 1], raw.length() - items[i - 1]) << endl;

        return s;
    }

public:
    Create() {
        columns = new struct column[1];
        columns[0] = nullptr;
        col_count = 0;
    }

    void run(String query) {
        this->resetVariables();
        String table_name = Parser::getTable(query);
        long long begin_cols = query.search("(");
        long long end_cols = query.search(")", 0, true);
        struct column *cols = this->parse_column(query.cut(begin_cols, end_cols - begin_cols + 1));

    }
};


#endif //DATABASE_CREATE_H
