//
// Created by Hrayr on 5/30/2020.
//

#ifndef DATABASE_INSERT_H
#define DATABASE_INSERT_H

#include <iostream>

using namespace std;

class Insert {

public:
    void run(String query) {
        String table_name = Parser::getTable(query);
        cout << table_name << endl;
    }
};


#endif //DATABASE_INSERT_H
