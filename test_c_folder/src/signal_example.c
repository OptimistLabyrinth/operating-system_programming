#include "../include/signal_example.h"

static void sigcatcher(int);
void (*was)(int);

int main()
{
    if ((was = signal(SIGINT, sigcatcher)) == SIG_ERR) {
        perror("SIGINT error\n");
        exit(EXIT_FAILURE);
    }

    while(1) {
        pause();
    }

    return 0;
}

static void sigcatcher(int signo)
{
    switch (signo)
    {
        case SIGINT:
            printf("PID %d caught signal SIGINT.\n", getpid());
            signal(SIGINT, was);
            break;

        default:
            perror("something wrong\n");
            exit(EXIT_FAILURE);
    }
}


