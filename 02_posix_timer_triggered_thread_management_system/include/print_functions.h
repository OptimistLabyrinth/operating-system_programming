#ifndef ___PRINT_FUNCTIONS__96a81bc8_488e_406b_95b6_f66f06387851__H___
#define ___PRINT_FUNCTIONS__96a81bc8_488e_406b_95b6_f66f06387851__H___

#include <iostream>

void print(void);

template <typename T> 
void print(T msg, std::string end="\n")
{
    std::cout << msg << end;
}

#endif /* ___PRINT_FUNCTIONS__96a81bc8_488e_406b_95b6_f66f06387851__H___ */
