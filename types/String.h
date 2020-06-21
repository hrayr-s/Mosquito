//
// Created by Hrayr on 5/29/2020.
//

#ifndef DATABASE_STRING_H
#define DATABASE_STRING_H

#include <iostream>
#include "structures.h"

class String {
private:
    char *content;
    long long _size = 0;
    long long actual_size = 100;
    char end_input_symbol = '\0';
public:
    String();

    String(char end_input_symbol);

    String(char *text);

    String(nullptr_t);

    String(const char *text);

    String(char *text, long long int size);

    friend std::ostream &operator<<(std::ostream &out, const String &str);

    friend std::istream &operator>>(std::istream &in, String &str);

    String operator=(String s);

    String operator=(String *s);

    String operator=(char *s);

    String operator=(nullptr_t s);

    bool operator!=(String *s);

    bool operator!=(String s);

    bool operator==(String s);

    bool operator==(String *s);

    bool operator==(const char *s);

    bool operator!=(nullptr_t s);

    String operator+(String str);

    String operator+(char *str);

    friend String operator+(const char *str, String &s);

    String operator+(const char *str);

    String operator+(char str);

    friend String operator+(char ch, String &str);

    String operator+=(char str);

    String operator+=(double number);

    String operator+=(const char *str);

    String operator+=(char *str);

    String operator+=(String str);

    String operator+(double number);

    friend String operator+(double number, String &str);

    String operator+(float number);

    friend String operator+(float number, String &str);

    String operator+(int number);

    friend String operator+(int number, String &str);

    String operator+(long long number);

    friend String operator+(long long number, String &str);

    char &operator[](int idx);

    char &operator[](long long idx);

    operator char *();

    operator const char *();

    operator long long();

    /**
     * Concatenation of two given string in given order` first str1 then str2
     * @param str
     * @param str2
     * @return
     */
    static char *concat(char *str, char *str2);

    char *getContent();

    /**
     * Returns position of searched string
     * @param text
     * @param haystack
     * @return -1 if stroke was not found
     */
    static long long search(String text, String haystack, long long index = 0, bool negative = false);

    static long long *searchAll(String text, String haystack, long long position = 0);

    static long long searchInArray(char **array_string, char *haystack);

    /**
     * Returns position of found text otherwise -1
     * @param array_string
     * @param haystack
     * @return
     */
    static long long searchInArray(String *array_string, char *haystack, long long pos = 0);

    long long searchInArray(String *array_string, long long pos = 0);

    long long *searchAll(char *haystack, long long pos = 0);

    long long search(char *haystack, long long pos = 0, bool negative = false);

    long long search(const char *haystack, long long pos = 0);

    static long long size(char *text);

    static long long size(const char *text);

    long long size();

    long long length();

    /**
     * Compare two given strings
     * @param str1
     * @param str2
     * @return
     */
    static bool compare(char *str1, char *str2);

    /**
     * Compare current string with given
     * @param str
     * @return
     */
    bool compare(char *str);

    /**
    * Checks for string to being a number
    * @return bool
    */
    bool isNumber();

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
    static String cut(String str, long long pos, long long length = 0);

    String cut(long long pos, long long length = 0);

    /**
     * Remove first and last space like symbols
     */
    String trim();

    /**
     * Manipulations with string characters cases
     *
     * @return
     */
    String toUpperCase();

    static String toUpperCase(char *s);

    String toLowerCase();

    static String toLowerCase(char *s);

    /**
     * Parsing to String from other types
     */

    static String parse(long long var);

    long long parseToInt();

    /*
     * Splits String by provided delimeter
     */
    String *split(String delimiter);

    static bool isSpace(char a);
};


#endif //DATABASE_STRING_H
