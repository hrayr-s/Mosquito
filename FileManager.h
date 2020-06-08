//
// Created by Hrayr on 5/29/2020.
//

#ifndef DATABASE_FILEMANAGER_H
#define DATABASE_FILEMANAGER_H

class String;
#include <iostream>

using namespace std;

class FileManager {
private:
    FILE *f;
    char *mode;
    int current_error = 0;
    String *filename;
public:
    static const int NO_ERROR = 0,
            FILE_NOT_FOUND = 1,
            CONTENT_LENGTH_ZERO = 2;

    FileManager();

    FileManager(char *filename);

    FileManager(char *filename, char *mode);

    FILE *getFileInstance();

    void setError(int code);

    int getError() {
        return this->current_error;
    }

    /**
     * Loads file into current instance
     * @param name
     * @param mode
     * @return
     */
    FileManager load(char *name, char *mode = "r");

    char *getFileName();

    char *read();

    long long size();

    bool write(char *content);

    bool write(String content);
};


#endif //DATABASE_FILEMANAGER_H
