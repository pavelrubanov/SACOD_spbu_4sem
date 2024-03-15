#ifndef polynom_H
#define polynom_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>


typedef struct {
  int8_t deg;     
  int8_t *coef;  
  int8_t len;     
} pol;

pol* pol_init(int8_t degree, int8_t *coeff, int8_t len);

void pol_free(pol *p);

int pol_eq(const pol *a, const pol *b);

#endif