#include "buffer.h"

int a = 3;
int b = 4;

int main(void)
{
    int c = 5;
    int d = 6;

    pid_t pid = fork();
    pid_t pid2 = -1;

    if (pid < 0) {
        perror("fork() Failed\n");
        exit(EXIT_FAILURE);
    }
    print_str("fork OK");

    if (pid != 0) {
        ++c;
        print_str("incr var 'c' in Parent");
    }
    else if ((pid2 = fork()) < 0) {
        perror("fork() in Child Failed\n");
        exit(EXIT_FAILURE);
    }
    
    if (c == 6)
    {   // PARENT Process
        int i=0;
        c = INT_MIN / 2;
        d = INT_MIN + 1;
        while (i < 100) {
            print_str("Parent is working...");
            printf("C: %d\tD: %d\n", c++, d++);
            ++i;
        }
    }
    else if (c == 5)
    {   // CHILD Process
        int i=0;
        while (i < 100) {
            print_str("Child is working...");
            printf("C: %d\tD: %d\n", c++, d++);
            ++i;
        }
    }

    return 0;
}