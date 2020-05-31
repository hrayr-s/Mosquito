//
// Created by Hrayr on 5/30/2020.
//

#ifndef DATABASE_SELECT_H
#define DATABASE_SELECT_H

#include "../types/String.h"
#include "Parser.h"
#include <iostream>

class Select {
private:

    bool Table(char *params) {

    }

public:
    void run(String query) {
        String table_name = Parser::getTable(query);
        std::cout << table_name << std::endl;
    }
};


#endif //DATABASE_SELECT_H
