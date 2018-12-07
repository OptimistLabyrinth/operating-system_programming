#include "../include/pthread_manager.hpp"

std::vector<pthread_t> Thread_Manager::threads;

Thread_Manager::Thread_Manager(uint type)
{
    threads = std::vector<pthread_t>(0);
    pthread_type_name = type;
}

uint Thread_Manager::get_pos_for_new_thread(void) 
{
    threads.resize(threads.size() + 1);
    return threads.size() - 1;
}

void Thread_Manager::create_new_thread(void* arg)
{
    auto class_context = reinterpret_cast<CLASS_TEST*>(arg);

    pthread_create( 
        &(Thread_Manager::threads.at(Thread_Manager::get_pos_for_new_thread())), 
        nullptr, 
        &CLASS_TEST::execute_helper, 
        class_context);
}
