//
// Created by Hrayr on 5/30/2020.
//

#ifndef DATABASE_CREATE_H
#define DATABASE_CREATE_H

#include "../types/String.h"
#include <iostream>
#include "types/structures.h"

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
        long long size = 0;

        s = new column[1];
        s[0].name = &raw;
        s[0].type = 1;
        s[0].size = 0;
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
        long long *items = query.searchAll((char *) ",", begin_cols);
        cout << query.cut(begin_cols, items[0] - begin_cols) << endl;
        long long i = 1;
        for (; items[i] != NULL; ++i) {
            cout << query.cut(items[i - 1], items[i] - items[i - 1]) << endl;
        }
        cout << query.cut(items[i - 1], end_cols - items[i - 1] + 1) << endl;
        struct column *cols = this->parse_column(query.cut(begin_cols, end_cols - begin_cols + 1));

    }
};


#endif //DATABASE_CREATE_H
