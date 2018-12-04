#ifndef ___PRINT_FUNCTIONS__9f76bbe8_1c62_4912_b540_d7b1355ae6e9__HPP___
#define ___PRINT_FUNCTIONS__9f76bbe8_1c62_4912_b540_d7b1355ae6e9__HPP___

#include <iostream>

void print(void);

template <typename T> 
void print(const T& msg, const std::string& end="\n")
{
    std::cout << msg << end;
}

#endif /* ___PRINT_FUNCTIONS__9f76bbe8_1c62_4912_b540_d7b1355ae6e9__HPP___ */