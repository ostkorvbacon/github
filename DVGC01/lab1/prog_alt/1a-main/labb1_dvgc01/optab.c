//Erik Svensson
/**********************************************************************/
/* lab 1 DVG C01 - Operator Table OBJECT                              */
/**********************************************************************/

/**********************************************************************/
/* Include files                                                      */
/**********************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/**********************************************************************/
/* Other OBJECT's METHODS (IMPORTED)                                  */
/**********************************************************************/
#include "keytoktab.h"

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define NENTS 4
#define ROWS 9

static int optab[][NENTS] = {
   {'+', integer, integer, integer},
   {'+', real,    real,    real},
   {'+', integer, real,    real},
   {'+', real,    integer, real},
   {'*', integer, integer, integer},
   {'*', real,    real,    real},
   {'*', integer, real,    real},
   {'*', real,    integer, real},
   {'$', undef,   undef,   undef}
   };

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/
/**********************************************************************/
/* display the op tab                                                 */
/**********************************************************************/
void p_optab()
{
   
    printf("________________________________________________________ \n");
    printf("THE OPERATOR TABLE\n");
    printf("________________________________________________________ \n");
    printf("   operator        arg1         arg2           result\n");
    printf("________________________________________________________ \n");
  
    for (int i=0;i<ROWS;i++) printf("     %c,       %10s,     %10s,     %10s\n",optab[i][0],tok2lex(optab[i][1]),tok2lex(optab[i][2]),tok2lex(optab[i][3]));
    
    printf("________________________________________________________ \n");
 
    
   }

/**********************************************************************/
/* return the type of a binary expression op arg1 arg2                */
/**********************************************************************/
int get_otype(int op, int arg1, int arg2)
{  
   for (int i=0;i<ROWS;i++){
        if (op==optab[i][0] && arg1==optab[i][1] && arg2==optab[i][2]) return optab[i][3];
               
   }
    return undef;
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/