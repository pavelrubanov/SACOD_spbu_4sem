#include "polynom.h"

pol *pol_init(int8_t deg, int8_t *p_coef, int8_t len)
{
    pol *res = malloc(sizeof(pol));
    if (res == NULL)
        return NULL;

    if (res == NULL || deg < 0 || p_coef == NULL || len < 0)
        return NULL;

    res->coef = malloc(sizeof(int8_t) * len);
    if (res->coef == NULL)
        return NULL;

    // реальный размер массива может отличаться от len. нужно добавить проверку!
    for (int i = 0; i < len; i++)
    {
        res->coef[i] = p_coef[i];
    }

    res->deg = deg;
    res->len = len;

    return res;
}

void pol_free(pol *p)
{
    if (p != NULL)
        free(p->coef);
    free(p);
}

int pol_eq(const pol *a, const pol *b)
{
    if (a == NULL || b == NULL || a->deg != b->deg || a->len != b->len)
        return 0;

    for (int i = 0; i < a->len; i++)
    {
        if (a->coef[i] != b->coef[i])
            return 0;
    }

    return 1;
}

void pol_deg_normalize(pol *a)
{
    if (a == NULL)
        return;

    size_t k = a->len - 1;

    while ((k > 0) && (a->coef[k] == 0))
        k--;

    a->deg = k;
}

void pol_coef_normalize(pol *a, int8_t p)
{
    
}

pol *pol_zero(size_t len)
{
    if (len == NULL || len == 0)
        return NULL;

    int8_t *tmp = calloc(len, sizeof(int8_t));

    pol *res = pol_init(0, tmp, len);

    free(tmp);

    return res;
}

pol *pol_sum(const pol *a, const pol *b)
{
}

pol *pol_diff(const pol *a, const pol *b)
{
}

pol *pol_mult(const pol *a, const pol *b)
{
}

pol *pol_div(const pol *a, const pol *b)
{
}