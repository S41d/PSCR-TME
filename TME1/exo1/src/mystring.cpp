#include "mystring.hh"
#include <cstddef>
#include <cstring>

size_t pr::length(const char *str) {
    size_t i = 0;
    while (str[i]) i++;
    return i;
}

char * pr::newcopy(const char *str) {
    size_t len = length(str) + 1;
    char * str2 = new char[len];

    for (int i = 0; i < len; ++i) {
        str2[i] = str[i];
    }
    return str2;
}
