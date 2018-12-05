#ifndef PTHREAD_MANAGER__1234__HPP___
#define PTHREAD_MANAGER__1234__HPP___

#include <vector>

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

#include "class_test.hpp"
#include "print_functions.hpp"

class Thread_Manager
{
public:
    static std::vector<pthread_t> threads;
    uint pthread_type_name;

    // Constructor 
    Thread_Manager(uint);

    // member functions 
    uint get_pos_for_new_thread(void);
    void create_new_thread(void* arg);

private:


};

#endif /* PTHREAD_MANAGER__1234__HPP___ */