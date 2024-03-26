#ifndef utils_H
#define utils_H

#include "fflib.h"

bool same_ff(const ff_el *a, const ff_el *b);
uint64_t mpow(uint64_t base, uint64_t exp);
ff_el *ff_el_cp(const ff_el *f);
void ff_el_print(const ff_el *a);

#endif