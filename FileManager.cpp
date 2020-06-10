//
// Created by Hrayr on 5/29/2020.
//

#include <iostream>
#include "types/String.h"
#include "FileManager.h"

FileManager::FileManager() {
    this->setError(NO_ERROR);
}

FileManager::FileManager(char *filename) {
    this->load(filename, "r");
}

FileManager::FileManager(String filename) {
    this->load(filename, "r");
}

FileManager::FileManager(char *filename, char *mode) {
    this->load(filename, mode);
}

FileManager::FileManager(String filename, char *mode) {
    this->load(filename, mode);
}

FILE *FileManager::getFileInstance() {
    return this->f;
}

void FileManager::setError(int code) {
    this->current_error = code;
}

FileManager FileManager::load(char *name, char *mode) {
    String fname(name);
    this->filename = &fname;
    this->mode = mode;
    this->setError(NO_ERROR);
    this->f = fopen(filename->getContent(), mode);
    if (this->f == nullptr) {
        this->setError(FILE_NOT_FOUND);
    } else {
        fseek(this->f, 0, SEEK_END);
    }
    return *this;
}

char *FileManager::getFileName() {
    return (char *) this->filename;
}

char *FileManager::read() {
    this->setError(NO_ERROR);
    char *content;
    long long size = 0;

    if (this->f == nullptr) {
        this->setError(FILE_NOT_FOUND);
        return nullptr;
    }
    size = this->size();
    content = new char[size + 1];
    cout << size << endl;
    fread(content, sizeof(char), size, this->f);
    content[size] = '\0';
    return content;
}

long long FileManager::size() {
    long long size;
    long long current_pos = ftell(this->f); // save current position
    fseek(this->f, 0, SEEK_END); // set current position to the end of file
    size = ftell(this->f); // get position - this will be the size of the file
    fseek(this->f, current_pos, SEEK_SET); // set current position that saved position
    return size; // return size of a file
}

bool FileManager::write(char *content, long long int size) {
    this->setError(NO_ERROR);
    // No file opened or Requested file does not exist
    if (this->f == nullptr) {
        this->setError(FILE_NOT_FOUND);
        return false;
    }

    if (this->mode == "r") {
        throw "Can not write until file open mode is 'r'";
    }
    // Empty content to write
    if (content == nullptr) {
        fputc('\0', this->f);
    } else {
        fwrite(content, sizeof(char), size, this->f);
    }
    fflush(this->f);
    return true;
}

bool FileManager::write(char *content) {
    long long size = String::size(content);
    return this->write(content, size);
}

bool FileManager::write(String content) {
    return this->write(content.getContent(), content.length());
}
/*

FileManager::~FileManager() {
    if (this->f != nullptr) {
        fclose(this->f);
    }
}
*/
