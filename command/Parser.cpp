//
// Created by Hrayr on 5/30/2020.
//

#include "Parser.h"
#include <iostream>
#include "../types/String.h"

int Parser::cureent_cmd = -1;


String Parser::get_table_name(String &query, const char *from_str) {
    long long from_pos = query.search(from_str, 0);
    long long table_pos = query.search("`", from_pos);
    long long table_word_end_pos = query.search("`", table_pos + 1);
    return query.cut(table_pos, table_word_end_pos - table_pos - 1);
}

String Parser::get_table_from_select(String &query) {
    return Parser::get_table_name(query, "FROM");
}

String Parser::get_table_from_create(String &query) {
    return Parser::get_table_name(query, "TABLE");
}

String Parser::get_table_from_insert(String &query) {
    return Parser::get_table_name(query, "INTO");
}

String Parser::get_table_from_drop(String &query) {
    return Parser::get_table_name(query, "TABLE");
}

String Parser::get_table_from_delete(String &query) {
    return Parser::get_table_name(query, "FROM");
}

String Parser::get_table_from_update(String &query) {
    return Parser::get_table_name(query, "UPDATE");
}

int Parser::getCMD(char *command) {
    char cmd[7];
    cmd[6] = '\0';
    for (int i = 0, k = 0; i < Parser::cmnds_count; ++i) {
        if (k == 0 && (command[i] == ' ' || command[i] == '\n' || command[i] == '\t' || command[i] == '\r')) {
            continue;
        }
        cmd[k] = command[i];
        if (cmd[k] == ' ' || cmd[k] == '\n' || command[i] == '\t' || command[i] == '\r' || command[i] == ';') {
            cmd[k] = '\0';
            break;
        }
        k++;
    }
    int index = 0;
    for (; index < Parser::cmnds_count; ++index) {
        if (String::compare(cmd, (char *) Parser::cmnds[index]))
            break;
    }
    Parser::cureent_cmd = index;
    return index;
}

String Parser::getTable(String query) {
    switch (Parser::cureent_cmd) {
        case COMMAND_CREATE:
            return Parser::get_table_from_create(query);
        case COMMAND_INSERT:
            return Parser::get_table_from_insert(query);
        case COMMAND_UPDATE:
            return Parser::get_table_from_update(query);
        case COMMAND_DELETE:
            return Parser::get_table_from_delete(query);
        case COMMAND_DROP:
            return Parser::get_table_from_drop(query);
        case COMMAND_SELECT:
            return Parser::get_table_from_select(query);
        default:
            return nullptr;
    }
}

String Parser::getColumnName(String str) {
    long long index1 = str.search((char *) "`");
    long long index2 = str.search((char *) "`", index1 + 1);
    return str.cut(index1, index2 - index1 - 1);
}

String *Parser::getColumnName_P(String *str) {
    long long index1 = str->search((char *) "`");
    long long index2 = str->search((char *) "`", index1 + 1);
    String *rtn = new String(str->cut(index1, index2));
    return rtn;
}

char Parser::getColumnType(String str) {
    long long index1 = str.search((char *) "`");
    index1 = str.search((char *) "`", index1);
    String s = str.cut(index1, str.length() - index1).trim();
    if (s[s.length() - 1] == ')') {
        s = s.cut(0, s.search("(") - 1);
    }
    char index = 0;
    for (; index < Parser::types_count; ++index) {
        if (s.compare((char *) Parser::types[index]))
            break;
    }
    if (index == Parser::cmnds_count) {
        return -1;
    }
    return index;
}

long long Parser::getColumnSize(String col) {
    long long index1 = col.search("(");
    long long index2 = col.search(")");
    return (long long) col.cut(index1, index2 - index1 - 1);
}

char *Parser::getColumnTypeName(char type) {
    return (char *) Parser::types[type];
}
