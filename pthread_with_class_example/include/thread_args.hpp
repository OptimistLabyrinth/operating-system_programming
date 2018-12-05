#ifndef THREAD_ARGS__1234__HPP___
#define THREAD_ARGS__1234__HPP___

#define THREAD_TYPE_01_DEF 11223344U

#include <string>



using thread_args = struct thread_args;
struct thread_args {

};



using thread_args_01 = struct thread_args_01;
struct thread_args_01 : thread_args 
{   // #define THREAD_TYPE_01_DEF 11223344U;
    thread_args_01(int i, std::string s) { i_one = i; msg = s; }
    int i_one;
    std::string msg;
};



#endif /* THREAD_ARGS__1234__HPP___ */