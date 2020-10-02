#pragma once
#include <iostream>

inline int getint()
{
    int result = 0;
    char c;
    while ((c = getchar()) == ' ' || c == '\n')
        ;
    while (isdigit(c))
    {
        result = result * 10 + c - '0';
        c = getchar();
    }
    return result;
}

inline unsigned int getuint()
{
    unsigned int result = 0;
    char c;
    while ((c = getchar()) == ' ' || c == '\n')
        ;
    while (isdigit(c))
    {
        result = result * 10 + c - '0';
        c = getchar();
    }
    return result;
}