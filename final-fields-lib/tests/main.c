#include <stdio.h>

#include "minunit.h"
#include "../src/polynom.h"
#include "../src/fflib.h"

MU_TEST(pol_tests)
{
    int8_t coef1[] = {1, 2, 3};

    int8_t coef2[] = {1, 2};

    pol *p1 = pol_init(3, &coef1, 3);
    pol *p2 = pol_init(2, &coef2, 2);

    mu_assert_int_eq(1, p1->coef[0]);
    mu_assert_int_eq(2, p1->coef[1]);
    mu_assert_int_eq(3, p1->coef[2]);

    mu_assert_int_eq(1, p2->coef[0]);
    mu_assert_int_eq(2, p2->coef[1]);

    mu_assert_int_eq(3, p2->deg);
    mu_assert_int_eq(2, p2->len);

    mu_assert(!pol_eq(p1, p2), "pols not equal");

    pol_free(p1);
    pol_free(p2);
}

int main()
{
    MU_RUN_TEST(pol_tests);

    MU_REPORT();
    return 0;
}