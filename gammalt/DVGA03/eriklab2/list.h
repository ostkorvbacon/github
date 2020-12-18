#include <stddef.h> //Included libraries
#include <stdio.h>
#include <stdlib.h>
#include "node.h"

//function prototypes 
	

int storlek(struct nodeEl *head);
int nysist(struct nodeEl *head,int a);
int ny(struct nodeEl *head,int a,int pos);
struct nodeEl *nyfirst(struct nodeEl *head,int a);
struct nodeEl * exit1(struct nodeEl *head);
int isEmp(struct nodeEl *head);
struct nodeEl *nynull(struct nodeEl *head,int a);
int sok(struct nodeEl *head,int a);
int sok2(struct nodeEl *head,int a);
int retur(struct nodeEl *head,int pos);
int remint(struct nodeEl *head,int a);
int rem(struct nodeEl *head,int pos);
struct nodeEl * rem1(struct nodeEl *head,int size);
int skriv2(struct nodeEl *head, int *temp,int size);
int skriv3(struct nodeEl *head, int *temp,int size);
int turn(struct nodeEl *head,int size);
int sort(struct nodeEl *head,int size);
int shiftl(struct nodeEl *head,int size);
int shiftr(struct nodeEl *head,int size);
struct nodeEl * cnode(struct nodeEl * head,int *size);
