#ifndef PRINT_FUNCTIONS__237216e1_b6da_45ec_bced_fe6d10f199a6__HPP___
#define PRINT_FUNCTIONS__237216e1_b6da_45ec_bced_fe6d10f199a6__HPP___

#include <iostream>

void print(void);
void perr(void);

template <typename T> 
void print(const T& msg, const std::string& end="\n")
{
    std::cout << msg << end;
}

template <typename T>
void perr(const T& msg, const std::string& end="\n")
{
    std::cerr << msg << end;
}

#endif /* PRINT_FUNCTIONS__237216e1_b6da_45ec_bced_fe6d10f199a6__HPP___ */
