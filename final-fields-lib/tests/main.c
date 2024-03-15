#include "minunit.h"

MU_TEST(test1)
{
    mu_assert_int_eq(1,2);
}

int main()
{
    printf("start");
    MU_RUN_TEST(test1);
    MU_REPORT();
    return 0;
}