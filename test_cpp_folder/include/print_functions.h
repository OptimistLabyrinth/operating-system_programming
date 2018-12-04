#ifndef __TMPLT_H__
#define __TMPLT_H__

#include <iostream>

void print(void);

template <typename T> 
void print(T msg, std::string end="\n")
{
    std::cout << msg << end;
}

#endif /* __TMPLT_H__ */
