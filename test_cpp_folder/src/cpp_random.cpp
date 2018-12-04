#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    std::srand(std::time(NULL));
    std::cout << "OK\n" << std::endl;

    for (int i=0; i < 100; ++i) {
        int random_var = std::rand();
        std::cout << random_var%99 + 1 << "\t"; 
    }

    std::cout << std::endl;

    return 0;
}