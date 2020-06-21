//
// Created by Hrayr on 5/30/2020.
//

#ifndef DATABASE_INSERT_H
#define DATABASE_INSERT_H

class String;

class Parser;

#include <iostream>

class Insert {
private:
    char *values_text = "VALUES";
public:

    void run(String query);
};


#endif //DATABASE_INSERT_H
