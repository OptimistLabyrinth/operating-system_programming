#ifndef PRINT_FUNCTIONS__1234__H___
#define PRINT_FUNCTIONS__1234__H___

#include <iostream>

void print(void);

template <typename T> 
void print(T msg, std::string end="\n")
{
    std::cout << msg << end;
}

#endif /* PRINT_FUNCTIONS__1234__H___ */
