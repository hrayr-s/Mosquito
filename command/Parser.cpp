//
// Created by Hrayr on 5/30/2020.
//

#include "../types/structures.h"
#include "Parser.h"
#include <iostream>
#include "../types/String.h"

int Parser::current_cmd = -1;


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
    Parser::current_cmd = index;
    return index;
}

String Parser::getTable(String query) {
    switch (Parser::current_cmd) {
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
    char col_name_decorators[] = "`'";
    // ----------------------------- NEW Implementation
    bool look_for_name = true;
    String col_name;
    str = str.trim();
    if (str[0] == col_name_decorators[0]) {

    }
    for (int i = 0; i < str.length(); ++i) {
        if (look_for_name) {

        }
    }
    // ----------------------------- OLD Implementation
    char decorator = '\'';
    char sec_decorator = '`';
    String search_obj = str.trim();
    long long index1 = -1, index2 = -1;
    index1 = search_obj.search((char *) decorator);
    if (index1 != -1) {
        index2 = search_obj.search((char *) decorator, index1 + 1);
    } else {
        // If first decorator wasn't found lookup for the second
        index1 = search_obj.search((char *) sec_decorator);
        if (index1 != -1) {
            index2 = search_obj.search((char *) sec_decorator, index1 + 1);
        }
    }
    return search_obj.cut(index1, index2 - index1 - 1);
}

String *Parser::getColumnName_P(String *str) {
    long long index1 = str->search((char *) "`");
    long long index2 = str->search((char *) "`", index1 + 1);
    String *rtn = new String(str->cut(index1, index2));
    return rtn;
}

char Parser::getColumnType(String str) {
    long long index1 = str.search((char *) "`");
    if (index1 == -1) {
        index1 = str.search((char *) "'", index1);
    } else {
        index1 = str.search((char *) "`", index1);
        if (index1 == -1) {
            throw (new String("Syntax Error: ")) + str;
        }
    }
    String s = str.cut(index1, str.length() - index1).trim();
    if (s[s.length() - 1] == ')') {
        s = s.cut(0, s.search("(") - 1);
    }
    if (s.length() == 0) {
        long long index2 = str.search((char *) ",", index1);
        index1 = str.search((char *)" ", str.length() - index2);
        s = str.cut(index1, index2).trim();
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

char *Parser::parseInsertValues(table tb, String str) {
    long long pos = str.search(tb.name->getContent()) + 1;
    void **raw_data;
    raw_data = new void *[101];
    raw_data[100] = nullptr;
    long long tmp_integer = 0;
    String tmp_string;
    while (str[pos] != '\0') {
        for (char i = 0; i < tb.cols_count; ++i) {
            // Split str with ',' delimeter and assign each column - value
        }
    }
    return nullptr;
}

String *Parser::getSelectColumns(String query) {
    long long start = query.search("SELECT", 0);
    String cols_raw = query.cut(start, query.search(" FROM ", 0) - 6 - start);
    String *cols = cols_raw.split(",");
    for (long long i = 0; cols[i] != nullptr; ++i) {
        cols[i] = cols[i].trim();
        cols[i] = cols[i].cut(1, cols[i].length() - 2);
    }
    return cols;
}

struct condition *Parser::parseConditions(String query) {
    long long start = query.search("WHERE", 0);
    long long start_AND, start_OR;
    if (start == -1) {
        return nullptr;
    }
    String condition_raw = query.cut(start, query.length() - start - 1).trim();
    start_AND = condition_raw.search("AND");
    start_OR = condition_raw.search("OR");
    if (start_OR > start_AND) {
        start = start_AND - 3;
    } else {
        start = start_OR - 2;
    }
    if (start <= -1) {
        start = condition_raw.length();
    }
    struct condition *s = new condition[2];
    s[0].set(condition_raw.cut(0, start));
    s[1] = NULL;
    return s;
}
