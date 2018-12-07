#include "../include/main_executor.hpp"

int main()
{
    main_executor();

    return 0;
}

void main_executor(void)
{
    std::setlocale(LC_TIME, "ko_KR.utf8");

    print("inside main_executor( )");
    
    initialize_variables();

    create_new_thread();
    print("posix thread create OK OK OK");

    create_posix_timer();
    print("posix_timer is created OK");

    print("pause HERE");
    while(1) {
        pause();
    }
}
