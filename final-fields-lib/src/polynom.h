#ifndef polynom_H
#define polynom_H

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct 
{
  int8_t deg;     
  int8_t *coef;  
  int8_t len;     
} pol;

pol* pol_init(int8_t degree, int8_t *coeff, int8_t len);

void pol_free(pol *p);

int pol_eq(const pol *a, const pol *b);

void pol_deg_normalize(pol* a);
void pol_coef_normalize(pol* a, int8_t p);

pol* pol_zero (size_t len);

pol* pol_sum (const pol* a, const pol* b);
pol* pol_diff (const pol* a, const pol* b);
pol* pol_mult (const pol* a, const pol* b);
pol* pol_div (const pol* a, const pol* b);

//utils:

int8_t mod (int8_t a, int8_t b);

#endif