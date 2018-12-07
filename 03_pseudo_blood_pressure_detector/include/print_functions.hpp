#ifndef PRINT_FUNCTIONS__2b784ca3_a7cd_4e18_ad2c_791129508144__H___
#define PRINT_FUNCTIONS__2b784ca3_a7cd_4e18_ad2c_791129508144__H___

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

#endif /* PRINT_FUNCTIONS__2b784ca3_a7cd_4e18_ad2c_791129508144__H___ */