
#include "list.h"
#include "node.h"

int d1,d2;	//Variables to store input from user
int size; //Variable to know the number of nodes in list 

//Calls function in list.c to create list with position 1 being the first position 2 the second
//Pre:Pointer of type nodeEl 
//Post:Returns pointer to first node of created list
struct nodeEl * start(struct nodeEl * head){ 
	
	return cnode(head,&size);
	
	}
	
//Calls function in list.c to remove list 
//Pre:Pointer to first element in list
//Post:Removes list,pointer is set to NULL
void case0(struct nodeEl *head) {
	
	exit1(head);
	
	}
	
//Calls function in list.c to return elements in list if list exsist and prints them
//Pre:Pointer to first element in list
//Post:Returns pointer to first node of created list	
void case1(struct nodeEl *head){
	
	if (size==0) {
		
		printf(" List is empty");
	}
	
	else {
		for(int i=1;i<=size;i++) printf("\n El: %d \n",retur(head,i));

		}
	
	}
	
//Prints number of nodes in list 
//Pre:True
//Post:Prints number of nodes in list 
void case2 (){
	
	printf(" Elements in list: %d\n",size);

	}
	
//Calls function in list.c to add node to end of list 
//Pre:Pointer to first element in list or NULL pointer
//Post:Node addet to end of list, size increased by 1. Returns pointer to first element
struct nodeEl *case3(struct nodeEl *head){
	
	printf(" Int to store: ");
	scanf("%d",&d1);
	
	if (head!=NULL) nysist(head,d1); //Diferent functions called depending if the list is empty or not
			
	else {
		
		head=nynull(head,d1);
		size++;
		return head;

		}
	size++;
	return head;
	}
	
	
//Calls function in list.c to add node to chosen position in list 
//Pre:Pointer to first element in list or NULL pointer, position in or just after list and an int to store in node
//Post:Node added to list, size increased by 1. Returns pointer to first element
struct nodeEl * case4(struct nodeEl *head){
			
		printf(" Int to store: ");		
		scanf("%d",&d1);
		printf(" Position: ");
		scanf("%d",&d2);
		
		if (d2==1) {				//Diferent functions called depending on desired position 
			head=nyfirst(head,d1);
			size++;

		}
		else if (d2>1 && d2<=size+1) {
			ny(head,d1,d2);
			size++;
			return head;
		}
			
		else printf("\n Illegal position");
		return head;
	
	}
	
//Calls function in list.c to remove node with chosen value
//Pre:Pointer to first element in list, value to be removed
//Post:Node removed and size decreased by 1 if it is first occurrence with selected value
struct nodeEl * case5(struct nodeEl *head){
	
			if (size==0) {					//Checks if list is empty
					printf("List empty");
					return NULL;
				}
			printf(" Int to remove: ");		
			scanf("%d",&d1);
			
			if (sok(head,d1)==0) {
				
				printf(" Int not in list");	//If not found do nothing and alert user
				return head;
			}
			
			else if (sok(head,d1)==1) {		//If found function in list.c called depends on position in list	
				
				head=rem1(head,size);
				size--;
				return head;
	
				}
				
			else {
				
				remint(head,d1);
				size--;
				return head;
			}
	
	}
	
//Calls function in list.c to remove node at chosen position
//Pre:Pointer to first element in list, position to be removed
//Post:Node removed and size decreased by 1 if position is in list
struct nodeEl * case6(struct nodeEl *head){
	
	if (size==0) {
		printf(" list empty"); //Checks if list is empty
		return NULL;
	}
	printf(" Position to remove: ");
	scanf("%d",&d1);						//Function in list.c called depends on position
	
	if (d1<=size && d1!=1) {
		rem(head,d1);
		size--;
	}
	else if (d1==1 && size>0) {
				
			head=rem1(head,size);
			size--;
			return head;
	}
			
	else printf(" Illegal position");  
	
	return head;
	}
	
//Calls function in list.c to remove list
//Pre:Pointer to first element in list
//Post:List removed pointer set to NULL and size set to 0
struct nodeEl * case7(struct nodeEl *head){
	head=exit1(head);
	size=0;
	return head;
	}
	
//Calls function in list.c to invert list
//Pre:Pointer to first element in list
//Post:List inverted
void case8(struct nodeEl *head){
	
	turn(head,size);
	
	}
	
//Calls function in list.c to shift list left
//Pre:Pointer to first element in list
//Post:List shifted left	
void case9(struct nodeEl *head){
	
	shiftl(head,size);
	
	}
	
//Calls function in list.c to shift list right
//Pre:Pointer to first element in list
//Post:List shifted right	
void case10(struct nodeEl *head){
	shiftr(head,size);
	}
	
//Calls function in list.c to sort list lowest value to largest
//Pre:Pointer to first element in list
//Post:List sorted
void case11(struct nodeEl *head){
	
	sort(head,size);
	
	}
	
//Prints start address
//Pre:Pointer to first element in list
//Post:Start address printed
void case12(struct nodeEl *head){
	
	printf(" Start address: %ld\n",(long)&head);
	
	}

