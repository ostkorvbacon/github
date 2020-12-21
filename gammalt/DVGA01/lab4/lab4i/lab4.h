#ifndef LAB4_h
#define LAB4_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define RSIZE 10
#define NSIZE 20
typedef struct{
  char namn[NSIZE];
  char pnum[NSIZE];
}person;
typedef struct{
  person agare1;
  person agare2;
}agare;
typedef struct{
  char marke[NSIZE];
  char arsmodell[NSIZE];
  char reg[NSIZE];
  char count[NSIZE];
  agare agare;
}bil;
void finfile(bil b[RSIZE], int *ant);
void foutfile(bil b[RSIZE], int ant);




#endif
