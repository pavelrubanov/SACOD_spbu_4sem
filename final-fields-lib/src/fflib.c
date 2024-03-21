#include "fflib.h"
#include "utils.h"

ff *ff_init(uint8_t ch, size_t n, const uint8_t *p)
{
    ff *result = malloc(sizeof(ff));
    if (result == NULL)
        return NULL;
    if (p[n] != 1)
        return NULL;

    result->ch = ch;
    result->n = n;
    result->p = malloc((n + 1) * sizeof(uint8_t));
    if (result->p == NULL)
    {
        free(result);
        return NULL;
    }
    memcpy(result->p, p, (n + 1) * sizeof(uint8_t));

    return result;
}

void ff_free(ff *a)
{
    if (a == NULL)
        return;

    free(a->p);
    free(a);
}

ff_el *ff_el_init(const ff *ff)
{
    if (ff == NULL)
        return NULL;

    ff_el *result = malloc(sizeof(ff_el));
    if (result == NULL)
        return NULL;

    result->ff = ff;
    result->dig = calloc(ff->n, sizeof(uint8_t)); // 0
    if (result->dig == NULL)
    {
        free(result);
        return NULL;
    }

    return result;
}

void ff_el_free(ff_el *a)
{
    if (a == NULL)
        return;

    free(a->dig);
    free(a);
}

ff_el *ff_zero(const ff *a)
{
    if (a == NULL)
        return NULL;

    return ff_el_init(a);
}

ff_el *ff_identity(const ff *a)
{
    if (a == NULL)
        return NULL;

    ff_el *result = ff_el_init(a);
    if (result == NULL)
        return NULL;
    result->dig[0] = 1;

    return result;
}

ff_el *ff_el_from_arr(const ff *a, const uint8_t *p)
{
    if (a == NULL)
        return NULL;
    if (p == NULL)
        return NULL;

    ff_el *result = ff_el_init(a);
    if (result == NULL)
        return NULL;
    for (size_t i = 0; i < a->n; i++)
        result->dig[i] = p[i];

    return result;
}

int ff_el_equals(const ff_el *a, const ff_el *b)
{
    if (a == NULL)
        return 0;
    if (b == NULL)
        return 0;
    if (!same_ff(a, b))
        return 0;

    return memcmp(a->dig, b->dig, a->ff->n) == 0;
}

ff_el *ff_sum(const ff_el *a, const ff_el *b)
{
    if (a == NULL)
        return NULL;
    if (b == NULL)
        return NULL;
    if (!same_ff(a, b))
        return NULL;

    const ff *ff = a->ff;
    ff_el *result = ff_el_init(ff);
    if (result == NULL)
        return NULL;
    for (size_t i = 0; i < ff->n; i++)
        result->dig[i] = (a->dig[i] + b->dig[i]) % ff->ch;

    return result;
}

ff_el *ff_sub(const ff_el *a, const ff_el *b)
{
    if (a == NULL)
        return NULL;
    if (b == NULL)
        return NULL;
    if (!same_ff(a, b))
        return NULL;

    ff_el *b_neg = ff_negative(b);
    if (b_neg == NULL)
        return NULL;
    ff_el *result = ff_sum(a, b_neg);
    ff_el_free(b_neg);

    return result;
}

ff_el *ff_negative(const ff_el *a)
{
    if (a == NULL)
        return NULL;

    const ff *ff = a->ff;
    ff_el *result = ff_el_init(ff);
    if (result == NULL)
        return NULL;

    for (size_t i = 0; i < ff->n; i++)
    {
        result->dig[i] = (ff->ch - a->dig[i]) % ff->ch;
    }

    return result;
}

