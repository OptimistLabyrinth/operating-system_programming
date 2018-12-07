#ifndef PRINT__2__HPP___
#define PRINT__2__HPP___

#include <iostream>

void print(void);

template <typename T>
void print(T msg)
{
    std::cout << msg << "\n";
}

#endif /* PRINT__2__HPP___ */