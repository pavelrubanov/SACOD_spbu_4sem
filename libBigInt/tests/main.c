#include <limits.h>

#include "../src/libBigInt.h"
#include "../src/utils.h"
#include "minunit.h"

MU_TEST(str_tests)
{
    BigInt *a = read_from_str("1234");
    char *str = to_str(a);
    mu_assert_string_eq("1234", str);
    mu_check(a->sign == 1);
    mu_check(a->n == 4);

    a = read_from_str("-1234");
    str = to_str(a);
    mu_assert_string_eq("-1234", str);
    mu_check(a->sign == -1);
    mu_check(a->n == 4);

    BigInt_free(a);
}

MU_TEST(length_tests)
{
    size_t size_0 = 0;
    size_t size_1000 = 1000;
    size_t size_uint_max = UINT_MAX;

    BigInt *a = BigInt_init(size_0);
    BigInt *b = BigInt_init(size_1000);
    BigInt *c = BigInt_init(size_uint_max);

    mu_check(a->n == 0);
    mu_check(b->n == 1000);
    mu_check(c->n == size_uint_max);

    BigInt_free(a);
    BigInt_free(b);
    BigInt_free(c);
}

MU_TEST(sum_tests)
{
    BigInt *a = read_from_str("12345");
    BigInt *b = read_from_str("23456");

    const char *ans1 = "35801";
    BigInt *res = addition(a, b);

    mu_assert_int_eq(5, res->n);
    mu_assert_string_eq(ans1, to_str(res));

    a = read_from_str("-12345");
    b = read_from_str("-23456");

    const char *ans2 = "-35801";
    res = addition(a, b);

    mu_assert_int_eq(5, res->n);
    mu_assert_string_eq(ans2, to_str(res));


    BigInt_free(a);
    BigInt_free(b);
}

MU_TEST(normalize_tests)
{
    BigInt *a = read_from_str("0000123");
    normalize(a);
    mu_assert_int_eq(3, a->n);
    mu_assert_string_eq("123", to_str(a));

    a = read_from_str("-0000123");
    normalize(a);
    mu_assert_int_eq(3, a->n);
    mu_assert_string_eq("-123", to_str(a));

    BigInt_free(a);
}

int main()
{
    MU_RUN_TEST(str_tests);
    MU_RUN_TEST(length_tests);
    MU_RUN_TEST(sum_tests);
    MU_RUN_TEST(normalize_tests);

    MU_REPORT();

    return MU_EXIT_CODE;
}

void test(BigInt *a)
{
    printf("n: %ld\n", a->n);
    printf("sign: %d\n", a->sign);
    printf("strlen: %ld\n", strlen(a->digits));
    printf("to_str: %s\n", to_str(a));
}