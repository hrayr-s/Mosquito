//
// Created by Hrayr on 5/30/2020.
//

#ifndef DATABASE_PARSER_H
#define DATABASE_PARSER_H

#include <iostream>
#include "../types/String.h"

const char COMMAND_SELECT = 0,
        COMMAND_UPDATE = 1,
        COMMAND_DELETE = 2,
        COMMAND_INSERT = 3,
        COMMAND_DROP = 4,
        COMMAND_CREATE = 5,
        COMMAND_EXIT = 6;

class Parser {
private:
    static constexpr int cmnds_count = 7;
    static constexpr char cmnds[7][7] = {
            "SELECT",
            "UPDATE",
            "DELETE",
            "INSERT",
            "DROP\0\0",
            "CREATE",
            "EXIT\0\0"
    };

    static String get_table_name(String &query, const char *from_str) {
        long long from_pos = query.search(from_str, 0);
        long long table_pos = query.search("`", from_pos);
        long long table_word_end_pos = query.search("`", table_pos + 1);
        return query.cut(table_pos, table_word_end_pos - table_pos - 1);
    }

    /**
     * Extract table name from SELECT query string
     * @param query
     * @return
     */
    static String get_table_from_select(String &query) {
        return Parser::get_table_name(query, "FROM");
    }

    /**
     * Extract table name from CREATE table query string
     * @param query
     * @return
     */
    static String get_table_from_create(String &query) {
        return Parser::get_table_name(query, "TABLE");
    }

    /**
     * Extract table name from INSERT table query string
     * @param query
     * @return
     */
    static String get_table_from_insert(String &query) {
        return Parser::get_table_name(query, "INTO");
    }

    /**
     * Extract table name from DROP table query string
     * @param query
     * @return
     */
    static String get_table_from_drop(String &query) {
        return Parser::get_table_name(query, "TABLE");
    }

    /**
     * Extract table name from DELETE table query string
     * @param query
     * @return
     */
    static String get_table_from_delete(String &query) {
        return Parser::get_table_name(query, "FROM");
    }

    /**
     * Extract table name from UPDATE table query string
     * @param query
     * @return
     */
    static String get_table_from_update(String &query) {
        return Parser::get_table_name(query, "UPDATE");
    }

public:
    static int cureent_cmd;

    static int getCMD(char *command) {
        char cmd[7];
        cmd[6] = '\0';
        for (int i = 0, k = 0; i < cmnds_count; ++i) {
            if (k == 0 && (command[i] == ' ' || command[i] == '\n' || command[i] == '\t' || command[i] == '\r')) {
                continue;
            }
            cmd[k] = command[i];
            if (cmd[k] == ' ' || cmd[k] == '\n' || command[i] == '\t' || command[i] == '\r') {
                cmd[k] = '\0';
                break;
            }
            k++;
        }
        int index = 0;
        for (; index < cmnds_count; ++index) {
            if (String::compare(cmd, (char *) Parser::cmnds[index]))
                break;
        }
        Parser::cureent_cmd = index;
        return index;
    }

    /**
     * Extracts table name from command
     * Should be called only after getCMD
     * @param cmd
     * @return
     */
    static String getTable(String query) {
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

    static String getColumnName(String str) {
        long long index1 = str.search((char *) "`");
        long long index2 = str.search((char *) "`", index1 + 1);
        return str.cut(index1, index2);
    }

    static String getColumnName(String *str) {
        long long index1 = str.search((char *) "`");
        long long index2 = str.search((char *) "`", index1 + 1);
        return str.cut(index1, index2);
    }

    static int getColType(String *str) {
        long long index1 = str.search((char *) "`");
        long long index2 = str.search((char *) "`", index1 + 1);
        String tmp =
        return 0;
    }
};


#endif //DATABASE_PARSER_H
