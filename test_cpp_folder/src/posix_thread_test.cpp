#include "../include/posix_thread_test.h"

#define NUM_OF_THREADS 2

pthread_mutex_t g_mutex;
pthread_cond_t g_cond[NUM_OF_THREADS];

pthread_t arr_threads[NUM_OF_THREADS];

void init_vars(void)
{
    std::cout << "calling init-var( )" << std::endl;
    pthread_mutex_init(&g_mutex, nullptr);
    for (auto& x : g_cond)
    {
        pthread_cond_init(&x, nullptr);
    }
}

void destroy_vars(void)
{
    std::cout << "calling destroy_vars( )" << std::endl;
    pthread_mutex_destroy(&g_mutex);
    for (auto& x : g_cond)
    {
        pthread_cond_destroy(&x);
    }
}

void execution(void)
{
    int turn = 0;

    std::cout << "calling execution( )" << std::endl;
    pthread_create(&arr_threads[0], nullptr, incr, reinterpret_cast<void*>(&turn));
    pthread_create(&arr_threads[1], nullptr, decr, reinterpret_cast<void*>(&turn));

    sleep(2);
}

void* incr(void* args)
{
    std::cout << "calling incr ( )" << std::endl;
    
    while (1) 
    {
        std::cout << "incr : mutex_lock" << std::endl;
        pthread_mutex_lock(&g_mutex);
        std::cout << "incr : reinterpret_cast" << std::endl;
        auto v = reinterpret_cast<int*>(args);
        if (*v == 1)
        {
            std::cout << "incr : cond_wait" << std::endl;
            pthread_cond_wait(&g_cond[0], &g_mutex);
        }
        std::cout << "incr : += 1U" << std::endl;
        *v = 1;
        
        std::cout << "turn in incr( ) " << *v << std::endl;
        
        std::cout << "incr : cond_signal" << std::endl;
        pthread_cond_signal(&g_cond[1]);
        std::cout << "incr : mutex_unlock" << std::endl;
        pthread_mutex_unlock(&g_mutex);
    }
}

void* decr(void* args)
{
    std::cout << "calling decr ( )" << std::endl;

    while(1) 
    {
        std::cout << "decr : mutex_lock" << std::endl;
        pthread_mutex_lock(&g_mutex);
        std::cout << "decr : reinterpret_cast" << std::endl;
        auto v = reinterpret_cast<int*>(args);
        if (*v == -1)
        {
            std::cout << "decr : cond_wait" << std::endl;
            pthread_cond_wait(&g_cond[1], &g_mutex);
        }
        std::cout << "decr : += 1U" << std::endl;
        *v = -1;

        std::cout << "turn in decr( ) " << *v << std::endl;
        
        std::cout << "decr : cond_signal" << std::endl;
        pthread_cond_signal(&g_cond[0]);
        std::cout << "decr : mutex_unlock" << std::endl;
        pthread_mutex_unlock(&g_mutex);
    }
}

void pthread_test_main(void)
{
    std::cout << "pthread_test_main function begins..." << std::endl;

    init_vars();
    std::atexit(destroy_vars);

    execution();

    for (auto& x : arr_threads)
    {
        pthread_cancel(x);
    }

    std::cout << "pth_test_main RETURN ! ! !" << std::endl;
}

int main()
{
    std::cout << std::flush;
    std::cout << "main begins..." << std::endl;

    pthread_test_main();

    std::cout << "main ends...!" << std::endl;

    return 0;
}
