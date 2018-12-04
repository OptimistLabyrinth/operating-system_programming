#include "../include/alarm_example.h"

int main()
{
    int i;

    char* rst = quickreply("login-name : ");

    if (rst == 0) {
        perror("Login ERROR\n");
        exit(EXIT_FAILURE);
    }

    printf("Login OK\n");

    for (i=0; i < 10; ++i) {
        printf("do something as a user... %i\n", i);
    }

    return 0;
}

const char* quickreply(const char* prompt)
{
    void(*was)(int);
    int ntries, i;
    char* answer;

    was = signal(SIGALRM, sig_catch);
    siginterrupt(SIGALRM, 1);

    for (ntries=0; ntries < MAXTRIES; ++ntries)
    {
        timed_out = FALSE;

        printf("\n%s", prompt);
        fflush(stdout);
        alarm(TIMEOUT);

        for (i=0; i < LINESIZE; ++i)
        {
            if ((myline[i] = getchar()) < 0)
                break;
            if (myline[i] == '\n') {
                myline[i] = 0;
                break;
            }
        }

        alarm(0);
        if (timed_out == FALSE)
            break;
    }

    answer = myline;

    signal(SIGALRM, was);
    
    return (ntries == MAXTRIES ? ((char*)0) : answer);
}

void sig_catch(int sig_no)
{
    timed_out = TRUE;
    putchar('\007');
    fflush(stdout);
    signal(SIGALRM, sig_catch);
}


