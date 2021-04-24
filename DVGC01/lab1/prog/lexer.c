/**********************************************************************/
/* lab 1 DVG C01 - Lexer OBJECT                                       */
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
#define BUFSIZE 1024
#define LEXSIZE   30
#define DEBUG 0
static char buffer[BUFSIZE];
static char lexbuf[LEXSIZE];
static int  pbuf  = 0;               /* current index program buffer  */
static int  plex  = 0;               /* current index lexeme  buffer  */
static void get_prog();
static void pbuffer();
char * get_lexeme();
static void id_or_key();
static void num_string();
static void special_string();



/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/
static void in(char * name)
{
  printf("\n *** In   %s\n", name);
}
/**********************************************************************/
/* buffer functions                                                   */
/**********************************************************************/
/**********************************************************************/
/* Read the input file into the buffer                                */
/**********************************************************************/

static void get_prog()
{
  int i = 0;
  char temp;
  do
  {
    temp = fgetc(stdin);
    if(temp == EOF)
    {
      break;
    }
    buffer[i] = temp;
    i++;
  }while(1);
  buffer[i] = '$';
}

/**********************************************************************/
/* Display the buffer                                                 */
/**********************************************************************/

static void pbuffer()
{
   printf("\n%s", buffer);
}

/**********************************************************************/
/* Copy a character from the program buffer to the lexeme buffer      */
/**********************************************************************/

static void get_char()
{
   lexbuf[plex] = buffer[pbuf];
   plex ++;
   pbuf++;
}

/**********************************************************************/
/* End of buffer handling functions                                   */
/**********************************************************************/

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/
/**********************************************************************/
/* Return a token                                                     */
/**********************************************************************/
int get_token()
{
  memset(lexbuf, 0, LEXSIZE);
  plex = 0;
  if(pbuf == 0)
  {
    get_prog();
    pbuffer();
  }
  //printf("buffer: %c\n", buffer[pbuf]);
  while(isspace(buffer[pbuf]) != 0)
  {
    if(DEBUG == 2) in("White_space");
    pbuf ++;
  }
  //printf("isalpha(buffer[pbuf]: %d\n", isalpha(buffer[pbuf]));

  if(isalpha(buffer[pbuf]) != 0)
  {
    get_char();
    id_or_key();
    return lex2tok(lexbuf);
  }
  else if(isdigit(buffer[pbuf]) != 0)
  {
    get_char();
    num_string();
    return number;
  }
  else
  {
    special_string();
    return lex2tok(lexbuf);
  }
}
static void id_or_key()
{
  if(DEBUG == 1 || DEBUG == 2) in("id_or_key");
  if(isalnum(buffer[pbuf]) != 0)
  {
    get_char();
    id_or_key();
  }
}
static void num_string()
{
  if(DEBUG == 1 || DEBUG == 2) in("num_string");
  if(isdigit(buffer[pbuf]) != 0)
  {
    get_char();
    num_string();
  }
}
static void special_string()
{
  if(DEBUG == 1 || DEBUG == 2) in("special_string");
  if(isspace(buffer[pbuf]) != 0)
  {
    if(DEBUG == 2) in("White_space");
    pbuf ++;
  }
  else if(buffer[pbuf]==':' && buffer[pbuf+1]=='=')
  {
    get_char();
    get_char();
  }
  else if(isalnum(buffer[pbuf]) == 0)
  {
    get_char();
  }
}

/**********************************************************************/
/* Return a lexeme                                                    */
/**********************************************************************/
char * get_lexeme()
{
  return lexbuf;
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
