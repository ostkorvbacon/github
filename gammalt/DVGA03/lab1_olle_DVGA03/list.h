#ifndef LIST_H
#define LIST_H

// including libraries.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

// Declaring functions.
void skrivList(node *head);
int listStor(node *head);
node *addSist(node *head, int in);
node *addFri(node *head, int in, int in2);
int hittaEl(node *head, int in);
node *bortEl(node *head, int j);
node *bortPlats(node *head, int in);
node *tomLista(node *head);
node *vandList(node *head);
node *skiftV(node *head);
node *skiftH(node *head);
node *sortList(node *head);
void skrivAdrs(node *head);
int testList(node *head);

#endif /* LIST_H */
