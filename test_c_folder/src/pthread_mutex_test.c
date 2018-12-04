#include "../include/pthread_mutex_test.h"

#define NUM_THREADS 20

pthread_mutex_t m_mutex;
pthread_cond_t m_cond;

typedef struct Args {
    pthread_t _t;
    int* i_ptr;
} Args;

void* print_hello(void* threadid)
{
    pthread_mutex_lock(&m_mutex);
    int tid = (int)threadid;
    int rv = tid;
    for (int i=0; i < threadid; ++i) {
        printf("%c", 'a' + threadid - 1);
    }

    printf(" %d: Hello World!\n", tid);

    for (int i=0; i < 3; ++i) {
        print_int(rv);
        rv = 100*rv + tid;
    }
    print_int(rv);

    pthread_mutex_unlock(&m_mutex);
    pthread_exit((void*)rv);
}

void _main_02(void)
{
    pthread_mutex_init(&m_mutex, NULL);
    pthread_cond_init(&m_cond, NULL);

    pthread_t threads[NUM_THREADS + 1];
    void* rv;
    int t;

    for (t=1; t <= NUM_THREADS; ++t)
    {
        printf("Creating a new Thread %d\n", t);
        pthread_create(&(threads[t]), NULL, print_hello, (void*) t);
    }

    for (t=1; t <= NUM_THREADS; ++t)
    {
        pthread_join(threads[t], &rv);
        printf("Joined thread %d - %d\n", t, (int)rv);
    }

    pthread_cond_destroy(&m_cond);
    pthread_mutex_destroy(&m_mutex);

    pthread_exit(NULL);
}

int main()
{
    // _main_01();
    _main_02();

    return 0;
}










void simple_test(void)
{
    int i;
    pthread_t p[NUM];
    struct arg_struct data[NUM];

    for (i=1; i <= NUM; ++i) {
        data[i].index = i;
        data[i].string = sentences[i];
        pthread_create(&(p[i]), NULL, funcXXX, &(data[i]));
    }


}

void* funcXXX(void* data)
{
    for (int i=0; i < LOOP; ++i)
    {
        
    }

    return NULL;
}










const size_t NUMTHREADS = 20;
int done = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* thread_entry(void* id)
{
    const int myid = (long)id;
    const int workloops = 5;
    for (int i=0; i < workloops; ++i)
    {
        printf("[thread %d] working (%d%d)\n", myid, i, workloops);
        sleep(1);
    }

    pthread_mutex_lock(&mutex);
    ++done;
    printf("[thread %d] done is now %d. Signalling cond.\n", myid, done);

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void _main_01(void)
{
    int t;
    puts("[thread main] starting...");

    pthread_t threads[NUMTHREADS];

    for (t=0; t < NUMTHREADS; ++t)
    {
        pthread_create(&threads[t], NULL, thread_entry, (void*)(long)t);
    }
    pthread_mutex_lock(&mutex);

    while(--t > 1)
    {
        printf("[thread main] done is %d which is < %d so waiting on cond\n"
                , done, (int)NUMTHREADS);
        pthread_cond_wait(&cond, &mutex);
        puts("[thread main] wake - cond was signalled");
    }

    printf("[thread main] done == %d so everyone is done\n", (int)NUMTHREADS);

    pthread_mutex_unlock(&mutex);
}