ff_el *ff_mult(const ff_el *a, const ff_el *b)
{
    if (a == NULL)
        return NULL;
    if (b == NULL)
        return NULL;
    if (!same_ff(a, b))
        return NULL;

    const ff *ff = a->ff;

    uint8_t *dig = calloc(2 * ff->n - 1, sizeof(uint8_t));
    if (dig == NULL)
        return NULL;

    ff_el *result = ff_el_init(ff);
    if (result == NULL)
    {
        free(dig);
        return NULL;
    }

    for (size_t i = 0; i < ff->n; i++)
    {
        for (size_t j = 0; j < ff->n; j++)
        {
            dig[i + j] = (dig[i + j] + a->dig[i] * b->dig[j]) % ff->ch;
        }
    }

    for (ssize_t i = ff->n - 2; i >= 0; i--)
    {
        int8_t mul = dig[ff->n + i];
        for (ssize_t j = ff->n; j >= 0; j--)
        {
            int32_t digitn = (dig[i + j] - ff->p[j] * mul) % ff->ch;
            dig[i + j] = digitn >= 0 ? digitn : digitn + ff->ch;
        }
    }

    memcpy(result->dig, dig, ff->n * sizeof(*(result->dig)));
    free(dig);

    return result;
}

ff_el *ff_pow(const ff_el *a, uint64_t exp)
{
    const ff *ff = a->ff;
    ff_el *result = ff_identity(ff);
    if (result == NULL)
        return NULL;
    ff_el *base = ff_el_cp(a);
    if (base == NULL)
    {
        ff_el_free(result);
        return NULL;
    }

    while (exp)
    {
        if (exp % 2 == 1)
        {
            ff_el *resultn = ff_mult(result, base);
            if (resultn == NULL)
            {
                ff_el_free(result);
                ff_el_free(base);
                return NULL;
            }
            ff_el_free(result);
            result = resultn;
            exp--;
        }
        else
        {
            ff_el *basen = ff_mult(base, base);
            if (basen == NULL)
            {
                ff_el_free(result);
                ff_el_free(base);
                return NULL;
            }
            ff_el_free(base);
            base = basen;
            exp /= 2;
        }
    }
    ff_el_free(base);
    return result;
}

ff_el *ff_inverse(const ff_el *a)
{
    if (a == NULL)
        return NULL;

    const ff *ff = a->ff;
    size_t d = mpow(ff->ch, ff->n) - 2;
    return ff_pow(a, d);
}

ff_el *ff_div(const ff_el *a, const ff_el *b)
{
    if (a == NULL)
        return NULL;
    if (b == NULL)
        return NULL;

    ff_el *b_inv = ff_inverse(b);
    if (b_inv == NULL)
        return NULL;
    ff_el *result = ff_mult(a, b_inv);
    ff_el_free(b_inv);

    return result;
}

uint8_t _f2_8[] = {1, 0, 1, 1, 1, 0, 0, 0, 1};
ff _ff2_8 = {2, 8, _f2_8};
uint8_t _f2_16[] = {1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1};
ff _ff2_16 = {2, 16, _f2_16};
uint8_t _f2_32[] = {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
ff _ff2_32 = {2, 32, _f2_32};

const ff *ff2_8 = &_ff2_8;
const ff *ff2_16 = &_ff2_16;
const ff *ff2_32 = &_ff2_32;

ff_el *ff_el_uint8(uint8_t a)
{
    ff_el *result = ff_el_init(ff2_8);
    if (result == NULL)
        return NULL;

    for (size_t i = 0; i < 8; i++)
    {
        result->dig[i] = a & 1;
        a >>= 1;
    }
    return result;
}
ff_el *ff_el_uint16(uint16_t a)
{
    ff_el *result = ff_el_init(ff2_16);
    if (result == NULL)
        return NULL;

    for (size_t i = 0; i < 16; i++)
    {
        result->dig[i] = a & 1;
        a >>= 1;
    }
    return result;
}
ff_el *ff_el_uint32(uint32_t a)
{
    ff_el *result = ff_el_init(ff2_32);
    if (result == NULL)
        return NULL;

    for (size_t i = 0; i < 32; i++)
    {
        result->dig[i] = a & 1;
        a >>= 1;
    }
    return result;
}
