/**********************************************************************/
/* lab 1 DVG C01 - Parser OBJECT                                      */
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
#include "keytoktab.h"          /* when the keytoktab is added   */
#include "lexer.h"              /* when the lexer     is added   */
/* #include "symtab.h"      */       /* when the symtab    is added   */
/* #include "optab.h"       */       /* when the optab     is added   */

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define DEBUG 1
static int  lookahead=0;
static int  is_parse_ok=1;

/**********************************************************************/
/* RAPID PROTOTYPING - simulate the token stream & lexer (get_token)  */
/**********************************************************************/
/* define tokens + keywords NB: remove this when keytoktab.h is added */
/**********************************************************************/
/**********************************************************************/
/* Simulate the token stream for a given program                      */
/**********************************************************************/
static int tokens[] = {program, id, '(', input, ',', output, ')', ';',
var, id, ',', id, ',', id, ':', integer, ';',
begin, id, assign, id, '+', id, '*', number, end, '.',
               '$' };
/**********************************************************************/
/*  Simulate the lexer -- get the next token from the buffer          */
/**********************************************************************/
static int pget_token()
{
   static int i=0;
   if (tokens[i] != '$') return tokens[i++]; else return '$';
   }

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/
static void prog();
static void prog_header();
static void var_part();
static void var_dec_list();
static void var_dec();
static void id_list();
static void type();

static void stat_part();
static void stat_list();
static void stat();
static void assign_stat();
static void expr();
static void term();
static void factor();
static void operand();
/**********************************************************************/
/* The Parser functions                                               */
/**********************************************************************/
static void match(int t)
{
   if(DEBUG) printf("\n -------- In match expected: %7s found: %7s",
                    tok2lex(t), tok2lex(lookahead));
   if (lookahead == t) lookahead = pget_token();
   else {
      is_parse_ok=0;
      printf("\n *** Unexpected Token: expected: %7s found: %7s (in match)",
              tok2lex(t), tok2lex(lookahead));
      }
   }

/**********************************************************************/
/* The grammar functions                                              */
/**********************************************************************/

static void in(char * name)
{
  printf("\n *** In   %s", name);
}
static void out(char * name)
{
  printf("\n *** Out  %s", name);
}

static void prog()
{
  if(DEBUG == 1 || DEBUG == 2) in("program");
  if(lookahead == program)
  {
    prog_header();  if(DEBUG == 1 || DEBUG == 2) out("program_header");
  }
  if (lookahead == var)
  {
    var_part();  if(DEBUG == 1 || DEBUG == 2) out("var_part");
  }
  if (lookahead == begin)
  {
    stat_part();  if(DEBUG == 1 || DEBUG == 2) out("stat_part");
  }
}
static void prog_header()
{
  if(DEBUG == 1 || DEBUG == 2) in("program_header");
  match(program);
  match(id);
  match('(');
  match(input);
  match(',');
  match(output);
  match(')');
  match(';');
}
static void var_part()
{
  if(DEBUG == 1 || DEBUG == 2) in("var_part");
  match(var);
  var_dec_list(); if(DEBUG == 2) out("var_dec_list");
}
static void var_dec_list()
{
  if(DEBUG == 2) in("var_dec_list");
  var_dec(); if(DEBUG == 2) out("var_dec");
  if(lookahead == id)
  {
    var_dec(); if(DEBUG == 2) out("var_dec");
  }
}
static void var_dec()
{
  if(DEBUG == 2) in("var_dec");
  id_list(); if(DEBUG == 2) out("id_list");
  match(':');
  type(); if(DEBUG == 2) out("type");
  match(';');

}
static void id_list()
{
  //id | [id list] , id
  if(DEBUG == 2) in("id_list");
  match(id);
  if(lookahead == ',')
  {
    match(',');
    id_list(); if(DEBUG == 2) out("id_list");
  }
}
static void type()
{
  //integer | real | boolean
  if(DEBUG == 2) in("type");
  if(lookahead == integer)
    match(integer);
  else if(lookahead == real)
    match(real);
  else if(lookahead == boolean)
    match(boolean);
}
static void stat_part()
{
  if(DEBUG == 1 || DEBUG == 2) in("var_dec_list");
  match(begin);
  stat_list(); if(DEBUG == 2) out("stat_list");
  match(end);
  match('.');
}
static void stat_list()
{
  if(DEBUG == 2) in("stat_list");
  stat(); if(DEBUG == 2) out("stat");
  if(lookahead == ';')
  {
    match(';');
    stat_list(); if(DEBUG == 2) out("stat_list");
  }
}
static void stat()
{
  if(DEBUG == 2) in("stat");
  assign_stat(); if(DEBUG == 2) out("assign_stat");
}
static void assign_stat()
{
  if(DEBUG == 2) in("assign_stat");
  match(id);
  match(assign);
  expr(); if(DEBUG == 2) out("expr");
}
static void expr()
{
  if(DEBUG == 2) in("expr");
  term();
  if(lookahead == '+')
  {
    match('+');
    expr(); expr("if(DEBUG == 2) out");
  }
}
static void term()
{
  if(DEBUG == 2) in("term");
  factor();
  if(lookahead == '*')
  {
    match('*');
    term(); if(DEBUG == 2) out("term");
  }

}
static void factor()
{
  if(DEBUG == 2) in("factor");
  if(lookahead == '(')
  {
    match('(');
    expr(); if(DEBUG == 2) out("expr");
    match(')');
  }
  else
  {
    operand();  if(DEBUG == 2) out("operand");
  }
}
static void operand()
{
  if(DEBUG == 2) in("operand");
  if(lookahead == id)
    match(id);
  else if(lookahead == number)
    match(number);
}

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/

int parser()
{
   if (DEBUG) printf("\n *** if(DEBUG == 2) in  parser");
   lookahead = pget_token();       // get the first token
   prog();               // call the first grammar rule
   return is_parse_ok;             // status indicator
   }

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
