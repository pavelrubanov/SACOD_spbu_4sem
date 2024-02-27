#ifndef utils_H
#define utils_H

#include "libBigInt.h"

char *strrev(char *str);
void normalize(BigInt *);
_Bool is_zero(const BigInt *);
BigInt* max_bigInt(const BigInt *, const, BigInt *);
BigInt* min_bigInt(const BigInt *, const BigInt *);
size_t max_size(const BigInt *, const BigInt *);

#endif