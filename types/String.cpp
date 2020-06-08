//
// Created by Hrayr on 5/29/2020.
//

class ArrayHelper;

#include <iostream>
#include "../ArrayHelper.h"
#include "String.h"

long long _size = 0;
long long actual_size = 100;
char end_input_symbol = '\0';

String::String() {
    content = new char[actual_size];
}

String::String(char end_input_symbol) {
    content = new char[actual_size];
    this->end_input_symbol = end_input_symbol;
}

String::String(char *text) {
    if (text != NULL) {
        long long size = String::size(text);
        this->content = new char[size + 1];
        this->_size = size;
        std::strcpy(this->content, text);
        this->content[size] = '\0';
    } else {
        this->content = nullptr;
        this->_size = NULL;
    }
}

/** Overload operators */

friend std::ostream &String::operator<<(std::ostream &out, const String &str) {
    // Since operator<< is a friend of the String class, we can access Point's members directly.
    out << str.content;

    return out; // return std::ostream so we can chain calls to operator<<
}

/**
 * Input multiline strings
 * @param in
 * @param str
 * @return
 */
friend std::istream &String::operator>>(std::istream &in, String &str) {
    // Since operator>> is a friend of the String class, we can access Point's members directly.
    char *buf = new char[101];
    char *tmp = nullptr;
    char *mtp;
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
                delete[] tmp;
            }
            tmp = new char[size + 1];
            tmp[size] = '\0';
            memcpy(tmp, mtp, size * sizeof(char));
            delete[] mtp;
        }
        if (c != '\n' && enter_pressed) {
            enter_pressed = false;
        }
        if (c == '\n' && !enter_pressed) {
            enter_pressed = true;
            c = '\0';
        }
        if (str.end_input_symbol != '\0' && c == str.end_input_symbol) {
            break;
        }
    } while (!(c == '\n' && enter_pressed) && !in.fail());
    buf[counter] = '\0';

    mtp = new char[size];
    memcpy(mtp, tmp, sizeof(char) * (size - counter));
    memcpy(mtp + (size - counter), buf, counter * sizeof(char));
    delete[] tmp;
    tmp = new char[size + 1];
    memcpy(tmp, mtp, size * sizeof(char));
    delete[] mtp;
    tmp[size] = '\0';
    str = tmp;
    return in; // return std::istream so we can chain calls to operator>>
}

String String::operator=(String s) {
    this->_size = s.size();
    this->content = s.getContent();
    return *this;
}

String String::operator=(char *s) {
    if (s == NULL) {
        return nullptr;
    }
    this->_size = String::size(s);
    this->content = s;
    return *this;
}

String String::operator=(nullptr_t s) {
    this->_size = NULL;
    this->content = nullptr;
    return *this;
}

bool String::operator!=(String s) {
    return s.getContent() == this->content;
}

bool String::operator!=(nullptr_t s) {
    return s == this->content;
}

String String::operator+(String str) {
    char *tmp;
    long long size = String::size(str);
    long long new_size = size + this->size();
    tmp = new char[new_size + 1];
    std::strcpy(tmp, this->content);
    std::strcpy(tmp + this->size(), str);

    String s(tmp);
    return s;
}

/**
 * Casting to char*
 * @return
 */
String::operator char *() {
    char *tmp = new char[this->length() + 1];
    tmp[this->length()] = '\0';
    memcpy(tmp, this->getContent(), sizeof(char) * this->length());
    return tmp;
}

String::operator const char *() {
    char *tmp = new char[this->length() + 1];
    tmp[this->length()] = '\0';
    memcpy(tmp, this->getContent(), sizeof(char) * this->length());
    return (const char *) tmp;
}

const char String::operator[](std::size_t idx) const { return this->content[idx]; }

/** End Operators Overloading */

char *String::concat(char *str, char *str2) {
    char *tmp;
    long long size = String::size(str);
    long long new_size = size + String::size(str2);
    tmp = new char[new_size + 1];
    std::strcpy(tmp, str);
    std::strcpy(tmp + size, str2);
    tmp[new_size] = '\0';
    return tmp;
}

