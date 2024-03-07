
#include "libBigInt.h"
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
void BigInt_free(BigInt *num)
{
    free(num->digits);
    free(num);
}

BigInt *addition(const BigInt *a, const BigInt *b)
{
    if (a->sign == 0)
    {
        return get_cp(b);
    }
    if (b->sign == 0)
    {
        return get_cp(a);
    }
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
    if (a->sign == 1 && b->sign == 1 && is_bigger(a, b) == 1)
    {
        BigInt *res = BigInt_init(max_size(a, b));
        res->sign = 1;
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
    if (a->sign == 1 && b->sign == 1 && is_bigger(a, b) == 0)
    {
        BigInt *res = subtraction(b, a);
        res->sign = -1;
        return res;
    }
    if (a->sign == 1 && b->sign == -1)
    {
        return addition(a, get_cp_abs(b));
    }
    if (a->sign == -1 && b->sign == 1)
    {
        BigInt *res = addition(get_cp_abs(a), get_cp_abs(b));
        res->sign = -1;
        return res;
    }
    if (a->sign == -1 && b->sign == -1)
    {
        return subtraction(get_cp_abs(b), get_cp_abs(a));
    }
    return NULL;
}
BigInt *multiplication(const BigInt *a, const BigInt *b)
{
    BigInt *res = BigInt_init(a->n + b->n);

    char car = 0;
    for (int i = 0; i < a->n; i++)
    {
        for (int j = 0; j < b->n; j++)
        {
            res->digits[i + j] += a->digits[i] * b->digits[j] + car;
            car = res->digits[i + j] / 10;
            res->digits[i + j] %= 10;
        }
        res->digits[i + b->n] += car;
        car = 0;
    }
    normalize(res);
    res->sign = a->sign * b->sign;

    return res;
}
BigInt *division(const BigInt *a_org, const BigInt *b_org)
{
    BigInt *a = get_cp_abs(a_org);
    BigInt *b = get_cp_abs(b_org);

    if (is_bigger(b, a))
    {
        return zero();
    }

    BigInt *res = BigInt_init(max_size(a, b));
    res->sign = a_org->sign * b_org->sign;

    BigInt *car = zero();
    for (int i = a->n - 1; i >= 0; i--)
    {
        car = addition(multiplication(car, read_from_int(10)), read_from_int(a->digits[i]));

        int dig = 0;
        while (is_bigger(car, b))
        {
            car = subtraction(car, b);
            dig++;
        }

        res->digits[i] = dig;
    }

    normalize(res);
    return res;
}
BigInt *div_by_2(const BigInt *a)
{
    BigInt *res = BigInt_init(a->n);
    if (a->sign == 0)
    {
        return res;
    }
    int car = 0;
    for (int i = a->n - 1; i >= 0; i--)
    {
        int dig = car * 10 + a->digits[i];
        car = dig % 2;
        res->digits[i] = dig / 2;
    }
    if (res->digits[a->n - 1] == 0)
    {
        res->digits[res->n] = '\0';
        res->n--;
    }
    res->sign = 1;
    return res;
}
BigInt *modulo(const BigInt *a, const BigInt *b)
{
    return subtraction(a, multiplication(division(a, b), b));
}
BigInt *read_from_str(char *str)
{
    BigInt *res;
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

    res = BigInt_init(size);
    res->sign = sign;
    res->n = size;
    // TODO realloc
    for (int i = 0; i < res->n; i++)
    {
        res->digits[i] = str[last_el - 1 - i] - '0';
    }

    res->digits[res->n] = '\0';
    normalize(res);
    return res;
}
char *to_str(const BigInt *a)
{
    if (a->sign == 0)
    {
        return "0";
    }
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
BigInt *read_from_int(int a)
{
    BigInt *res = BigInt_init(11);
    res->sign = 1;
    if (a < 0)
    {
        a = -a;
        res->sign = -1;
    }

    int i = 0;
    while (a != 0)
    {
        res->digits[i] = a % 10;
        a /= 10;
        i++;
    }
    res->n = i;
    normalize(res);
    return res;
}
int to_int(const BigInt *a)
{
    int res = 0;
    int k = 1;
    for (int i = 0; i < a->n; i++)
    {
        res += a->digits[i] * k;
        k *= 10;
    }
    res = res * a->sign;
    return res;
}
