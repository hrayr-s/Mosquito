//
// Created by Hrayr on 5/31/2020.
//

#ifndef DATABASE_ARRAYHELPER_H
#define DATABASE_ARRAYHELPER_H

class ArrayHelper {
public:
    static bool resize(String *&f, long long size = 1);

    static bool resize(struct column *columns, long long size = 1);

    static bool resize(long long *&f, long long size = 1);
};


#endif //DATABASE_ARRAYHELPER_H
