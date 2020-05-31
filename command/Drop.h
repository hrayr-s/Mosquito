//
// Created by Hrayr on 5/30/2020.
//

#ifndef DATABASE_DROP_H
#define DATABASE_DROP_H

#include <iostream>

class Drop {

public:
    void run(String query) {
        String table_name = Parser::getTable(query);
        cout << table_name << endl;
    }
};


#endif //DATABASE_DROP_H
