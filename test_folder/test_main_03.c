#include <stdio.h>
#include "test_main_01.c"

extern void print_str(const char*);
extern void print_int(int);

int main()
{
    print_str("inside 3rd main test file");
    print_int(00700);

    return 0;
}


