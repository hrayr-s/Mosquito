//
// Created by Hrayr on 6/1/2020.
//

#ifndef DATABASE_STRUCTURES_H
#define DATABASE_STRUCTURES_H

#include <cstddef>

class String;

struct column {
    String *name;
    char type;
    long long size;
    long long rows_count;
    void **data; // column data array indexed row by row

    column();

    column(String raw_col);

    column(column *pColumn);

    struct column operator=(nullptr_t s);

    struct column operator=(String raw_col);

    bool operator==(nullptr_t s);

    bool operator!=(nullptr_t s);

    bool insert(String data);

    bool remove_last_added();

    bool checkVar(String var);
};

struct table {
    struct column *columns;
    char cols_count; // Table columns count should not be more than 255
    String *name;
    char *data; // Raw data of a table

    bool flushed; // Indicator of flushed into raw this->data from columns data

    table();

    /**
     * With given String array organize table structure
     * @param s
     * @return
     */
    table(String name, String *raw);

    /**
     * With given char/byte array organize table structure
     * @param s
     * @return
     */
    table(String name, char *raw);

    struct table operator=(nullptr_t s);

    struct table operator=(table *tb);

    /** No needed for now
     * With given String array organize table structure
     * @param s
     * @return
     */
    struct table operator=(String *s);

    bool operator==(nullptr_t s) const;

    bool operator!=(nullptr_t s) const;

    bool setTableData(char *raw);

    bool insert(String raw);

    char *getTableVoidData();

    long long getDataSize();
};

#endif //DATABASE_STRUCTURES_H
