#include "../src/fflib.h"
#include "minunit.h"

// неприводимые:
uint8_t f2_p[] = {1, 1};
uint8_t f2p2_p[] = {1, 1, 1};
uint8_t f2p3_p[] = {1, 1, 0, 1};
uint8_t f3_p[] = {1, 1};
uint8_t f3p3_p[] = {1, 2, 0, 1};
uint8_t f5_p[] = {1, 1};
uint8_t f7_p[] = {1, 1};

MU_TEST(init_tests)
{
    ff *ff_el1 = ff_init(2, 1, f2_p);
    ff *ff_el2 = ff_init(2, 2, f2p2_p);
    ff *ff_el3 = ff_init(2, 3, f2p3_p);
    ff *ff_el4 = ff_init(3, 1, f3_p);
    ff *ff_el5 = ff_init(5, 1, f5_p);

    mu_check(ff_el1 != NULL);
    mu_check(ff_el2 != NULL);
    mu_check(ff_el3 != NULL);
    mu_check(ff_el4 != NULL);
    mu_check(ff_el5 != NULL);

    ff_free(ff_el1);
    ff_free(ff_el2);
    ff_free(ff_el3);
    ff_free(ff_el4);
    ff_free(ff_el5);
}

MU_TEST(zero_tests)
{
    ff *ff_el1 = ff_init(2, 1, f2_p);
    ff *ff_el2 = ff_init(2, 2, f2p2_p);

    ff_el *ff_el3 = ff_zero(ff_el1);
    ff_el *ff_el4 = ff_zero(ff_el2);
    uint8_t ep[] = {0};
    ff_el *ff_el5 = ff_el_from_arr(ff_el1, ep);
    uint8_t fp[] = {0, 0};
    ff_el *ff_el6 = ff_el_from_arr(ff_el2, fp);

    mu_check(ff_el_equals(ff_el3, ff_el5));
    mu_check(ff_el_equals(ff_el4, ff_el6));

    ff_el_free(ff_el3);
    ff_el_free(ff_el4);
    ff_el_free(ff_el5);
    ff_el_free(ff_el6);

    ff_free(ff_el1);
    ff_free(ff_el2);
}

MU_TEST(identity_tests)
{
    ff *ff_el1 = ff_init(2, 1, f2_p);
    ff *ff_el2 = ff_init(2, 2, f2p2_p);

    ff_el *ff_el3 = ff_identity(ff_el1);
    ff_el *ff_el4 = ff_identity(ff_el2);
    uint8_t ep[] = {1};
    ff_el *ff_el5 = ff_el_from_arr(ff_el1, ep);
    uint8_t fp[] = {1, 0};
    ff_el *ff_el6 = ff_el_from_arr(ff_el2, fp);

    mu_check(ff_el_equals(ff_el3, ff_el5));
    mu_check(ff_el_equals(ff_el4, ff_el6));

    ff_el_free(ff_el3);
    ff_el_free(ff_el4);
    ff_el_free(ff_el5);
    ff_el_free(ff_el6);

    ff_free(ff_el1);
    ff_free(ff_el2);
}

MU_TEST(sum_tests)
{
    ff *ff_el1 = ff_init(2, 3, f2p3_p);
    ff *ff_el2 = ff_init(7, 1, f5_p);
    ff *ff_el3 = ff_init(3, 3, f3p3_p);

    uint8_t dp[] = {1, 1, 1};
    ff_el *ff_el4 = ff_el_from_arr(ff_el1, dp);
    uint8_t ep[] = {1, 0, 1};
    ff_el *ff_el5 = ff_el_from_arr(ff_el1, ep);
    uint8_t fp[] = {0, 1, 0};
    ff_el *ff_el6 = ff_el_from_arr(ff_el1, fp);
    ff_el *ff_el7 = ff_sum(ff_el4, ff_el5);

    uint8_t hp[] = {4};
    ff_el *ff_el8 = ff_el_from_arr(ff_el2, hp);
    uint8_t ip[] = {6};
    ff_el *ff_el9 = ff_el_from_arr(ff_el2, ip);
    uint8_t jp[] = {3};
    ff_el *ff_el10 = ff_el_from_arr(ff_el2, jp);
    ff_el *ff_el11 = ff_sum(ff_el8, ff_el9);

    uint8_t lp[] = {2, 0, 2};
    ff_el *ff_el12 = ff_el_from_arr(ff_el3, lp);
    uint8_t mp[] = {2, 2, 1};
    ff_el *ff_el13 = ff_el_from_arr(ff_el3, mp);
    uint8_t np[] = {1, 2, 0};
    ff_el *ff_el14 = ff_el_from_arr(ff_el3, np);
    ff_el *ff_el15 = ff_sum(ff_el12, ff_el13);

    mu_check(ff_el_equals(ff_el7, ff_el6));
    mu_check(ff_el_equals(ff_el11, ff_el10));
    mu_check(ff_el_equals(ff_el14, ff_el15));

    ff_el_free(ff_el4);
    ff_el_free(ff_el5);
    ff_el_free(ff_el6);
    ff_el_free(ff_el7);
    ff_el_free(ff_el8);
    ff_el_free(ff_el9);
    ff_el_free(ff_el10);
    ff_el_free(ff_el11);
    ff_el_free(ff_el12);
    ff_el_free(ff_el13);
    ff_el_free(ff_el14);
    ff_el_free(ff_el15);
    ff_free(ff_el1);
    ff_free(ff_el2);
    ff_free(ff_el3);
}

