//
// Created by Hrayr on 5/29/2020.
//

#include <iostream>
#include "String.h"
#include "../ArrayHelper.h"
#include <climits>

#define d_LENGTH 16
#define f_LENGTH 8
#define i_LENGTH 11
#define ll_LENGTH 20

String::String() {
    this->content = new char[this->actual_size];
    this->content[0] = '\0';
    this->_size = 0;
}

String::String(char end_input_symbol) {
    this->content = new char[this->actual_size];
    this->end_input_symbol = end_input_symbol;
}

String::String(char *text) {
    if (text != nullptr) {
        long long size = String::size(text);
        this->content = new char[size + 1];
        this->_size = size;
        memcpy(this->content, text, sizeof(char) * size);
        this->content[size] = '\0';
    } else {
        this->content = nullptr;
        this->_size = NULL;
    }
}

String::String(nullptr_t s) {
    this->content = nullptr;
    this->_size = NULL;
}

String::String(const char *text) {
    if (text != nullptr) {
        long long size = String::size(text);
        this->content = new char[size + 1];
        this->_size = size;
        memcpy(this->content, text, sizeof(char) * size);
        this->content[size] = '\0';
    } else {
        this->content = nullptr;
        this->_size = NULL;
    }
}

String::String(char *text, long long int size) {
    if (text != nullptr) {
        this->content = new char[size + 1];
        this->_size = size;
        memcpy(this->content, text, sizeof(char) * size);
        this->content[size] = '\0';
    } else {
        this->content = nullptr;
        this->_size = NULL;
    }
}

/** Overload operators */

std::ostream &operator<<(std::ostream &out, const String &str) {
    // Since operator<< is a friend of the String class, we can access Point's members directly.
    if (str.content != nullptr) {
        out << str.content;
    }

    return out; // return std::ostream so we can chain calls to operator<<
}

/**
 * Input multiline strings
 * @param in
 * @param str
 * @return
 */
std::istream &operator>>(std::istream &in, String &str) {
    // Since operator>> is a friend of the String class, we can access Point's members directly.
    char *buf = new char[101];
    char *tmp = nullptr;
    char *mtp;
    long long size = 0;
    long long counter = 0;
    bool enter_pressed = false;
    char c;
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
    this->content = new char[s.length() + 1];
    memcpy(this->content, s.getContent(), s.length() + 1);
//    this->content = s.getContent();
    return *this;
}

String String::operator=(String *s) {
    this->_size = s->size();
    this->content = new char[s->size() + 1];
    memcpy(this->content, s->content, s->size());
    this->content[this->_size] = '\0';
    return *this;
}

