#ifndef libBigInt_H
#define libBigInt_H

typedef struct
{
    char *digits;
    unsigned int n;
    char sign;
} BigInt;

BigInt *BigInt_init(int);
void BigInt_free(BigInt *);
BigInt *addition(BigInt, BigInt);
BigInt *subtraction(BigInt, BigInt);
BigInt *multiplication(BigInt, BigInt);
BigInt *division(BigInt, BigInt);
BigInt *modulo(BigInt, BigInt);
BigInt *read_from_str(char *);
char *to_str(BigInt);
void print_BigInt(BigInt *);
char *strrev(char *);

#endif
