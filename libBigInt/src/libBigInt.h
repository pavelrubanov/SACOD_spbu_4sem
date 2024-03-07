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

void BigInt_free(BigInt *);
BigInt *addition(const BigInt *, const BigInt *);
BigInt *subtraction(const BigInt *, const BigInt *);
BigInt *multiplication(const BigInt *, const BigInt *);
BigInt *division(const BigInt *, const BigInt *);
BigInt *div_by_2(const BigInt *);
BigInt *modulo(const BigInt *, const BigInt *);
BigInt *read_from_str(char *);
BigInt *read_from_int(int);
char *to_str(const BigInt *);
int to_int(const BigInt *);

#endif