long long String::search(String text, String haystack, long long index = 0, bool negative = false) {
    if (text.getContent()[0] == '\0') {
        throw "Text can not be empty";
    }
    if (haystack[0] == '\0') {
        throw "Haystack can not be empty";
    }
    if (negative) {
        if (index >= 0) {
            index = text.length() - index;
        } else {
            index = text.length() + index;
        }
        for (long long k = text.length() - 1; k >= 0; --k) {
            for (long long i = haystack.length() - 1;; --i) {
                // If haystack ends
                if (i == -1) {
                    // stroke was found at the position {index}
                    return index;
                }

                if (haystack.getContent()[i] != text.getContent()[index--]) {
                    // Break for closure` haystack ended
                    break;
                }
            }
        }
    } else {
        for (; text.getContent()[index] != '\0';) {
            for (long long i = 0;; ++i) {
                // If haystack ends
                if (haystack.getContent()[i] == '\0') {
                    // stroke that has been found ends at the position {index}
                    return index;
                }

                if (haystack.getContent()[i] != text.getContent()[index++]) {
                    // Break for closure` haystack ended
                    break;
                }
            }
        }
    }
    return -1;
}

long long *String::searchAll(char *text, char *haystack, long long position = 0) {
    long long *items = new long long[10];
    long long *tmp;
    long long count = 0;
    for (; (position = String::search(text, haystack, position)) != -1;) {
        items[count] = position;
        ++count;
        if (count > 9) {
            ArrayHelper::resize(items, count + 1);
//                tmp = new long long[count];
//                std::memcpy(tmp, items, sizeof(long long) * count);
//                delete[] items;
//                items = new long long[count+1];
//                std::memcpy(items, tmp, sizeof(long long) * count);
//                delete[] tmp;
        }
    }
    if (count < 9) {
        items[count] = NULL;
        ArrayHelper::resize(items, count + 1);
//            tmp = new long long[count];
//            std::memcpy(tmp, items, sizeof(long long) * count);
//            delete[] items;
//            items = new long long[count+1];
//            std::memcpy(items, tmp, sizeof(long long) * count);
//            delete[] tmp;
    }
    return items;
}

long long String::searchInArray(String *array_string, char *haystack, long long pos = 0) {
    for (long long i = pos; array_string[i] != nullptr; ++i) {
        if (array_string[i].compare(haystack)) {
            return i;
        }
    }
    return -1;
}

long long String::searchInArray(String *array_string, long long pos = 0) {
    for (long long i = pos; array_string[i] != nullptr; ++i) {
        if (array_string[i].compare(this->content)) {
            return i;
        }
    }
    return -1;
}

bool String::compare(char *str1, char *str2) {
    size_t pos = 0;
    while (str1[pos] != '\0' && str2[pos] != '\0') {
        if (str1[pos] != str2[pos]) {
            return false;
        }
        pos++;
    }
    return !(str1[pos] != '\0' || str2[pos] != '\0');
}

String String::cut(String str, long long pos, long long length = 0) {
    char *tmp;

    // Calculate for positive position
    if (pos >= 0) {
        // Calculate for negative length
        if (length < 0) {
            if (length + pos < 0) {
                return nullptr;
            }
            pos = length + pos;
            length = length * (-1); // set to positive
        }
        // Calculates for none length given
        if (length == 0) {
            length = pos;
            pos = 0;
        }
    } else {
        // temporary pos
        if (length < 0) {
            // Calculates position
            pos = str.length() + pos + length;
            // After calcs position should not be lower than 0
            if (pos < 0) {
                return nullptr;
            }
            length = length * (-1);
        } else {
            // if length is zero so it wasn't given
            if (length == 0) {
                // Calculate by given position
                length = pos * (-1);
            }
            pos = str.length() + pos;
        }
    }

    // Requested position-length can't reach the str length
    if (pos + length > str.length()) {
        return nullptr;
    }

    tmp = new char[length + 1];
    for (long long index = pos, i = 0; index < pos + length; ++i, ++index) {
        tmp[i] = str.getContent()[index];
    }
    tmp[length] = '\0';
    return tmp;
}

long long String::searchInArray(char **array_string, char *haystack) {
    for (long long i = 0; array_string[i] != nullptr; ++i) {
        if (String::compare(array_string[i], haystack)) {
            return i;
        }
    }
    return -1;
}