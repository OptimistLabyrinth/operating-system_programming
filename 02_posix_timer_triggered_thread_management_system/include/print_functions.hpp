#ifndef PRINT_FUNCTIONS__96a81bc8_488e_406b_95b6_f66f06387851__H___
#define PRINT_FUNCTIONS__96a81bc8_488e_406b_95b6_f66f06387851__H___

#include <iostream>

void print(void);

template <typename T> 
void print(const T& msg, const std::string& end="\n")
{
    std::cout << msg << end;
}

#endif /* PRINT_FUNCTIONS__96a81bc8_488e_406b_95b6_f66f06387851__H___ */