MU_TEST(sub_tests)
{
    ff *ff_el1 = ff_init(2, 3, f2p3_p);
    ff *ff_el2 = ff_init(7, 1, f5_p);
    ff *ff_el3 = ff_init(3, 3, f3p3_p);

    uint8_t dp[] = {1, 1, 1};
    ff_el *ff_el4 = ff_el_from_arr(ff_el1, dp);
    uint8_t ep[] = {1, 0, 1};
    ff_el *ff_el5 = ff_el_from_arr(ff_el1, ep);
    uint8_t fp[] = {0, 1, 0};
    ff_el *ff_el6 = ff_el_from_arr(ff_el1, fp);
    ff_el *ff_el7 = ff_sub(ff_el4, ff_el5);

    uint8_t hp[] = {4};
    ff_el *ff_el8 = ff_el_from_arr(ff_el2, hp);
    uint8_t ip[] = {6};
    ff_el *ff_el9 = ff_el_from_arr(ff_el2, ip);
    uint8_t jp[] = {5};
    ff_el *ff_el10 = ff_el_from_arr(ff_el2, jp);
    ff_el *ff_el11 = ff_sub(ff_el8, ff_el9);

    uint8_t lp[] = {2, 0, 2};
    ff_el *ff_el12 = ff_el_from_arr(ff_el3, lp);
    uint8_t mp[] = {2, 2, 1};
    ff_el *ff_el13 = ff_el_from_arr(ff_el3, mp);
    uint8_t np[] = {0, 1, 1};
    ff_el *ff_el14 = ff_el_from_arr(ff_el3, np);
    ff_el *ff_el15 = ff_sub(ff_el12, ff_el13);

    mu_check(ff_el_equals(ff_el7, ff_el6));
    mu_check(ff_el_equals(ff_el11, ff_el10));
    mu_check(ff_el_equals(ff_el14, ff_el15));

    ff_el_free(ff_el4);
    ff_el_free(ff_el5);
    ff_el_free(ff_el6);
    ff_el_free(ff_el7);
    ff_el_free(ff_el8);
    ff_el_free(ff_el9);
    ff_el_free(ff_el10);
    ff_el_free(ff_el11);
    ff_el_free(ff_el12);
    ff_el_free(ff_el13);
    ff_el_free(ff_el14);
    ff_el_free(ff_el15);
    ff_free(ff_el1);
    ff_free(ff_el2);
    ff_free(ff_el3);
}

MU_TEST(negative_tests)
{
    ff *ff_el1 = ff_init(2, 3, f2p3_p);
    ff *ff_el2 = ff_init(7, 1, f5_p);
    ff *ff_el3 = ff_init(3, 3, f3p3_p);

    uint8_t dp[] = {1, 1, 1};
    ff_el *ff_el4 = ff_el_from_arr(ff_el1, dp);
    uint8_t fp[] = {1, 1, 1};
    ff_el *ff_el6 = ff_el_from_arr(ff_el1, fp);
    ff_el *ff_el7 = ff_negative(ff_el4);

    uint8_t hp[] = {4};
    ff_el *ff_el8 = ff_el_from_arr(ff_el2, hp);
    uint8_t jp[] = {3};
    ff_el *ff_el10 = ff_el_from_arr(ff_el2, jp);
    ff_el *ff_el11 = ff_negative(ff_el8);

    uint8_t lp[] = {2, 0, 2};
    ff_el *ff_el12 = ff_el_from_arr(ff_el3, lp);
    uint8_t np[] = {1, 0, 1};
    ff_el *ff_el14 = ff_el_from_arr(ff_el3, np);
    ff_el *ff_el15 = ff_negative(ff_el12);

    mu_check(ff_el_equals(ff_el7, ff_el6));
    mu_check(ff_el_equals(ff_el11, ff_el10));
    mu_check(ff_el_equals(ff_el14, ff_el15));

    ff_el_free(ff_el4);
    ff_el_free(ff_el6);
    ff_el_free(ff_el7);
    ff_el_free(ff_el8);
    ff_el_free(ff_el10);
    ff_el_free(ff_el11);
    ff_el_free(ff_el12);
    ff_el_free(ff_el14);
    ff_el_free(ff_el15);
    ff_free(ff_el1);
    ff_free(ff_el2);
    ff_free(ff_el3);
}

