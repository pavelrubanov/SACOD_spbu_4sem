#ifndef libBigInt_H
#define libBigInt_H

#include <string.h>

struct BigInt {
    char* digits;
    int n;
    char sign; // 1 = +, 0 = -
};

void addition (struct BigInt, struct BigInt, struct BigInt*);
void subtraction (struct BigInt, struct BigInt, struct BigInt*);
void multiplication (struct BigInt, struct BigInt, struct BigInt*);
void division (struct BigInt, struct BigInt, struct BigInt*);
void modulo (struct BigInt, struct BigInt, struct BigInt*);
void read_from_str(char*, struct BigInt*);


#endif 
