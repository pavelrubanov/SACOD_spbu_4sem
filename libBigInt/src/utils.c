#include "utils.h"

void normalize(BigInt *num)
{
    int new_len = num->n;
    while (new_len > 0 && num->digits[new_len - 1] == 0)
    {
        new_len--;
    }

    num->n = new_len;
    if (num->n == 0)
    {
        num->sign = 0;
    }

    num->digits = realloc(num->digits, sizeof(char) * new_len);
    if (num->n == 0)
    {
        num->sign = 0;
    }
}
size_t max_size(const BigInt *a, const BigInt *b)
{
    if (a->n > b->n)
    {
        return a->n;
    }
    else
    {
        return b->n;
    }
}
BigInt *get_cp_abs(const BigInt *a)
{
    BigInt *res = read_from_str(to_str(a));
    res->sign = 1;
    return res;
}
BigInt *get_cp_opposite(const BigInt *a)
{
    BigInt *res = get_cp_abs(a);
    res->sign = a->sign * (-1);
}
int is_bigger(const BigInt *a, const BigInt *b)
{
    if (a->n > b->n)
    {
        return 1;
    }
    if (a->n < b->n)
    {
        return 0;
    }
    size_t len = a->n;
    for (int i = len - 1; i >= 0; i--)
    {
        if (a->digits[i] < b->digits[i])
        {
            return 0;
        }
    }
    return 1;
}
