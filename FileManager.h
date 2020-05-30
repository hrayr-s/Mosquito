//
// Created by Hrayr on 5/29/2020.
//

#ifndef DATABASE_FILEMANAGER_H
#define DATABASE_FILEMANAGER_H

#include <iostream>
#include "types/String.h"
using namespace std;

class FileManager {
private:
    FILE *f;
    char* mode;
    int current_error = 0;
    String filename;
public:
    const int NO_ERROR = 0,
        FILE_NOT_FOUND = 1,
        CONTENT_LENGTH_ZERO = 2;

    FileManager() {
        this->setError(NO_ERROR);
    }

    FileManager(char *filename) {
        this->setError(NO_ERROR);
        this->f = fopen(filename, "r");
        if (this->f == NULL) {
            this->setError(FILE_NOT_FOUND);
        }
        this->mode = "r";
    }

    FileManager(char *filename, char *mode) {
        this->setError(NO_ERROR);
        this->f = fopen(filename, mode);
        if (this->f == NULL) {
            this->setError(FILE_NOT_FOUND);
        }
        this->mode = mode;
    }

    FILE *getFileInstance() {
        return this->f;
    }

    void setError(int code) {
        this->current_error = code;
    }

    int getError() {
        return this->current_error;
    }

    void setFileName(char* name) {
        String fname(name);
        this->filename = fname;
    }

    char* getFileName() {
        return this->filename.getContent();
    }

    char *read() {
        this->setError(NO_ERROR);
        char *content;
        long long size = 0;

        if (this->f == NULL) {
            this->setError(FILE_NOT_FOUND);
            return nullptr;
        }

        fseek(this->f, 0, SEEK_END);
        size = ftell(this->f);
        rewind(this->f);
        content = new char[size + 1];
        cout << size << endl;
        fread(content, sizeof(char), size, this->f);
        content[size] = '\0';
        return content;
    }

    bool write(char *content) {
        this->setError(NO_ERROR);
        // No file opened or Requested file does not exist
        if (this->f == NULL) {
            this->setError(FILE_NOT_FOUND);
            return false;
        }

        if (this->mode == "r") {
            throw "Can not write until file open mode is 'r'";
        }
        // Empty content to write
        if (content[0] == '\0') {
            this->setError(CONTENT_LENGTH_ZERO);
            return false;
        }
        long long size = String::size(content);

        fwrite(content, sizeof(char), size, this->f);
        return true;
    }

    bool write(String content) {
        this->setError(NO_ERROR);
        // No file opened or Requested file does not exist
        if (this->f == NULL) {
            this->setError(FILE_NOT_FOUND);
            return false;
        }

        if (this->mode == "r") {
            throw "Can not write until file open mode is 'r'";
        }
        // Empty content to write
        if (content.getContent()[0] == '\0' || content.length() == 0) {
            this->setError(CONTENT_LENGTH_ZERO);
            return false;
        }

        fwrite(content.getContent(), sizeof(char), content.length(), this->f);
        return true;
    }
};


#endif //DATABASE_FILEMANAGER_H
