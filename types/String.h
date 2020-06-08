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
    String();

    String(char end_input_symbol);

    String(char *text);

    friend std::ostream &operator<<(std::ostream &out, const String &str);

    friend std::istream &operator>>(std::istream &in, String &str);

    String operator=(String s);

    String operator=(char *s);

    String operator=(nullptr_t s);

    bool operator!=(String *s);

    bool operator!=(String s);

    bool operator!=(nullptr_t s);

    String operator+(String str);

    const char operator[](std::size_t idx) const;

    explicit operator char *();

    explicit operator const char *();

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

    static long long *searchAll(char *text, char *haystack, long long position = 0);

    static long long searchInArray(char **array_string, char *haystack);

    /**
     * Returns position of found text otherwise -1
     * @param array_string
     * @param haystack
     * @return
     */
    static long long searchInArray(String **array_string, char *haystack, long long pos = 0);

    long long searchInArray(String **array_string, long long pos = 0);

    long long *searchAll(char *haystack, long long pos = 0);

    long long search(char *haystack, long long pos = 0, bool negative = false);

    long long search(const char *haystack, long long pos = 0);

    static long long size(char *text);

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

};


#endif //DATABASE_STRING_H
