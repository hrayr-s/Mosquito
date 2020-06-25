//
// Created by Hrayr on 5/30/2020.
//


#include "../types/structures.h"
#include "../types/String.h"
#include "Parser.h"
#include "Select.h"
#include "../DB.h"
#include <iomanip>

using namespace std;

void Select::run(String query) {
    String table_name = Parser::getTable(query);
    struct table *tb = DB::getInstance()->getTableStructure(table_name);
    String *select_columns = Parser::getSelectColumns(query);
    long long *cols_indexes = new long long[256];
    if (select_columns[0] == "*") {
        for (char i = 0; i < tb->cols_count; ++i) {
            cols_indexes[i] = i;
        }
        cols_indexes[tb->cols_count] = -1;
    } else {
        char i;
        char j;
        for (i = 0; select_columns[i] != nullptr; ++i) {
            j = 0;
            for (; j < tb->cols_count; ++j) {
                if (*tb->columns[j].name == select_columns[i]) {
                    cols_indexes[i] = j;
                    break;
                }
            }
            // If j = tb->cols_counts that means column was not found
            if (j == tb->cols_count) {
                String err("Column ");
                err += select_columns[i];
                err += " was not found in the table!";
                throw err.getContent();
            }
        }
        cols_indexes[i] = -1;
    }

    // Note! For now there's only one condition
    struct condition *conditions = Parser::parseConditions(query);
    if (conditions != nullptr) {
        for (int k = 0; conditions[k] != nullptr; ++k) {
            for (char f = 0; f < tb->cols_count; ++f) {
                if (*tb->columns[f].name == *conditions[k].left_operand) {
                    conditions[k].col_index = f;
                    break;
                }
            }
        }
    }
    for (int k = 0; cols_indexes[k] != -1; ++k) {
        cout << left << setfill(' ') << (tb->columns[cols_indexes[k]].type == TYPE_INT ? setw(12) : setw(30))
             << *tb->columns[cols_indexes[k]].name << right;
    }
    cout << endl;
    bool show_row = true;
    for (long long i = 0; i < tb->columns[0].rows_count; ++i) {
        show_row = true;
        for (int k = 0; conditions[k] != nullptr; ++k) {
            if (!conditions[k].doCompare(tb, i)) {
                show_row = false;
                break;
            }
        }
        if (!show_row) {
            continue;
        }
        for (long long col = 0; cols_indexes[col] != -1; ++col) {
            switch (tb->columns[cols_indexes[col]].type) {
                case TYPE_INT:
                    cout << left << setfill(' ') << setw(12) << *((long long *) tb->columns[cols_indexes[col]][i]);
                    break;
                case TYPE_VARCHAR:
                case TYPE_TEXT:
                    cout << left << setfill(' ') << setw(30) << (char *) tb->columns[cols_indexes[col]][i];
                    break;
            }
        }
        cout << endl;
    }
}