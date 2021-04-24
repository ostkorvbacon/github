//Erik Svensson
/**********************************************************************/
/* lab 1 DVG C01 - Driver OBJECT                                      */
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
/**********************************************************************/
/* type definitions                                                   */
/**********************************************************************/

//static int  in_var= 0;

typedef struct tab {
	char 	* text;
	int 	token;
	} tab;

/**********************************************************************/
/* data objects (tables)                                              */
/**********************************************************************/
static tab tokentab[ ] = {
    {"id", 	        id},
	{"number", 	number},
	{":=", 	        assign},
	{"undef", 	undef},
	{"predef", 	predef},
	{"tempty", 	tempty},
	{"error",        error},
	{"type",         typ},
	{"$",            '$'},
	{"(",            '('},
	{")",            ')'},
	{"*",            '*'},
	{"+",            '+'},
	{",",            ','},
	{"-",            '-'},
	{".",            '.'},
	{"/",            '/'},
	{":",            ':'},
	{";",            ';'},
	{"=",            '='},
	{"TERROR", 	nfound}
        };


static tab keywordtab[ ] = {
	{"program", 	program},
	{"input", 	input},
	{"output", 	output},
	{"var", 	var},
	{"begin", 	begin},
	{"end", 	end},
	{"boolean", 	boolean},
	{"integer", 	integer},
	{"real", 	real},
	{"KERROR", 	nfound}
	} ;

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/
/**********************************************************************/
/* Display the tables                                                 */
/**********************************************************************/
void p_toktab()
{
    printf("\nThe program kewords\n");
    for (int i=0;i<sizeof(keywordtab)/sizeof(tab)-1;i++) printf("\n %10s  %d",keywordtab[i].text,keywordtab[i].token);
    printf("\n\nThe program tokens\n");
    for (int i=0;i<sizeof(tokentab)/sizeof(tab)-1;i++) printf("\n %10s  %d",tokentab[i].text,tokentab[i].token);
    printf("\n");
}

/**********************************************************************/
/* lex2tok - convert a lexeme to a token                              */
/**********************************************************************/
toktyp lex2tok(char * fplex)

{

		 for (int i=0;i<sizeof(keywordtab)/sizeof(tab);i++){

				if (strcmp(fplex,keywordtab[i].text)==0) return keywordtab[i].token;

		}

		 for (int i=0;i<sizeof(tokentab)/sizeof(tab);i++){

        if (strncmp(fplex,tokentab[i].text,10)==0) return tokentab[i].token;
    }

    return tokentab[0].token;

   }

/**********************************************************************/
/* key2tok - convert a keyword to a token                             */
/**********************************************************************/
toktyp key2tok(char * fplex)
{
    for (int i=0;i<sizeof(keywordtab)/sizeof(tab);i++){
        if (strcmp(fplex,keywordtab[i].text)==0 && fplex != NULL/*?*/) return keywordtab[i].token;

    }

    return tokentab[0].token;
   }

/**********************************************************************/
/* tok2lex - convert a token to a lexeme                              */
/**********************************************************************/
char * tok2lex(toktyp ftok)
{
   for (int i=0;i<sizeof(keywordtab)/sizeof(tab);i++){
        if (ftok==keywordtab[i].token) return keywordtab[i].text;
   }
    for (int i=0;i<sizeof(tokentab)/sizeof(tab);i++){
        if (ftok==tokentab[i].token) return tokentab[i].text;
   }
  return 0;
}
/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
