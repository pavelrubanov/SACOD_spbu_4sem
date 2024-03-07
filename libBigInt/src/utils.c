#include "utils.h"

BigInt *BigInt_init(size_t size)
{
    BigInt *num = malloc(sizeof(BigInt));
    if (num)
    {
        num->digits = malloc(sizeof(char) * (size + 1));
        num->n = size;
        num->sign = 0;
        for (int i = 0; i < size; i++)
        {
            num->digits[i] = 0;
        }
        num->digits[size] = '\0';
    }
    return num;
}

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

    num->digits = realloc(num->digits, sizeof(char) * (new_len + 1));
    num->digits[new_len] = '\0';
}
BigInt *zero()
{
    return BigInt_init(0);
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
    BigInt *res = get_cp(a);
    res->sign = 1;
    return res;
}

BigInt *get_cp(const BigInt *a)
{
    BigInt *res = BigInt_init(a->n);
    res->sign = a->sign;
    for (int i = 0; i < res->n; i++)
    {
        res->digits[i] = a->digits[i];
    }
    return res;
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
    for (int i = a->n - 1; i >= 0; i--)
    {
        if (a->digits[i] > b->digits[i])
        {
            return 1;
        }
        if (a->digits[i] < b->digits[i])
        {
            return 0;
        }
    }
    return 1;
}
int equals(const BigInt *a, const BigInt *b)
{
    return strcmp(to_str(a), to_str(b));
}