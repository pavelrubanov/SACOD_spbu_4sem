
#include "libBigInt.h"
#include "utils.h"

BigInt *BigInt_init(size_t size)
{
    BigInt *num = malloc(sizeof(BigInt));
    if (num)
    {
        num->digits = malloc(sizeof(char) * size);
        num->n = size;
    }
    return num;
}
void BigInt_free(BigInt *num)
{
    free(num->digits);
    free(num);
}

BigInt *addition(const BigInt *a, const BigInt *b)
{
    if (a->sign == b->sign)
    {
        size_t size = max_size(a, b) + 1;
        BigInt *res = BigInt_init(size);

        for (int i = 0; i < size; i++)
        {
            char a_dig = 0;
            char b_dig = 0;
            if (i < a->n)
            {
                a_dig = a->digits[i];
            }
            if (i < b->n)
            {
                b_dig = b->digits[i];
            }
            res->digits[i] = a_dig + b_dig;
        }

        int car = 0;
        for (int i = 0; i < res->n; i++)
        {
            res->digits[i] += car;
            car = res->digits[i] / 10;
            res->digits[i] %= 10;
        }

        normalize(res);

        res->sign = a->sign;

        return res;
    }
    else
    {
        if (a->sign == -1)
        {
            return subtraction(b, get_cp_abs(a)); 
        }
        else
        {
            return (subtraction(a, get_cp_abs(b)));
        }
    }
}
BigInt *subtraction(const BigInt *a, const BigInt *b)
{
    if (a->sign == 1 && b->sign == 1 && is_bigger(a,b) == 1)
    {
        BigInt *res = BigInt_init(max_size(a,b));
        for (int i = 0; i < res->n; i++)
        {
            char a_dig = 0;
            char b_dig = 0;
            if (i < a->n)
            {
                a_dig = a->digits[i];
            }
            if (i < b->n)
            {
                b_dig = b->digits[i];
            }

            res->digits[i] = a_dig - b_dig;
        }

        int car = 0;
        for (int i = 0; i < res->n; i++)
        {
            res->digits[i] -= car;
            car = 0;
            if (res->digits[i] < 0)
            {
                res->digits[i] += 10;
                car++;
            }
        }

        normalize(res);
        return res;
    }

    if (a->sign == 1 && b->sign == 1 && is_bigger(a,b) == 0)
    {
        BigInt *res = subtraction(b,a);
        res->sign = -1;
        return res;
    }

    if (a->sign == 1 && b->sign == -1)
    {
        return addition(a,get_cp_abs(b));
    }

    if (a->sign == -1 && b->sign == 1)
    {
        BigInt* res = addition(get_cp_abs(a),get_cp_abs(b));
        res->sign = -1;
        return res;
    }

    if (a->sign == -1 && b->sign == -1)
    {
        return subtraction(get_cp_abs(b), get_cp_abs(a));
    }
}
BigInt *multiplication(const BigInt *a, const BigInt *b)
{
    
}
BigInt *division(const BigInt *a, const BigInt *b)
{
}
BigInt *modulo(const BigInt *a, const BigInt *b)
{
}
BigInt *read_from_str(char *str)
{
    BigInt *result;
    size_t size = strlen(str);
    size_t last_el = size;
    char sign;
    if (str[0] == '-')
    {
        sign = -1;
        size--;
    }
    else
    {
        sign = 1;
    }

    result = BigInt_init(size);
    result->sign = sign;
    result->n = size;

    for (int i = 0; i < result->n; i++)
    {
        result->digits[i] = str[last_el - 1 - i] - '0';
    }

    result->digits[result->n] = '\0';

    return result;
}
char *to_str(const BigInt *a)
{
    char *str = malloc(sizeof(char) * a->n);
    for (int i = 0; i < a->n; i++)
    {
        str[i] = a->digits[a->n - i - 1] + '0';
    }
    str[a->n] = '\0';
    if (a->sign == -1)
    {
        size_t len = a->n;
        str = realloc(str, (len + 1) * sizeof(char));
        memmove(str + 1, str, len + 1);
        str[0] = '-';
    }

    return str;
}