MU_TEST(mul_tests)
{
    ff *ff_el1 = ff_init(2, 3, f2p3_p);
    ff *ff_el2 = ff_init(7, 1, f5_p);
    ff *ff_el3 = ff_init(3, 3, f3p3_p);

    uint8_t dp[] = {1, 1, 1}; // ff_el1^5
    ff_el *ff_el4 = ff_el_from_arr(ff_el1, dp);
    uint8_t ep[] = {1, 0, 1}; // ff_el1^6
    ff_el *ff_el5 = ff_el_from_arr(ff_el1, ep);
    uint8_t fp[] = {0, 1, 1}; // ff_el1^4
    ff_el *ff_el6 = ff_el_from_arr(ff_el1, fp);
    ff_el *ff_el7 = ff_mult(ff_el4, ff_el5);

    uint8_t hp[] = {4};
    ff_el *ff_el8 = ff_el_from_arr(ff_el2, hp);
    uint8_t ip[] = {6};
    ff_el *ff_el9 = ff_el_from_arr(ff_el2, ip);
    uint8_t jp[] = {3};
    ff_el *ff_el10 = ff_el_from_arr(ff_el2, jp);
    ff_el *ff_el11 = ff_mult(ff_el8, ff_el9);

    uint8_t lp[] = {2, 0, 2}; // ff_el1^8
    ff_el *ff_el12 = ff_el_from_arr(ff_el3, lp);
    uint8_t mp[] = {2, 2, 1}; // ff_el1^7
    ff_el *ff_el13 = ff_el_from_arr(ff_el3, mp);
    uint8_t np[] = {0, 0, 2}; // ff_el1^15
    ff_el *ff_el14 = ff_el_from_arr(ff_el3, np);
    ff_el *ff_el15 = ff_mult(ff_el12, ff_el13);

    mu_check(ff_el_equals(ff_el7, ff_el6));
    mu_check(ff_el_equals(ff_el11, ff_el10));
    mu_check(ff_el_equals(ff_el14, ff_el15));

    ff_el_free(ff_el4);
    ff_el_free(ff_el5);
    ff_el_free(ff_el6);
    ff_el_free(ff_el7);
    ff_el_free(ff_el8);
    ff_el_free(ff_el9);
    ff_el_free(ff_el10);
    ff_el_free(ff_el11);
    ff_el_free(ff_el12);
    ff_el_free(ff_el13);
    ff_el_free(ff_el14);
    ff_el_free(ff_el15);

    ff_free(ff_el1);
    ff_free(ff_el2);
    ff_free(ff_el3);
}

MU_TEST(div_tests)
{
    ff *ff_el1 = ff_init(2, 3, f2p3_p);
    ff *ff_el2 = ff_init(7, 1, f5_p);
    ff *ff_el3 = ff_init(3, 3, f3p3_p);

    uint8_t dp[] = {1, 1, 1}; // ff_el1^5
    ff_el *ff_el4 = ff_el_from_arr(ff_el1, dp);
    uint8_t ep[] = {1, 0, 1}; // ff_el1^6
    ff_el *ff_el5 = ff_el_from_arr(ff_el1, ep);
    uint8_t fp[] = {1, 0, 1}; // ff_el1^6
    ff_el *ff_el6 = ff_el_from_arr(ff_el1, fp);
    ff_el *ff_el7 = ff_div(ff_el4, ff_el5);

    uint8_t hp[] = {4};
    ff_el *ff_el8 = ff_el_from_arr(ff_el2, hp);
    uint8_t ip[] = {6};
    ff_el *ff_el9 = ff_el_from_arr(ff_el2, ip);
    uint8_t jp[] = {3};
    ff_el *ff_el10 = ff_el_from_arr(ff_el2, jp);
    ff_el *ff_el11 = ff_div(ff_el8, ff_el9);

    uint8_t lp[] = {2, 0, 2}; // ff_el1^8
    ff_el *ff_el12 = ff_el_from_arr(ff_el3, lp);
    uint8_t mp[] = {2, 2, 1}; // ff_el1^7
    ff_el *ff_el13 = ff_el_from_arr(ff_el3, mp);
    uint8_t np[] = {0, 1, 0}; // ff_el1
    ff_el *ff_el14 = ff_el_from_arr(ff_el3, np);
    ff_el *ff_el15 = ff_div(ff_el12, ff_el13);

    mu_check(ff_el_equals(ff_el7, ff_el6));
    mu_check(ff_el_equals(ff_el11, ff_el10));
    mu_check(ff_el_equals(ff_el14, ff_el15));

    ff_el_free(ff_el4);
    ff_el_free(ff_el5);
    ff_el_free(ff_el6);
    ff_el_free(ff_el7);
    ff_el_free(ff_el8);
    ff_el_free(ff_el9);
    ff_el_free(ff_el10);
    ff_el_free(ff_el11);
    ff_el_free(ff_el12);
    ff_el_free(ff_el13);
    ff_el_free(ff_el14);
    ff_el_free(ff_el15);
    ff_free(ff_el1);
    ff_free(ff_el2);
    ff_free(ff_el3);
}

