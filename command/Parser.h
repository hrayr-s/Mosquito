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

    static String *getColumnName(String *str);

    static int getColType(String &str);

};
#endif //DATABASE_PARSER_H
