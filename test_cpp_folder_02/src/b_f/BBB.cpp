#include "../../include/b_f/BBB.hpp"

void BBB(void)
{
    auto vector_BBB = std::make_shared<std::vector<double>>();
    (*vector_BBB).push_back(7);
    print((*vector_BBB).back());
}
