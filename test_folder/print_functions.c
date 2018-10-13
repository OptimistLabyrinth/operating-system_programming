#include "print_functions.h"

// static inline void print_str(const char*) __attribute__((always_inline));
// static inline void print_int(int) __attribute__((always_inline));

void print_str(const char * string) 
{ 
    printf("%s\n", string); 
}

void print_int(int i)
{ 
    printf("%d\n", i); 
}

// int main(void)
// {
//     print_int(1);
//     print_str("Go! Go! Go!");

//     return 0;
// }


