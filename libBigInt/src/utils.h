#ifndef utils_H
#define utils_H

#include "libBigInt.h"

char *strrev(char *str);
void normalize(BigInt *);
int is_zero(const BigInt *);
size_t max_size(const BigInt *, const BigInt *);
BigInt *get_cp_abs(const BigInt *);
BigInt *get_cp_opposite(const BigInt *);
int is_bigger(const BigInt *, const BigInt *);

#endif