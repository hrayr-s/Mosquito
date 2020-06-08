//
// Created by Hrayr on 5/30/2020.
//


#include "../types/String.h"
#include "Parser.h"
#include "Select.h"

using namespace std;

void Select::run(String query) {
    String table_name = Parser::getTable(query);
    cout << table_name << endl;
}