#include "utils.h"

void normalize(BigInt * num)
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
