#include "buffer.h"

#define SZ 5

int main(void) 
{
    pid_t p[SZ] = {0};
    pid_t pid;
    p[0] = 1;
    unsigned int idx = 0;

    print_str("\t\tMain Begins...");
    print_int(getpid());

    pid = fork();
    p[++idx] = pid;
    ++(p[0]);
    printf("%i - value of p1: %i\n", getpid(), p[1]);

    if (p[idx] != 0) {
        printf("%i - parent process after fork() \n", getpid());

        p[++idx] = fork();
        ++(p[0]);
        printf("%i - value of p2: %i\n", getpid(), p[2]);

        if (p[idx] != 0) {
            printf("%i - parent process after fork()fork()\n", getpid());

            p[++idx] = fork();
            ++(p[0]);
            printf("%i - value of p3: %i\n", getpid(), p[3]);

            if (p[idx] != 0) {
                printf("%i - parent process after fork()fork()fork()\n", getpid());

                p[++idx] = fork();
                ++(p[0]);
                printf("%i - value of p3: %i\n", getpid(), p[3]);

                if (p[idx] != 0) {
                    printf("%i - parent process after fork()fork()fork()fork()\n", getpid());
                }
                else {
                    printf("%i - child %d process\n", getpid(), idx);
                    int i;
                    for (i=1; i < idx; ++i)
                        p[i] = 0;
                }
            }
            else {
                printf("%i - child %d process\n", getpid(), idx);
                int i;
                for (i=1; i < idx; ++i)
                    p[i] = 0;
            }
        }
        else {
            printf("%i - child %d process\n", getpid(), idx);
            int i;
            for (i=1; i < idx; ++i)
                p[i] = 0;
        }
    }
    else {
        printf("%i - child %d process\n", getpid(), idx);
        int i;
    }

    if (p[1] != 0) {
        printf("Total Process Number: %d\n", p[0]);

        int i = 1;
        while (i <= idx) {
            if (p[i++] != 0 ) {
                wait(0);
                printf("child %d joined to parent :)\n", i-1);
                --(p[0]);
            }
        }
    }

    if (p[1] != 0)
        printf("Total Process Number: %d\n", p[0]);

    printf("\t\t%i - Main Ends!\n", getpid());

    return 0;
}


