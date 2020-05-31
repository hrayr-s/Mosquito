//
// Created by Hrayr on 5/30/2020.
//

#ifndef DATABASE_DELETE_H
#define DATABASE_DELETE_H

#include <iostream>

using namespace std;

class Delete {

public:
    void run(String query) {
        String table_name = Parser::getTable(query);
        cout << table_name << endl;
    }
};


#endif //DATABASE_DELETE_H
