//
// Created by Hrayr on 6/1/2020.
//

#ifndef DATABASE_STRUCTURES_H
#define DATABASE_STRUCTURES_H

#include <cstddef>

class String;

struct column {
    String *name;
    int type;
    long long size;

    column();

    column(String raw_col);

    column(column *pColumn);

    struct column operator=(nullptr_t s);

    bool operator==(nullptr_t s);

    bool operator!=(nullptr_t s);

};

struct table {
    struct column *columns;
    long long cols_count;
    String *name;
    char *data;

    table();

    /**
     * With given String array organize table structure
     * @param s
     * @return
     */
    table(String name, String *raw);

    struct table operator=(nullptr_t s);

    /**
     * With given String array organize table structure
     * @param s
     * @return
     */
    struct table operator=(String *s);

    bool operator==(nullptr_t s);

    bool operator!=(nullptr_t s);
};

#endif //DATABASE_STRUCTURES_H
