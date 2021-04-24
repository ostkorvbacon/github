//Erik Svensson
int expr();
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
 #include "keytoktab.h"         /* when the keytoktab is added   */
 #include "lexer.h"              /* when the lexer     is added   */
 #include "symtab.h"            /* when the symtab    is added   */
 #include "optab.h"              /* when the optab     is added   */

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define DEBUG 0
static int  lookahead=0;
static int  is_parse_ok=1;

void get_prog();
void pbuffer();

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/

/**********************************************************************/
/* The Parser functions                                               */
/**********************************************************************/
static void match(int t)
{
   if(DEBUG) printf("\n *** In  match   Expected %s found  %4s  lexeme: %s ",
                    tok2lex(t), tok2lex(lookahead),get_lexeme());
   if (lookahead == t) lookahead = get_token();
   else {
      is_parse_ok=0;

      printf("SYNTAX:   Symbol expected %s found %s \n",
              tok2lex(t),get_lexeme());

      }
   }

/**********************************************************************/
/* The grammar functions                                              */
/**********************************************************************/
static void program_header()
{
   if (DEBUG) printf("\n *** In  program_header ");
   match(program); if (lookahead!=id){addp_name("???");} else {addp_name(get_lexeme());} match(id); match('('); match(input);
   match(','); match(output); match(')'); match(';');
    if (DEBUG) printf("\n *** Out program_header\n");
   }

void type() {
    if (DEBUG) printf("\n *** In type");
    if(lookahead==integer) {
        match(integer);
        setv_type(integer);
    }
    else if(lookahead==real) {
        match(real);
        setv_type(real);
    }
    else if (lookahead==boolean){
       match(boolean);
        setv_type(boolean);
         }
    else {
      setv_type(error);
      printf("SYNTAX:   Type name expected found %s \n", get_lexeme());
          is_parse_ok=0;
          }
    if (DEBUG) printf("\n *** Out type");
}

void id_list() {
    if (DEBUG) printf("\n *** In  id_list");
    if (lookahead == id){
    if (find_name(get_lexeme())) {

        printf("SEMANTIC: ID already declared: %s\n", get_lexeme());
        is_parse_ok=0;
    }
    else {
        addv_name(get_lexeme());

    }
    match(id);
  }
  else {
    printf("SYNTAX:   ID expected found  %s \n", get_lexeme());
    is_parse_ok = 0;

  }
    if (lookahead==',') {
        match(',');
        id_list();
        }
  if (DEBUG) printf("\n *** Out id_list");
}


void var_dec(){
    if (DEBUG) printf("\n *** In  var_dec");
    id_list();
    match(':');
    type();
    match(';');
    if (DEBUG) printf("\n *** Out var_dec");
}

void var_dec_list(){
    if (DEBUG) printf("\n *** In  var_dec_list");
    var_dec();
    if (lookahead==id) {

      var_dec_list();}
    if (DEBUG) printf("\n *** Out var_dec_list");
}

void var_part(){
    if (DEBUG) printf("\n *** In  var_part   ");
    match(var);
    var_dec_list();
     if (DEBUG) printf("\n *** Out var_part\n");

   }
int operand(){
    if (DEBUG) printf("\n *** In operand");


    if(lookahead==id) {
        if (!find_name(get_lexeme())) {
          printf("SEMANTIC: ID NOT declared: %s\n", get_lexeme());
        is_parse_ok=0;}
        int arg1 = get_ntype(get_lexeme());
        match(id);
        return arg1;
    }
    else if (lookahead==number) {
      match(number);
      if (DEBUG) printf("\n *** Out operand");
      return integer;
    }

    else {
      printf("SYNTAX:   Operand Expected \n");
      return error;

      }
}

int factor(){
      int arg1;
     if (DEBUG) printf("\n *** In factor");
    if(lookahead=='(') {
        match('(');
        arg1=expr();
        match(')');
    }
    else {
        arg1=operand();
    }

     if (DEBUG) printf("\n *** Out factor");
     return arg1;
}

int term(){
      if (DEBUG) printf("\n *** In term");
    int arg1=factor();

    if(lookahead=='*'){
        match('*');

    return get_otype('*', term(),arg1);
    }


    if (DEBUG) printf("\n *** Out term");
    return arg1;
}


int expr(){

    if (DEBUG) printf("\n *** In expr");

    int arg1=term();
     if(lookahead=='+'){
        match('+');
        return get_otype('+',expr(), arg1);
      }

      if (DEBUG) printf("\n *** Out expr");
      return arg1;
}

void assign_stat(){
    if (DEBUG) printf("\n *** Ïn assign_stat");
    int arg1=get_ntype(get_lexeme());
    if (!find_name(get_lexeme()) && lookahead == id) {
      printf("SEMANTIC: ID NOT declared: %s\n", get_lexeme());
      is_parse_ok=0;
    }
    if(lookahead == id)
  	{
  		match(id);
  	}

  	else
  	{
  		printf("SYNTAX:   ID expected found %s \n", get_lexeme());
  	}

    match(assign);
    int arg2=expr();
    if(arg1==undef)
  	{
  		arg1 = error;
  	}
  	if(arg1 !=arg2)
  	{
  		printf("SEMANTIC: Assign types: %s := %s\n", tok2lex(arg1), tok2lex(arg2));
  		is_parse_ok = 0;
  	}

    if (DEBUG) printf("\n *** Out assign_stat");

}

void stat(){
       if (DEBUG) printf("\n *** Ïn stat");
    assign_stat();
    if (DEBUG) printf("\n *** Out stat");
}

void stat_list(){
       if (DEBUG) printf("\n *** In stat_list");
   stat();
    if (lookahead==';') {
        match(';');
        stat_list();
        }
   if (DEBUG) printf("\n *** Out stat_list");
}

void stat_part(){
    if (DEBUG) printf("\n *** In stat_part");
    match(begin);
    stat_list();
    match(end);
    match('.');
     if (DEBUG) printf("\n *** Out stat_part");
}

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/

int parser()
{
   if (DEBUG) printf("\n *** In  program");
   lookahead = get_token();
   if (lookahead=='$') {
     is_parse_ok=0;
     printf("WARNING:  Input file is empty \n");
     return is_parse_ok;

   }
   program_header();
   var_part();
  stat_part();

   if(lookahead != '$')
 { is_parse_ok = 0;
   printf("SYNTAX:   Extra symbols after end of parse! \n");
   printf("         ");
   while(lookahead != '$')
   {
     printf(" %s", get_lexeme());
     match(lookahead);
   }

 }
 return is_parse_ok;
   }

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
