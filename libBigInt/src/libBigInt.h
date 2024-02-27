#ifndef libBigInt_H
#define libBigInt_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *digits;
    size_t n;
    char sign;
} BigInt;

BigInt *BigInt_init(size_t);
void BigInt_free(BigInt *);
BigInt *addition(BigInt, BigInt);
BigInt *subtraction(BigInt, BigInt);
BigInt *multiplication(BigInt, BigInt);
BigInt *division(BigInt, BigInt);
BigInt *modulo(BigInt, BigInt);
BigInt *read_from_str(char *);
char *to_str(const BigInt *);

#endif
