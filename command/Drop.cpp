//
// Created by Hrayr on 5/30/2020.
//


#include "../types/String.h"
#include "Parser.h"
#include "Drop.h"
#include "../DB.h"

using namespace std;

void Drop::run(String query) {
    String table_name = Parser::getTable(query);
    cout << endl;
    if (!DB::getInstance()->check_table_exists(table_name)) {
        throw "Can not find provided table!";
    }
    remove((table_name + ".structure.db").getContent());
    remove((table_name + ".data.db").getContent());
}

