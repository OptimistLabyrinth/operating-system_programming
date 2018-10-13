#include "test01.h"
#include "test02.h"

int main(void)
{
    const char* msg = functA();
    int ii = functB();

    print_str(msg);
    print_int(ii);

    return 0;
}


