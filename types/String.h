//
// Created by Hrayr on 5/29/2020.
//

#ifndef DATABASE_STRING_H
#define DATABASE_STRING_H
#include <iostream>

class String {
private:
    char* content;
    long long size = 0;
    long long actual_size = 100;

public:
    String() {
        content = new char[actual_size];
    }

    String(char *text) {
        long long size = String::size(text);
        this->content = new char[size];
        std::strcpy(this->content, text);
    }

    /**
     * Returns position of searched string
     * @param text
     * @param haystack
     * @return
     */
    static long long search(char *text, char *haystack) {

    }

    long long search (char* haystack) {
        return String::search(this->content, haystack);
    }

    static long long size(char* text) {
        long long size = 0;
        for (;text[size] != '\0'; ++size) {}
        return size;
    }

    long long size() {
        return this->size;
    }
};


#endif //DATABASE_STRING_H
