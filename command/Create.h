//
// Created by Hrayr on 5/30/2020.
//

#ifndef DATABASE_CREATE_H
#define DATABASE_CREATE_H

#include "../types/String.h"
#include <iostream>

using namespace std;

class Create {
private:
    String *columns;
    long long col_count = 0;

public:
    Create() {
        columns = new String[1];
        columns[0] = nullptr;
    }

    void run(String query) {
        String table_name = Parser::getTable(query);

    }
};


#endif //DATABASE_CREATE_H
