#include "buffer.h"

void func_parent(const char* string)
{
    print_str("parent called this");
    print_str("parameter: ");
    print_str(string);
}

void func_child(const char* string)
{
    print_str("child called this ~ ");
    print_str("parameter: ");
    print_str(string);
}

int main()
{
    print_str("*** Main Starts Here ***");

    int i = 0;
    print_str("int in stack 'i'");
    int* i_ptr = (int*) malloc(sizeof(int));
    print_str("int in heap 'i_ptr'");

    *i_ptr = 5;
    print_int(*i_ptr);
    print_str("let's do it");
    free(i_ptr);

    pid_t pid = fork();
    print_str("fork() here ! ! !");

    if (pid < 0) {
        perror("fork() failed\n");
        exit(EXIT_FAILURE);
    }
    else if (pid != 0) 
    {
        func_parent("aaaaaaaaaa apartment!");
    }
    else
    {
        func_child("z z z z z z Zebra?");
        exit(EXIT_SUCCESS);
    }

    wait(0);
    print_str("*** Main Returns Here ***");

    return 0;
}