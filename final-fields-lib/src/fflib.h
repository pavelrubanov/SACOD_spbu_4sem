#ifndef fflib_H
#define fflib_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for ssize_t

typedef struct
{
    uint8_t ch;
    size_t n;
    uint8_t *p;
} ff;

typedef struct
{
    const ff *ff;
    uint8_t *dig;
} ff_el;

extern const ff *ff2_8;
extern const ff *ff2_16;
extern const ff *ff2_32;

ff *ff_init(uint8_t ch, size_t n, const uint8_t *p);
void ff_free(ff *a);

ff_el *ff_zero(const ff *a);
ff_el *ff_identity(const ff *a);

ff_el *ff_el_from_arr(const ff *a, const uint8_t *p);

ff_el *ff_el_uint8(uint8_t a);
ff_el *ff_el_uint16(uint16_t a);
ff_el *ff_el_uint32(uint32_t a);

ff_el *ff_el_init(const ff *ff);
void ff_el_free(ff_el *a);

int ff_el_equals(const ff_el *a, const ff_el *b);

ff_el *ff_sum(const ff_el *a, const ff_el *b);
ff_el *ff_sub(const ff_el *a, const ff_el *b);
ff_el *ff_negative(const ff_el *a);
ff_el *ff_mult(const ff_el *a, const ff_el *b);
ff_el *ff_inverse(const ff_el *a);
ff_el *ff_div(const ff_el *a, const ff_el *b);
ff_el *ff_pow(const ff_el *a, uint64_t exp);


#endif