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

    bool resetVariables();

    struct column *parse_column(String raw);

public:
    Create();

    void run(String query);
};


#endif //DATABASE_CREATE_H
