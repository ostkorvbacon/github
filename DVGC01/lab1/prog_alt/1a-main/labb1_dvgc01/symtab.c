//Erik Svensson
/**********************************************************************/
/* lab 1 DVG C01 - Symbol Table OBJECT                                */
/**********************************************************************/

/**********************************************************************/
/* Include files                                                      */
/**********************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

/**********************************************************************/
/* Other OBJECT's METHODS (IMPORTED)                                  */
/**********************************************************************/
#include "keytoktab.h"

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define TABSIZE 1024                   /* symbol table size           */
#define NAMELEN   20                   /* name length                 */

typedef char tname[NAMELEN];

static tname  name[TABSIZE];
static toktyp role[TABSIZE];
static toktyp type[TABSIZE];
static int    size[TABSIZE];
static int    addr[TABSIZE];

static int numrows=0;                  /* number of rows in the ST    */
static int startp =0;                  /* start position program in ST*/
static int progsize=0;
void setprogsize(int progsize);

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/
/**********************************************************************/
/*  GET methods (one for each attribute)                              */
/**********************************************************************/
static char * get_name(int ftref)   { return name[ftref]; }
static toktyp get_role(int ftref)   { return role[ftref]; }
static toktyp get_type(int ftref)   { return type[ftref]; }
static int    get_size(int ftref)   { return size[ftref]; }
static int    get_addr(int ftref)   { return addr[ftref]; }

/**********************************************************************/
/*  SET methods (one for each attribute)                              */
/**********************************************************************/
static void set_name(int ftref, char * fpname) { strcpy(name[ftref],
                                                        fpname);}
static void set_role(int ftref, toktyp frole)  { role[ftref] = frole; }
static void set_type(int ftref, toktyp ftype)  { type[ftref] = ftype; }
static void set_size(int ftref, int    fsize)  { size[ftref] = fsize; }
static void set_addr(int ftref, int    faddr)  { addr[ftref] = faddr; }

/**********************************************************************/
/*  Add a row to the symbol table                                     */
/**********************************************************************/
static void addrow(char *fname, toktyp frole, toktyp ftype,
                   int fsize, int faddr)
{
    set_name(numrows,fname);
    set_role(numrows,frole);
    set_type(numrows,ftype);
    set_size(numrows,fsize);
    set_addr(numrows,faddr);
    numrows++;


}
/**********************************************************************/
/*  Initialise the symbol table                                       */
/**********************************************************************/
static void initst()
{
    addrow(tok2lex(predef),  typ, predef, 0, 0);
    addrow(tok2lex(undef),   typ, predef, 0, 0);
    addrow(tok2lex(error),   typ, predef, 0, 0);
    addrow(tok2lex(integer), typ, predef, 4, 0);
    addrow(tok2lex(boolean), typ, predef, 4, 0);
    addrow(tok2lex(real),    typ, predef, 8, 0);
}

/**********************************************************************/
/*  return a reference to the ST (index) if name found else nfound    */
/**********************************************************************/
 static int get_ref(char * fpname)
 {
   for (int i=0;i<numrows;i++) if (strcmp(name[i],fpname)==0) return i;
   return nfound;
 }

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/
/**********************************************************************/
/*  Display the symbol table                                          */
/**********************************************************************/
static void p_symrow(int ftref)
{
   printf("   %8s   %8s   %8s  %8d  %8d \n",get_name(ftref),tok2lex(get_role(ftref)),tok2lex(get_type(ftref)),get_size(ftref),get_addr(ftref));

   }

void p_symtab()

{  int totsize=0;
    printf("________________________________________________________ \n");
    printf(" THE SYMBOL TABLE\n");
    printf("________________________________________________________ \n");
    printf("       NAME       ROLE       TYPE      SIZE      ADDR     \n");
    printf("________________________________________________________ \n");
    for (int i=startp;i<numrows;i++) {
        p_symrow(i);
        if (role[i]!=program) totsize=totsize+size[i];

    }
    printf("________________________________________________________ \n");
    printf(" STATIC STORAGE REQUIRED is %d BYTES\n",totsize);
    printf("________________________________________________________ \n");
   }

/**********************************************************************/
/*  Add a program name to the symbol table                            */
/**********************************************************************/
void addp_name(char * fpname) {
  initst();

   startp=numrows;
   addrow(fpname,program,program,0,0);


   }

/**********************************************************************/
/*  Add a variable name to the symbol table                           */
/**********************************************************************/
void addv_name(char * fpname) {

    addrow(fpname,var,-1,0,0);
}

/**********************************************************************/
/*  Find a name in the the symbol table                               */
/*  return a Boolean (true, false) if the name is in the ST           */
/**********************************************************************/
int find_name(char * fpname) {

    for (int i=0;i<numrows;i++) if (strcmp(name[i],fpname)==0) return true;
    return false;
}

/**********************************************************************/
/*  Set the type of an id list in the symbol table                    */
/**********************************************************************/
void setv_type(toktyp ftype) {

   for (int i=startp;i<numrows;i++){
       if (type[i]==-1) {
           type[i]=ftype;
          size[i]=get_size(get_ref(tok2lex(ftype)));

           if (i!=0) addr[i]=addr[i-1]+size[i-1];
           else addr[i]=0;
           progsize=progsize+size[i];
           setprogsize(progsize);
       }

   }

}

void setprogsize(int progsize){

    for (int i=0;i<numrows;i++) if (role[i]==program) size[i]=progsize;

}

/**********************************************************************/
/*  Get the type of a variable from the symbol table                  */
/**********************************************************************/
toktyp get_ntype(char * fpname) {

    for (int i=0;i<numrows;i++) if (strcmp(name[i],fpname)==0) return type[i];

        return error;
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
