#include "../include/main_runner.hpp"

int main()
{
    CLASS_TEST ct(THREAD_TYPE_01_DEF);
    Thread_Manager tm(THREAD_TYPE_01_DEF);
    thread_args_01 l_args(17, "yes");

    ct._args_to_execute(reinterpret_cast<void*>(&l_args));

    tm.create_new_thread(reinterpret_cast<void*>(&ct));

    print("pause here");
    while (1) {
        pause();
    }

    return 0;
}
