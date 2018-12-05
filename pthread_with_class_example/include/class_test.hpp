#ifndef CLASS_TEST__1234__HPP___
#define CLASS_TEST__1234__HPP___

#include <string>

#include "thread_args.hpp"
#include "print_functions.hpp"



class CLASS_TEST 
{
public:
    CLASS_TEST(uint);
    CLASS_TEST(const CLASS_TEST&);
    CLASS_TEST(CLASS_TEST&&);
    CLASS_TEST& operator=(const CLASS_TEST&);
    ~CLASS_TEST();

    void execute(void);
    void _args_to_execute(void*);
    static void* execute_helper(void*);

private:
    uint thread_type_name;
    void* args_to_execute;
};



#endif /* CLASS_TEST__1234__HPP___ */