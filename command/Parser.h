//
// Created by Hrayr on 5/30/2020.
//

#ifndef DATABASE_PARSER_H
#define DATABASE_PARSER_H

class String;

const char COMMAND_SELECT = 0,
        COMMAND_UPDATE = 1,
        COMMAND_DELETE = 2,
        COMMAND_INSERT = 3,
        COMMAND_DROP = 4,
        COMMAND_CREATE = 5,
        COMMAND_EXIT = 6;

const char TYPE_INT = 0,
        TYPE_VARCHAR = 1,
        TYPE_TEXT = 2;

class Parser {
private:
    static constexpr int cmnds_count = 7;
    static constexpr char cmnds[cmnds_count][7] = {
            "SELECT",
            "UPDATE",
            "DELETE",
            "INSERT",
            "DROP\0\0",
            "CREATE",
            "EXIT\0\0"
    };
    static constexpr short int types_count = 3;
    static constexpr char types[types_count][8] = {
            "INT\0\0\0\0",
            "VARCHAR",
            "TEXT\0\0\0"
    };

    static String get_table_name(String &query, const char *from_str);

    /**
     * Extract table name from SELECT query string
     * @param query
     * @return
     */
    static String get_table_from_select(String &query);

    /**
     * Extract table name from CREATE table query string
     * @param query
     * @return
     */
    static String get_table_from_create(String &query);

    /**
     * Extract table name from INSERT table query string
     * @param query
     * @return
     */
    static String get_table_from_insert(String &query);

    /**
     * Extract table name from DROP table query string
     * @param query
     * @return
     */
    static String get_table_from_drop(String &query);

    /**
     * Extract table name from DELETE table query string
     * @param query
     * @return
     */
    static String get_table_from_delete(String &query);

    /**
     * Extract table name from UPDATE table query string
     * @param query
     * @return
     */
    static String get_table_from_update(String &query);

public:
    static int cureent_cmd;

    static int getCMD(char *command);

    /**
     * Extracts table name from command
     * Should be called only after getCMD
     * @param cmd
     * @return
     */
    static String getTable(String query);

    static String getColumnName(String str);

    static String *getColumnName_P(String *str);

    static char getColumnType(String str);

    static long long getColumnSize(String col);

    static char *getColumnTypeName(char type);

    static char *parseInsertValues(struct table tb, String str);

    static String *getSelectColumns(String query);

    static struct condition *parseConditions(String query);
};
#endif //DATABASE_PARSER_H
