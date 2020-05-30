//
// Created by Hrayr on 5/29/2020.
//

#ifndef DATABASE_STRING_H
#define DATABASE_STRING_H

#include <iostream>

class String {
private:
    char *content;
    long long _size = 0;
    long long actual_size = 100;

public:
    String() {
        content = new char[actual_size];
    }

    String(char *text) {
        long long size = String::size(text);
        this->content = new char[size];
        this->_size = size;
        std::strcpy(this->content, text);
    }

    friend std::ostream& operator<< (std::ostream &out, const String &str) {
        // Since operator<< is a friend of the String class, we can access Point's members directly.
        out << str.content;

        return out; // return std::ostream so we can chain calls to operator<<
    }

    friend std::istream& operator>> (std::istream &in, String &str) {
        // Since operator>> is a friend of the String class, we can access Point's members directly.
        char* buf = new char[101];
        char* tmp = nullptr;
//        tmp[0] = '\0';
        char* mtp;
        long long size = 0;
        long long counter = 0;
        bool enter_pressed = false;
        size_t cpy_size = 0;
        char c = '\0';
        do {
            c = in.get();
            buf[counter++] = c;
            size++;
            if (counter == 100) {
                counter = 0;
                mtp = new char[size];
                if (size > 100)
                    memcpy(mtp, tmp, sizeof(char) * (size - 100));
                memcpy(mtp + (size - 100), buf, 100 * sizeof(char));
                if (tmp != nullptr) {
                    delete [] tmp;
                }
                tmp = new char[size+1];
                tmp[size] = '\0';
                memcpy(tmp, mtp, size * sizeof(char));
                delete [] mtp;
            }
            if (c != '\n' && enter_pressed) {
                enter_pressed = false;
            }
            if (c == '\n' && !enter_pressed) {
                enter_pressed = true;
                c = '\0';
            }
        } while (!(c == '\n' && enter_pressed) && !in.fail());
        buf[counter] = '\0';

        mtp = new char[size];
        memcpy(mtp, tmp, sizeof(char) * (size - counter));
        memcpy(mtp + (size - counter), buf, counter * sizeof(char));
        delete [] tmp;
        tmp = new char[size+1];
        memcpy(tmp, mtp, size * sizeof(char));
        delete [] mtp;
        tmp[size] = '\0';
        str = tmp;
        return in; // return std::istream so we can chain calls to operator>>
    }

    String operator+(String str) {
        char* tmp;
        long long size = String::size(str.getContent());
        long long new_size = size + this->size();
        tmp = new char[new_size];
        std::strcpy(tmp, this->content);
        std::strcpy(tmp+this->size(), str.getContent());

        String s(tmp);
        return s;
    }

    String operator=(String s) {
        this->_size = s.size();
        this->content = s.getContent();
        return *this;
    }

    String operator=(char *s) {
        this->_size = String::size(s);
        this->content = s;
        return *this;
    }

    char* getContent() {
        return this->content;
    }

    /**
     * Returns position of searched string
     * @param text
     * @param haystack
     * @return -1 if stroke was not found
     */
    static long long search(char *text, char *haystack, long long index = 0) {
        if (text[0] == '\0') {
            throw "Text can not be empty";
        }
        if (haystack[0] == '\0') {
            throw "Haystack can not be empty";
        }

        for (; text[index] != '\0'; ++index) {
            for (long long i = 0;; ++i) {
                if (haystack[i] != text[index]) {
                    // Break for closure` haystack ended
                    break;
                }
                // If haystack ends
                if (haystack[i] == '\0') {
                    // stroke was found at the position {index}
                    return index;
                }
            }
        }
        return -1;
    }

    static long long *searchAll(char* text, char* haystack) {
        long long position = 0;
        long long *items = new long long[10];
        long long *tmp;
        long long count = 0;
        for (; (position = String::search(text, haystack, position)) != -1;) {
            items[count] = position;
            ++count;
            if (count > 9) {
                tmp = new long long[count];
                std::memcpy(tmp, items, sizeof(long long*) * (count -1));
                delete[] items;
                items = new long long[count];
                std::memcpy(items, tmp, sizeof(long long*) * (count -1));
                delete[] tmp;
            }
        }
        if (count < 9) {
            tmp = new long long[count];
            std::memcpy(tmp, items, sizeof(long long*) * (count -1));
            delete[] items;
            items = new long long[count];
            std::memcpy(items, tmp, sizeof(long long*) * (count -1));
            delete[] tmp;
        }
        return items;
    }

    long long *searchAll(char* haystack) {
        return String::searchAll(this->content, haystack);
    }

    long long search(char *haystack) {
        return String::search(this->content, haystack);
    }

    static long long size(char *text) {
        long long size = 0;
        for (; text[size] != '\0'; ++size) {}
        return size;
    }

    long long size() {
        return this->_size;
    }

    long long length() {
        return this->_size;
    }



};


#endif //DATABASE_STRING_H
