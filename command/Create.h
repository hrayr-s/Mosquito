//
// Created by Hrayr on 5/30/2020.
//

#ifndef DATABASE_CREATE_H
#define DATABASE_CREATE_H

class String;
class Parser;

#include <iostream>

using namespace std;

class Create {
private:
    struct table *tb;

    bool resetVariables();

    struct table *parse_table(String table_name, String *raw);


public:
    Create();

    void run(String query);
};


#endif //DATABASE_CREATE_H