String String::operator=(char *s) {
    if (s == nullptr) {
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

bool String::operator!=(String *s) {
    return s->getContent() != this->content;
}

bool String::operator!=(String s) {
    return s.getContent() != this->content;
}

bool String::operator==(String s) {
    return this->compare(s.getContent());
}

bool String::operator==(String *s) {
    return this->compare(s->getContent());
}

bool String::operator==(const char *s) {
    return this->compare((char *) s);
}

bool String::operator!=(nullptr_t s) {
    return s != this->content;
}

String String::operator+(String str) {
    char *tmp;
    long long size = str.length();
    long long new_size = size + this->size();
    tmp = new char[new_size + 1];
    std::strcpy(tmp, this->content);
    std::strcpy(tmp + this->size(), str.content);

    String s(tmp);
    delete[] tmp;
    return s;
}

String String::operator+(char *str) {
    char *tmp;
    long long size = String::size(str);
    long long new_size = size + this->size();
    tmp = new char[new_size + 1];
    std::strcpy(tmp, this->content);
    std::strcpy(tmp + this->size(), str);

    String s(tmp);
    delete[] tmp;
    return s;
}

String String::operator+(const char *str) {
    char *tmp;
    long long size = String::size((char *) str);
    long long new_size = size + this->size();
    tmp = new char[new_size + 1];
    std::strcpy(tmp, this->content);
    std::strcpy(tmp + this->size(), str);

    String s(tmp);
    delete[] tmp;
    return s;
}

String operator+(const char *str, String &s) {
    char *tmp;
    long long size = String::size((char *) str);
    long long new_size = size + s.size();
    tmp = new char[new_size + 1];
    std::strcpy(tmp, s.content);
    std::strcpy(tmp + s.size(), str);

    String raw(tmp);
    delete[] tmp;
    return raw;
}

String String::operator+(char ch) {
    char *tmp;
    long long new_size = 1 + this->size();
    tmp = new char[new_size + 1];
    if (this->size() >= 0) {
        std::strcpy(tmp, this->content);
    }
    tmp[new_size - 1] = ch;
    tmp[new_size] = '\0';
    String s(tmp);
    return s;
}

String operator+(char ch, String &str) {
    char *tmp;
    long long new_size = 1 + str.size();
    tmp = new char[new_size + 1];
    std::strcpy(tmp, str.content);
    tmp[new_size - 1] = ch;
    String s(tmp);
    delete[] tmp;
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

char &String::operator[](int idx) {
    if (idx > this->length() || idx < -1) {
        throw "Unknown position of a String";
    }
    if (this->content == nullptr) {
        *this = new String;
    }
    // If adding an Index
    if (idx == this->length() || idx == -1) {
        idx = this->length();
        *this = *this + 'x';
        this->content[idx] = '\0';
    }
    return this->content[idx];
}

char &String::operator[](long long idx) {
    if (idx > this->length() || idx < -1) {
        throw "Unknown position of a String";
    }
    if (this->content == nullptr) {
        *this = new String;
    }
    // If adding an Index
    if (idx == this->length() || idx == -1) {
        idx = this->length();
        *this = *this + '\0';
    }
    return this->content[idx];
}

String String::operator+=(char ch) {
    *this = *this + ch;
    return *this;
}

String String::operator+=(double number) {
    *this = *this + number;
    return *this;
}

String String::operator+=(const char *ch) {
    *this = *this + ch;
    return *this;
}

String String::operator+=(char *ch) {
    *this = *this + ch;
    return *this;
}

String String::operator+=(String ch) {
    *this = *this + ch;
    return *this;
}

String String::operator+(double number) {
    char *sum = new char[this->length() + d_LENGTH + 1];
    sprintf(sum, "%s%.*g", this->content, d_LENGTH, number);
    String s(sum);
    delete[] sum;
    return s;
}

String operator+(double number, String &str) {
    char *sum = new char[str.length() + d_LENGTH + 1];
    sprintf(sum, "%s%.*g", str.content, d_LENGTH, number);
    String s(sum);
    delete[] sum;
    return s;
}

String String::operator+(float number) {
    char *sum = new char[this->length() + f_LENGTH + 1];
    sprintf(sum, "%s%.*g", this->content, f_LENGTH, number);
    String s(sum);
    delete[] sum;
    return s;
}

String operator+(float number, String &str) {
    char *sum = new char[str.length() + f_LENGTH + 1];
    sprintf(sum, "%s%.*g", str.content, f_LENGTH, number);
    String s(sum);
    delete[] sum;
    return s;
}

String String::operator+(int number) {
    char *sum = new char[this->length() + i_LENGTH + 1];
    sprintf(sum, "%s%d", this->content, number);
    String s(sum);
    delete[] sum;
    return s;
}

String operator+(int number, String &str) {
    char *sum = new char[str.length() + i_LENGTH + 1];
    sprintf(sum, "%s%d", str.content, number);
    String s(sum);
    delete[] sum;
    return s;
}

String String::operator+(long long number) {
    char *sum = new char[this->length() + ll_LENGTH + 1];
    sprintf(sum, "%s%lld", this->content, number);
    String s(sum);
    delete[] sum;
    return s;
}

String operator+(long long number, String &str) {
    char *sum = new char[str.length() + ll_LENGTH + 1];
    sprintf(sum, "%s%lld", str.content, number);
    String s(sum);
    delete[] sum;
    return s;
}

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

char *String::getContent() {
    return this->content;
}

long long String::search(String text, String haystack, long long index, bool negative) {
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

long long *String::searchAll(String text, String haystack, long long position) {
    long long *items = new long long[10];
    items[9] = NULL;
    long long count = 0;
    for (; (position = String::search(text, haystack, position)) != -1;) {
        items[count] = position;
        ++count;
        if (count >= 9) {
            ArrayHelper::resize(items, count + 1);
        }
    }
    if (count == 0) {
        items = nullptr;
    } else if (count < 9) {
        items[count] = NULL;
        ArrayHelper::resize(items, count);
    }
    return items;
}

long long String::searchInArray(String *array_string, char *haystack, long long pos) {
    for (long long i = pos; array_string[i] != nullptr; ++i) {
        if (array_string[i].compare(haystack)) {
            return i;
        }
    }
    return -1;
}

long long String::searchInArray(String *array_string, long long pos) {
    for (long long i = pos; array_string[i] != nullptr; ++i) {
        if (array_string[i].compare(this->content)) {
            return i;
        }
    }
    return -1;
}

long long *String::searchAll(char *haystack, long long pos) {
    return String::searchAll(*this, haystack, pos);
}

long long String::search(char *haystack, long long pos, bool negative) {
    return String::search(*this, String(haystack), pos, negative);
}

long long String::search(const char *haystack, long long pos) {
    return String::search(*this, String(haystack), pos);
}

long long String::size(char *text) {
    long long size = 0;
    if (text == nullptr) {
        return 0;
    }
    for (; text[size] != '\0'; ++size) {}
    return size;
}

long long String::size(const char *text) {
    long long size = 0;
    if (text == nullptr) {
        return 0;
    }
    for (; text[size] != '\0'; ++size) {}
    return size;
}

long long String::size() {
    return this->_size;
}

long long String::length() {
    return this->_size;
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

bool String::compare(char *str) {
    return String::compare(this->content, str);
}

bool String::isNumber() {
    bool has_dot = false;
    for (long long i = 0; i < this->length(); ++i) {
        if ((this->content[i] >= '0') || (this->content[i] <= '9')) {
            continue;
        }
        if ((this->content[i] == '.') || (this->content[i] == ',')) {
            if (has_dot) {
                return false;
            } else {
                has_dot = true;
                continue;
            }
        }
        return false;
    }
    return true;
}

String String::cut(String str, long long pos, long long length) {
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
    memcpy(tmp, str.content + pos, length * sizeof(char));
//    for (long long index = pos, i = 0; index < pos + length; ++i, ++index) {
//        tmp[i] = str.getContent()[index];
//    }
    tmp[length] = '\0';
    String s(tmp);
//    delete [] tmp;
    return s;
}

String String::cut(long long pos, long long length) {
    String str = String::cut(*this, pos, length);
    return str;
}

long long String::searchInArray(char **array_string, char *haystack) {
    for (long long i = 0; array_string[i] != nullptr; ++i) {
        if (String::compare(array_string[i], haystack)) {
            return i;
        }
    }
    return -1;
}


String String::trim() {
    long long begin = 0, end = this->length();
    for (long long i = 0; i < this->length(); ++i) {
        if (this->content[i] == ' ' || this->content[i] == '\n' || this->content[i] == '\t' ||
            this->content[i] == '\r') {
            continue;
        }
        begin = i;
        break;
    }

    for (long long i = this->length() - 1; i > begin; --i) {
        if (this->content[i] == ' ' || this->content[i] == '\n' || this->content[i] == '\t' ||
            this->content[i] == '\r') {
            continue;
        }
        end = i + 1;
        break;
    }
    String s = String::cut(*this, begin, end - begin);
    return s;
}

String::operator long long() {
    long long tmp = 0;
    for (long long i = 0; i < this->length(); ++i) {
        tmp = tmp * 10 + (this->content[i] - '0');
    }
    return tmp;
}

String String::toUpperCase() {
    String str(this->content);
    char diff = 'A' - 'a';
    for (long long i = 0; i < this->length(); ++i) {
        if (str[i] >= 'a' && str[i] < 'z' + 1) {
            str[i] = str[i] + diff;
        }
    }
    return str;
}

String String::toUpperCase(char *str) {
    String s(str);
    return s.toUpperCase();
}

String String::toLowerCase() {
    String str(this->content);
    char diff = 'A' - 'a';
    for (long long i = 0; i < this->length(); ++i) {
        if (str[i] < 'Z' + 1) {
            if ('A' >= str[i]) {
                str[i] = str[i] - diff;
            }
        }
    }
    return str;
}

String String::toLowerCase(char *str) {
    String s(str);
    return s.toLowerCase();
}

String String::parse(long long int var) {
    char *sum = new char[ll_LENGTH + 1];
    sprintf(sum, "%lld", var);
    String s(sum);
    delete[] sum;
    return s;
}

long long String::parseToInt() {
    long long val = 0;
    int success = sscanf(this->content, "%lld", &val);
    if (success >= 1) return val;
    return NULL;
}

String *String::split(String delimiter) {
    long long *positions = this->searchAll(delimiter);
    long long parts_count;
    String *parts;
    if (positions != nullptr) {
        parts_count = ArrayHelper::count(positions) + 1;
        parts = new String[parts_count + 1];
        parts[parts_count] = nullptr;
        parts[0] = this->cut(0, positions[0] - delimiter.length());
        long long i = 1;
        for (; positions[i] != NULL; ++i) {
            parts[i] = this->cut(positions[i - 1], positions[i] - delimiter.length() - positions[i - 1]);
        }
        long long posit = positions[i - 1];
        long long length = this->length() - positions[i - 1];
        parts[i] = this->cut(posit, length);
    } else {
        positions = new long long[2];
        positions[0] = 0;
        positions[1] = NULL;
        parts = new String[2];
        parts[0] = new String(this->content);
        parts[1] = nullptr;
    }

    return parts;
}

bool String::isSpace(char a) {
    switch (a) {
        case ' ':
        case '\t':
        case '\r':
        case '\n':
        case '\f':
        case '\v':
            return true;
        default:
            return false;
    }
    return false;
}
