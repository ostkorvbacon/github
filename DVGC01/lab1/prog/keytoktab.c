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
  int i;
  printf("________________________________________________________ \n");
  printf("THE PROGRAM KEYWORDS \n");
  printf("________________________________________________________\n");
  for(i = 0; i < (int)sizeof(keywordtab)/16-1; i++)
  {
    printf("%11s %5d\n", keywordtab[i].text, keywordtab[i].token);
  }
  printf("________________________________________________________ \n");
  printf("THE PROGRAM TOKENS \n");
  printf("________________________________________________________\n");
  for(i = 0; i < (int)sizeof(tokentab)/16-1; i++)
  {
    printf("%11s %5d\n", tokentab[i].text, tokentab[i].token);
  }
}

/**********************************************************************/
/* lex2tok - convert a lexeme to a token                              */
/**********************************************************************/
toktyp lex2tok(char * fplex)
{
  int i;
  if(fplex == NULL)
    return 0;
  for(i = 0; i < (int)sizeof(keywordtab)/16-1; i++)
  {
    if(strcmp(fplex, keywordtab[i].text) == 0)
      return keywordtab[i].token;
  }
  for(i = 0; i < (int)sizeof(tokentab)/16; i++)
  {
    if(strcmp(fplex, tokentab[i].text) == 0)
      return tokentab[i].token;
  }

   return 258;
}

/**********************************************************************/
/* key2tok - convert a keyword to a token                             */
/**********************************************************************/
toktyp key2tok(char * fplex)
{
  int i;
  if(fplex == NULL)
    return 0;
  for(i = 0; i < (int)sizeof(keywordtab)/16-1; i++)
  {
    if(strcmp(fplex, keywordtab[i].text) == 0)
      return keywordtab[i].token;
  }

   return 258;
}

/**********************************************************************/
/* tok2lex - convert a token to a lexeme                              */
/**********************************************************************/
char * tok2lex(toktyp ftok)
{
  int i;
  for(i = 0; i < (int)sizeof(keywordtab)/16-1; i++)
  {
    if(ftok == keywordtab[i].token)
      return keywordtab[i].text;
  }
  for(i = 0; i < (int)sizeof(tokentab)/16; i++)
  {
    if(ftok == tokentab[i].token)
      return tokentab[i].text;
  }

   return 0;
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