MU_TEST(inv_tests)
{
    ff *ff_el1 = ff_init(2, 3, f2p3_p);
    ff *ff_el2 = ff_init(7, 1, f5_p);
    ff *ff_el3 = ff_init(3, 3, f3p3_p);

    uint8_t dp[] = {1, 1, 1}; // ff_el1^5
    ff_el *ff_el4 = ff_el_from_arr(ff_el1, dp);
    uint8_t fp[] = {0, 0, 1}; // ff_el1^2
    ff_el *ff_el6 = ff_el_from_arr(ff_el1, fp);
    ff_el *ff_el7 = ff_inverse(ff_el4);

    uint8_t hp[] = {4};
    ff_el *ff_el8 = ff_el_from_arr(ff_el2, hp);
    uint8_t jp[] = {2};
    ff_el *ff_el10 = ff_el_from_arr(ff_el2, jp);
    ff_el *ff_el11 = ff_inverse(ff_el8);

    uint8_t lp[] = {2, 0, 2}; // ff_el1^8
    ff_el *ff_el12 = ff_el_from_arr(ff_el3, lp);
    uint8_t np[] = {1, 2, 1}; // ff_el1^18
    ff_el *ff_el14 = ff_el_from_arr(ff_el3, np);
    ff_el *ff_el15 = ff_inverse(ff_el12);

    mu_check(ff_el_equals(ff_el7, ff_el6));
    mu_check(ff_el_equals(ff_el11, ff_el10));
    mu_check(ff_el_equals(ff_el14, ff_el15));

    ff_el_free(ff_el4);
    ff_el_free(ff_el6);
    ff_el_free(ff_el7);
    ff_el_free(ff_el8);
    ff_el_free(ff_el10);
    ff_el_free(ff_el11);
    ff_el_free(ff_el12);
    ff_el_free(ff_el14);
    ff_el_free(ff_el15);
    ff_free(ff_el1);
    ff_free(ff_el2);
    ff_free(ff_el3);
}

MU_TEST(ff8_16_32_tests)
{
    ff_el *ff_el1 = ff_el_uint8(17);
    ff_el *ff_el2 = ff_el_uint16(4353);
    ff_el *ff_el3 = ff_el_uint32(69889);

    uint8_t dp[] = {1, 0, 0, 0, 1, 0, 0, 0};
    ff_el *ff_el4 = ff_el_from_arr(ff2_8, dp);
    uint8_t ep[] = {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0};
    ff_el *ff_el5 = ff_el_from_arr(ff2_16, ep);
    uint8_t fp[] = {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ff_el *ff_el6 = ff_el_from_arr(ff2_32, fp);

    mu_check(ff_el_equals(ff_el1, ff_el4));
    mu_check(ff_el_equals(ff_el2, ff_el5));
    mu_check(ff_el_equals(ff_el3, ff_el6));

    ff_el_free(ff_el1);
    ff_el_free(ff_el2);
    ff_el_free(ff_el3);
    ff_el_free(ff_el4);
    ff_el_free(ff_el5);
    ff_el_free(ff_el6);
}

int main()
{
    MU_RUN_TEST(init_tests);
    MU_RUN_TEST(zero_tests);
    MU_RUN_TEST(identity_tests);
    MU_RUN_TEST(sum_tests);
    MU_RUN_TEST(sub_tests);
    MU_RUN_TEST(negative_tests);
    MU_RUN_TEST(mul_tests);
    MU_RUN_TEST(div_tests);
    MU_RUN_TEST(inv_tests);
    MU_RUN_TEST(ff8_16_32_tests);

    MU_REPORT();
    return 0;
}
