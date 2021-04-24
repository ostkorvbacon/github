/**********************************************************************/
/* lab 1 DVG C01 - Symbol Table OBJECT                                */
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

  set_name(numrows, fname);
  set_role(numrows, frole);
  set_type(numrows, ftype);
  set_size(numrows, fsize);
  set_addr(numrows, faddr);
  numrows ++;
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
    startp = numrows;
}

/**********************************************************************/
/*  return a reference to the ST (index) if name found else nfound    */
/**********************************************************************/
 static int get_ref(char * fpname)
 {
   int i;
   for(i = startp; i < numrows; i++)
   {
     if (strcmp(fpname, get_name(i)) == 0)
     {
       return i;
     }
   }
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
  int i;
  for(i = startp; i < numrows; i++)
  {
    printf("    %7s    %7s    %7s      %3d       %3d \n",
    get_name(i), tok2lex(get_role(i)), tok2lex(get_type(i)), get_size(i), get_addr(i));
  }
}

void p_symtab()
{
  int size = 0;
  size = get_addr(numrows-1) + get_size(numrows-1);
  set_size(startp, size);
  printf("\n THE SYMBOL TABLE\n");
  printf("________________________________________________________\n");
  printf("       NAME       ROLE       TYPE      SIZE      ADDR\n");
  printf("________________________________________________________\n");
  p_symrow(startp);
  printf("\tSTATIC STORAGE REQUIRED is %d BYTES\n", size);
  printf("________________________________________________________ \n");
}

/**********************************************************************/
/*  Add a program name to the symbol table                            */
/**********************************************************************/
void addp_name(char * fpname)
{
  initst();
  addrow(fpname, program, program, 0, 0);
}

/**********************************************************************/
/*  Add a variable name to the symbol table                           */
/**********************************************************************/
void addv_name(char * fpname)
{
addrow(fpname, var, 0, 0, 0);
}

/**********************************************************************/
/*  Find a name in the the symbol table                               */
/*  return a Boolean (true, false) if the name is in the ST           */
/**********************************************************************/
int find_name(char * fpname)
{
  int i;
  for(i = 0; i < numrows; i++)
  {
    if (strcmp(fpname, get_name(i)) == 0)
    {
      return 1;
    }
  }
  return 0;
}

/**********************************************************************/
/*  Set the type of an id list in the symbol table                    */
/**********************************************************************/
void setv_type(toktyp ftype)
{
  int i;
  for(i = startp; i < numrows; i++)
  {
    if(get_type(i) == 0)
    {
      set_type(i, ftype);
      if(strcmp(tok2lex(ftype), "integer") == 0)
      {
        set_size(i, sizeof(int));
      }
      else if(strcmp(tok2lex(ftype), "real") == 0)
      {
        set_size(i, sizeof(double));
      }
      else if(strcmp(tok2lex(ftype), "boolean") == 0)
      {
        set_size(i, 4);
      }
      set_addr(i, get_size(i-1) + get_addr(i-1));
    }
  }
}

/**********************************************************************/
/*  Get the type of a variable from the symbol table                  */
/**********************************************************************/
toktyp get_ntype(char * fpname)
{
  int i;
  for(i = 0; i < numrows; i++)
  {
    if (strcmp(fpname, get_name(i)) == 0)
    {
      if(get_role(i) == var)
        return get_type(i);
    }
  }
  return 0;
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
