#include "../include/posix_timer_example.h"

pthread_mutex_t m;

void before_main(void) 
{
    printf("before main\n");
    pthread_mutex_init(&m, NULL);
}

void after_main(void) 
{
    printf("after main\n");
    pthread_mutex_destroy(&m);
}

typedef struct mData {
    timer_t tm;
} mData;

int main()
{
    int i = 0;

    start_clock();

    while(i < 5) {
        pause();
        printf("inside while-LOOP... %i\n", i);
        ++i;
    }

    return 0;
}

void start_clock(void)
{
    mData data;

    struct sigevent sigev;
    struct itimerspec itval, oitval;
    struct sigaction newact;

    sigemptyset(&newact.sa_mask);
    newact.sa_flags = SA_SIGINFO;
    newact.sa_sigaction = clock_handler;
    sigaction(SIGRTMIN, &newact, NULL);

    sigev.sigev_notify = SIGEV_SIGNAL;
    sigev.sigev_signo = SIGRTMIN;
    sigev.sigev_value.sival_ptr = &data;
    timer_create(CLOCK_REALTIME, &sigev, &(data.tm));

    itval.it_value.tv_sec = 0;
    itval.it_value.tv_nsec = (long)10 * (1000000L);
    itval.it_interval.tv_sec = 0;
    itval.it_interval.tv_nsec = (long)10 * (1000000L);
    timer_settime(data.tm, 0, &itval, &oitval);
}

void clock_handler(int sig, siginfo_t* info, void* context)
{
    int n_overrun;
    // n_overrun = timer_getoverrun(info);
    n_overrun = timer_getoverrun(context);

    if (n_overrun >= 1) {
        printf("clock overrun = %d\n", n_overrun);
        fflush(stdout);
    }

    // do some periodic things or wakeup a periodic thread on time. 
}
