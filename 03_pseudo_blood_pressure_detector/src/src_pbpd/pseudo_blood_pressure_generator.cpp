#include "../../include/include_pbpd/pseudo_blood_pressure_generator.hpp"



auto m_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937_64 rand_gen(m_seed);
std::uniform_int_distribution<int> diastolic(60, 90);
std::uniform_int_distribution<int> systolic(110, 150);



int pseudo_distolic_blood_pressure(void)
{
    return diastolic(rand_gen);
}

int pseudo_systolic_blood_pressure(void)
{
    return systolic(rand_gen);
}
