#include "../../include/a_f/AAA.hpp"

void AAA(void)
{
    auto va = std::make_shared<unsigned long>();
    *va = static_cast<unsigned long>(2);
    print((*va) - 1);
}
