#include "utils.h"


bool same_ff(const ff_el *a, const ff_el *b)
{
    if (a == NULL)
        return false;
    if (b == NULL)
        return false;

    if (a->ff->ch != b->ff->ch || a->ff->n != b->ff->n)
        return false;
        
    return memcmp(a->ff->p, b->ff->p, a->ff->n + 1) == 0;
}

uint64_t mpow(uint64_t base, uint64_t exp)
{
    uint64_t result = 1;
    while (exp)
    {
        if (exp % 2 == 1)
        {
            result *= base;
            exp--;
        }
        else
        {
            exp /= 2;
            base *= base;
        }
    }
    return result;
}

ff_el *ff_el_cp(const ff_el *f)
{
    if (f == NULL)
        return NULL;

    const ff *ff = f->ff;
    ff_el *result = ff_el_init(ff);
    if (result == NULL)
        return NULL;

    for (size_t i = 0; i < ff->n; i++)
        result->dig[i] = f->dig[i];

    return result;
}

void ff_el_print(const ff_el *a)
{
    const ff *ff = a->ff;
    for (ssize_t i = ff->n - 1; i >= 0; i--)
    {
        printf("%dx^%ld", a->dig[i], i);
        if (i != 0)
            printf(" + ");
    }
    printf("\n");
}