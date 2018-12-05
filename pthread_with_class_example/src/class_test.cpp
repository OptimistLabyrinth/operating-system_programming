#include "../include/class_test.hpp"

CLASS_TEST::CLASS_TEST(uint type)
{
    thread_type_name = type;
    args_to_execute = nullptr;
}
CLASS_TEST::CLASS_TEST(const CLASS_TEST& another)
{
    thread_type_name = another.thread_type_name;
    if (another.args_to_execute != nullptr) {
        args_to_execute = another.args_to_execute;
    }
}
CLASS_TEST::CLASS_TEST(CLASS_TEST&& another)
{
    std::__exchange(thread_type_name, another.thread_type_name);
    std::__exchange(args_to_execute, another.args_to_execute);
}
CLASS_TEST& CLASS_TEST::operator=(const CLASS_TEST& another)
{
    if (this != &another) {
        thread_type_name = another.thread_type_name;
        if (another.args_to_execute != nullptr) {
            args_to_execute = another.args_to_execute;
        }
    }
    return *this;
}
CLASS_TEST::~CLASS_TEST()
{

}

void CLASS_TEST::execute(void)
{
    switch (thread_type_name)
    {
        case THREAD_TYPE_01_DEF:
        {
            auto args = reinterpret_cast<thread_args_01*>(args_to_execute);
            print( "Hello, World!" );
            print( "args i_one = " + std::to_string(args->i_one));
            print("args str_name = " + args->msg);
            break;
        }

        default:
            print("default case");
    }

}

void CLASS_TEST::_args_to_execute(void* arg)
{
    args_to_execute = reinterpret_cast<struct thread_args_01*>(arg);
}

void* CLASS_TEST::execute_helper(void* arg) // static function
{
    auto context = reinterpret_cast<CLASS_TEST*>(arg);
    for (int i=0; i < 5; ++i)
    {
        context->execute();
        print();
    }

    return nullptr;
}
