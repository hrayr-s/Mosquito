//
// Created by Hrayr on 5/30/2020.
//

#ifndef DATABASE_UPDATE_H
#define DATABASE_UPDATE_H

#include <iostream>

using namespace std;

class Update {

public:
    void run(String query) {
        String table_name = Parser::getTable(query);
        cout << table_name << endl;
    }
};


#endif //DATABASE_UPDATE_H
