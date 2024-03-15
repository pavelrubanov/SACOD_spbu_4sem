#include "polynom.h"
#include <stdio.h>

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

    //реальный размер массива может отличаться от len. нужно добавить проверку!
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