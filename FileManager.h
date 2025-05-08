//
// Created by Hrayr on 5/29/2020.
//

#ifndef DATABASE_FILEMANAGER_H
#define DATABASE_FILEMANAGER_H

class String;
#include <iostream>

using namespace std;

enum STATUS
{
    NO_ERROR = 0,
    FILE_NOT_FOUND=1,
    CONTENT_LENGTH_ZERO=2,
    FILE_OPEN_ERROR=3,
    FILE_READ_ERROR=4,
    FILE_WRITE_ERROR=5
};

class FileManager
{
private:
    FILE* f;
    char* mode;
    int current_error = 0;
    String* filename;

public:
    static constexpr int NO_ERROR = 0,
                         FILE_NOT_FOUND = 1,
                         CONTENT_LENGTH_ZERO = 2;

    FileManager();

    explicit FileManager(char* filename);

    explicit FileManager(String filename);

    FileManager(char* filename, char* mode);

    FileManager(String filename, char* mode);

    ~FileManager();

    FILE* getFileInstance();

    void setError(int code);

    int getError();

    /**
     * Loads file into current instance
     * @param name
     * @param mode
     * @return
     */
    FileManager* load(char* name, char* mode = static_cast<char*>("r"));

    char* getFileName();

    char* read();

    long long size();

    bool write(char* content, long long size);

    bool write(char* content);

    bool write(String content);
};


#endif //DATABASE_FILEMANAGER_H
