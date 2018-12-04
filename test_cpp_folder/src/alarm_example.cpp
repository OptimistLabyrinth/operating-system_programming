#include "../include/alarm_example.h"

std::string quickreply(std::string prompt)
{
    void(*was)(int);
    int ntries;
    std::string answer;

    was = signal(SIGALRM, sig_catch);
    siginterrupt(SIGALRM, 1);

    for (ntries=0; ntries < MAXTRIES; ++ntries)
    {
        timed_out = false;
        print(prompt);
        std::cout << std::flush;
        alarm(TIMEOUT);

        for (int i=0; i < LINESIZE; ++i)
        {
            if ((myline[i] = getchar()) < 0) {
                perror("getchar() error");
                break;
            }
            if (myline[i] == '\n') {
                myline[i] = 0;
                break;
            }
        }

        alarm(0);
        if (!timed_out)
            break;
    }

    answer = myline;
    
    signal(SIGALRM, was);
    return (ntries == MAXTRIES ? ((char*)0) : answer);
}

void sig_catch(int sig_no)
{
    timed_out = true;
    putchar(CTRL_G);
    std::cout << std::flush;
    signal(SIGALRM, sig_catch);
}

int main()
{
    quickreply("login-name: ");

    return 0;
}
