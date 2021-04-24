//Erik Svensson
/**********************************************************************/
/* lab 1 DVG C01 - Lexer OBJECT                                       */
/**********************************************************************/

/**********************************************************************/
/* Include files                                                      */
/**********************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

//#include <unistd.h>

/**********************************************************************/
/* Other OBJECT's METHODS (IMPORTED)                                  */
/**********************************************************************/
#include "keytoktab.h"

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define BUFSIZE 1024
#define LEXSIZE   30
static char buffer[BUFSIZE];
static char lexbuf[LEXSIZE];
static int  pbuf  = 0;               /* current index program buffer  */
static int  plex  = 0;               /* current index lexeme  buffer  */

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/
/**********************************************************************/
/* buffer functions                                                   */
/**********************************************************************/
/**********************************************************************/
/* Read the input file into the buffer                                */
/**********************************************************************/

static void get_prog()
{

    char c;
    int i=0;

    do {
      c = fgetc(stdin);
      if( feof(stdin) ) {
         break ;
      }

    buffer[i]=c;
    i++;
   } while(1);
    buffer[i]='$';
    


}

/**********************************************************************/
/* Display the buffer                                                 */
/**********************************************************************/

static void pbuffer()
{   printf("________________________________________________________ \n");
    printf(" THE PROGRAM TEXT\n");
    printf("________________________________________________________ \n");
    printf("%s\n",buffer);
    printf("________________________________________________________ \n");
}

/**********************************************************************/
/* Copy a character from the program buffer to the lexeme buffer      */
/**********************************************************************/


static void get_char()
{
  lexbuf[plex]=buffer[pbuf];
  plex++;
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
    if(pbuf==0) {
        get_prog();
        pbuffer();
    }

    plex=0;
    memset(lexbuf,0,strlen(lexbuf));
    while (isspace(buffer[pbuf])!=0) pbuf++;

    while(1){



         if(buffer[pbuf]==':' && buffer[pbuf+1]=='=' && plex==0) {

             get_char();
             get_char();

            return lex2tok(lexbuf);
         }

         else if (isdigit(buffer[pbuf])!=0){

           while (isdigit(buffer[pbuf])!=0) get_char();

           return number;

         }

         else if (isalpha(buffer[pbuf])!=0){

              while (isalnum(buffer[pbuf])!=0) {

                  get_char();
                }

                return key2tok(lexbuf);
         }


         else  {

          get_char();

           return lex2tok(lexbuf);
         }

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
