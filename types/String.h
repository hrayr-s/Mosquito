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
    char end_input_symbol = '\0';
public:
    String() {
        content = new char[actual_size];
    }

    String(char end_input_symbol) {
        content = new char[actual_size];
        this->end_input_symbol = end_input_symbol;
    }

    String(char *text) {
        long long size = String::size(text);
        this->content = new char[size + 1];
        this->_size = size;
        std::strcpy(this->content, text);
        this->content[size] = '\0';
    }

    friend std::ostream &operator<<(std::ostream &out, const String &str) {
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
    friend std::istream &operator>>(std::istream &in, String &str) {
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
                    delete [] tmp;
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
        delete [] mtp;
        tmp[size] = '\0';
        str = tmp;
        return in; // return std::istream so we can chain calls to operator>>
    }

    String operator+(String str) {
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
     * Concatenation of two given string in given order` first str1 then str2
     * @param str
     * @param str2
     * @return
     */
    static char *concat(char *str, char *str2) {
        char *tmp;
        long long size = String::size(str);
        long long new_size = size + String::size(str2);
        tmp = new char[new_size + 1];
        std::strcpy(tmp, str);
        std::strcpy(tmp + size, str2);
        tmp[new_size] = '\0';
        return tmp;
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

    /**
     * Casting to char*
     * @return
     */
    operator char *() {
        char *tmp = new char[this->length() + 1];
        tmp[this->length()] = '\0';
        memcpy(tmp, this->getContent(), sizeof(char) * this->length());
        return tmp;
    }

    char *getContent() {
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

        for (; text[index] != '\0';) {
            for (long long i = 0;; ++i) {
                // If haystack ends
                if (haystack[i] == '\0') {
                    // stroke was found at the position {index}
                    return index;
                }

                if (haystack[i] != text[index++]) {
                    // Break for closure` haystack ended
                    break;
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
            std::memcpy(tmp, items, sizeof(long long *) * (count - 1));
            delete[] items;
            items = new long long[count];
            std::memcpy(items, tmp, sizeof(long long *) * (count - 1));
            delete[] tmp;
        }
        return items;
    }

    static long long searchInArray(char **array_string, char *haystack) {
        for (long long i = 0; array_string[i] != nullptr; ++i) {
            if (String::compare(array_string[i], haystack)) {
                return i;
            }
        }
        return -1;
    }

    /**
     * Returns position of found text otherwise -1
     * @param array_string
     * @param haystack
     * @return
     */
    static long long searchInArray(String *array_string, char *haystack, long long pos = 0) {
        for (long long i = pos; array_string[i] != nullptr; ++i) {
            if (array_string[i].compare(haystack)) {
                return i;
            }
        }
        return -1;
    }

    long long searchInArray(String *array_string, long long pos = 0) {
        for (long long i = pos; array_string[i] != nullptr; ++i) {
            if (array_string[i].compare(this->content)) {
                return i;
            }
        }
        return -1;
    }

    long long *searchAll(char *haystack) {
        return String::searchAll(this->content, haystack);
    }

    long long search(char *haystack, long long pos = 0) {
        return String::search(this->content, haystack, pos);
    }

    long long search(const char *haystack, long long pos = 0) {
        return String::search(this->content, (char *) haystack, pos);
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

    /**
     * Compare two given strings
     * @param str1
     * @param str2
     * @return
     */
    static bool compare(char *str1, char *str2) {
        size_t pos = 0;
        while (str1[pos] != '\0' && str2[pos] != '\0') {
            if (str1[pos] != str2[pos]) {
                return false;
            }
            pos++;
        }
        return !(str1[pos] != '\0' || str2[pos] != '\0');
    }

    /**
     * Compare current string with given
     * @param str
     * @return
     */
    bool compare(char *str) {
        return String::compare(this->content, str);
    }

    /**
     * Cuts given String by position and length
     * if given only pos parameter then it will be used as length
     * and started position to cut will be beginning of the string
     * Use -1 pos to cut from string end
     * @param str
     * @param pos
     * @param length
     * @return
     */
    static String cut(String str, long long pos, long long length = 0) {
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
            long long tm = str.length() + pos;
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

    String cut(long long pos, long long length = 0) {
        return String::cut(*this, pos, length);
    }

};


#endif //DATABASE_STRING_H
