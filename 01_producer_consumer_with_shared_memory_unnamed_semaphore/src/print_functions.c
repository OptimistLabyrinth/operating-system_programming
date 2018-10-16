#include "../include/print_functions.h"

/* prints only a new line */
void println(void) 
{
    printf("\n");
}

void print_str(const char * string) 
{ 
    printf("%s\n", string); 
}

void print_int(int i) 
{ 
    printf("%d\n", i); 
}
