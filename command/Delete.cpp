//
// Created by Hrayr on 5/30/2020.
//

#include "../types/String.h"
#include "Parser.h"
#include "Delete.h"
#include "../types/structures.h"
#include "../DB.h"
#include <iostream>

using namespace std;

void Delete::run(String query) {
    String table_name = Parser::getTable(query);
    struct table *tb = DB::getInstance()->getTableStructure(table_name);
    struct condition *conditions = Parser::parseConditions(query);
    long long affected_rows = 0;
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
    bool rm;
    for (long long i = 0; i < tb->columns[0].rows_count; ++i) {
        rm = true;
        for (int k = 0; conditions[k] != nullptr; ++k) {
            if (!conditions[k].doCompare(tb, i)) {
                rm = false;
                break;
            }
        }
        if (!rm) {
            continue;
        }
        tb->remove(i);
        affected_rows++;
    }
    DB::getInstance()->flush(table_name);
    cout << "Affected " << affected_rows << " row(s)!" << endl;
}