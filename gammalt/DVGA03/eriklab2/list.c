
#include "list.h"
#include "node.h"


//Function to create a 3 node list with position 1 being the first position 2 the second
//Pre:Pointer of type nodeEl, pointer to inv to store number of nodes 
//Post:Returns pointer to first node of created list, number of nodes stored in memory piontet to by size
struct nodeEl * cnode(struct nodeEl * head,int *size) {
	
	struct nodeEl *node1 = malloc(sizeof(struct nodeEl)); //Alocates memory for 3 nodes 
	struct nodeEl *node2= malloc(sizeof(struct nodeEl));
	struct nodeEl *node3= malloc(sizeof(struct nodeEl));

	node1->el=1;	//Add data to nodes
	node2->el=2;
	node3->el=3;
	*size=3;
	node1->next = node2; //Link nodes
	node2->next = node3;
	node3->next = NULL;
	
	return node1;		//Return first node
	}


//Function to count number of nodes in list. Not used (Using the variable size is more efficient)but required to be here by instructions
//Pre:Pointer to first node
//Post:Returns numer of nodes
int storlek(struct nodeEl *head)

{	
	if (head!=NULL){
		struct nodeEl node=*head;
		return 1+storlek(node.next);
	
	}
	return 0;
	}
	


//Function to add node to end of list
//Pre:Pointer to first node, int to be stored
//Post:New node with sepecified int value added to end of list	
int nysist(struct nodeEl *head,int a){
	
	struct nodeEl *node=head;
	
	while (node->next!=NULL) node=node->next;	//Moves to end of list
	
	struct nodeEl *new = malloc(sizeof(struct nodeEl)); //New node created and linked to end of list
	new->el=a;
	new->next=NULL;
	node->next=new;

	return 0;
	}
	
	
//Function to add node to list
//Pre:Pointer to first node, int to be stored, position of new node 
//Post:New node with sepecified int value added to end of list	
int ny(struct nodeEl *head,int a,int pos){
	
	struct nodeEl *node1=head;
	struct nodeEl *node2=head;

	for (int i=0;i<pos-2;i++) {		//Finds nodes on "both sides" of new nodes position
		node1=node1->next;
	}
		
	for (int i=0;i<pos-1;i++) {
		if (node2->next!=NULL) node2=node2->next;
		else node2=NULL;
	}
	
	
	
	struct nodeEl *new = malloc(sizeof(struct nodeEl));		//Creates new node an link it to neighbors
	new->el=a;
	new->next=node2;
	node1->next=new;

	return 0;
	}
	
//Function to add node to begining of list
//Pre:Pointer to first node, int to be stored
//Post:New node with sepecified int value added to begining of list. Returns created node as new first node
struct nodeEl *nyfirst(struct nodeEl *head,int a){
	
		struct nodeEl *node1=head;
		struct nodeEl *new = malloc(sizeof(struct nodeEl));
		new->el=a;
		new->next=node1;
		
		return new;
	}
	
//Function to remove list
//Pre:Pointer to first node
//Post:Memmory of nodes dealocated and pointer to first node is returned as NULL		
struct nodeEl * exit1(struct nodeEl *head) {
	
	struct nodeEl *node=head;
	while (head!=NULL) { 
		
		node=head->next; //Jumps from node to node ande dealocates its memory
		free(head);
		head=node;		

	}
	
	return NULL;
    }
    
    
//Function to check if list is empty. Not used but required to be here by instructions
//Pre:Pointer to first node
//Post:Returns 1 if pointer to first node is NULL. If not returns 0
int isEmp(struct nodeEl *head){
	if (head==NULL) return 1;
	return 0;
	
	
	}
	
//Function to add node to begining of empty list
//Pre:Pointer to first node, int to be stored
//Post:New node with sepecified int value added to begining of list. Returns created node as new first node
struct nodeEl *nynull(struct nodeEl *head,int a){
	
	head=malloc(sizeof(struct nodeEl));
	head->el=a;
	head->next=NULL;
	return head;
	
	}
	
//Searches for an int in the list
//Pre: Pointer to linked list,int to be found
//post: Returns position of int if found in list and 0 if not
int sok(struct nodeEl *head,int a)
{
	
	int pos=0;   //Position in list, increaed when a new node is accesed
	struct nodeEl *node=head;
	while (node->next!=NULL) {
		pos++;
		if (a==node->el) return pos; // Checks list if data matches int to be found
		node=node->next;
		}
		pos++;						
		if (a==node->el) return pos;
		return 0;
	}

//Searches for an int in the list. Not used but required to be here by instructions
//Pre: Pointer to linked list,Int to be found
//post: returns 1 if found in list and 0 if not
int sok2(struct nodeEl *head,int a){
	
	if (sok(head,a)>0) return 1;
	
	return 0;
	
	}

//Returns int in node at given position.
//Pre: Pointer to linked list, position of node in list 
//Post:Returns int stored in node at position
int retur(struct nodeEl *head,int pos){
	
	struct nodeEl *node=head;
	for (int i=1;i<pos;i++){
		node=node->next;
		
		}
		return node->el;	
}

//Searches for an int in the list and removes first occurence of it
//Pre: Pointer to linked list,int in list
//post:Node with int removed 
int remint(struct nodeEl *head,int a){
	
	struct nodeEl *node1=head;
	struct nodeEl *node2=head;
	
	int pos=sok(head,a);		//Calls sok to find position of int 
	
	
		
	for (int i=0;i<pos-2;i++) {
		if (node1->next!=NULL) node2=node2->next;		//Finds neighbors 
		
	}	

	for (int i=0;i<pos-1;i++) {
		if (node1->next!=NULL) node1=node1->next;
		
	}
	
	
	node2->next=node1->next;		//Links neighbors bypassing node
	free(node1);					//Dealocates memory
	
	

	return 0;
	
	
	
	}
	

//Removes node at given position
//Pre: Pointer to linked list,position in list
//post:Node at position removed 
int rem(struct nodeEl *head,int pos){
	
	struct nodeEl *node1=head;
	struct nodeEl *node2=head;
	
	
	if (pos==0) return 0;
	
		
	for (int i=0;i<pos-2;i++) {
		if (node1->next!=NULL) node2=node2->next;  //Finds neighbors 
		
	}	

	for (int i=0;i<pos-1;i++) {
		if (node1->next!=NULL) node1=node1->next;
		
	}
		
	node2->next=node1->next;    //Links neighbors bypassing node
	free(node1);				//Dealocates memory
	
	

	return 0;
	}


//Removes first node
//Pre: Pointer to linked list, number of elements in list
//post:First node removed and returns new first node, NULL if no other nodes
struct nodeEl * rem1(struct nodeEl *head,int size){
	
	struct nodeEl *node=head;
	
	if (size==1) {   //Checks if the first node is alone
				
		free(node);
		return NULL;
		}
		
	head=head->next;
	free(node);
	
	return head;
	
	}
	

//Writes list data inverted to array
//Pre: Pointer to linked list, array large enough to store list,size of list  
//post:Inverted list data stored in array	
int skriv2(struct nodeEl *head, int *temp,int size)

{	

	if (head!=NULL){
		struct nodeEl node=*head;
		temp[size-1]=node.el;
		skriv2(node.next,temp,size-1);
	}
	return 0;
	}

//Writes array to list
//Pre: Pointer to linked list, array to write (must be smaler then list),size of array 
//post:Data from array stored in list	
int skriv3(struct nodeEl *head, int *temp,int size)

{	

		struct nodeEl *node=head;
		for (int i=0;i<size;i++){
		node->el=temp[i];
		node=node->next;
		}
	
	return 0;
	}
	
//Inverts list
//Pre: Pointer to linked list, size of list
//post:List inverted	
int turn(struct nodeEl *head,int size){
	int *temp=(int*) malloc(size*sizeof(int)); //Alocated array of same size as list
	
	skriv2(head,temp,size); 		//Calls skriv2 to invert list to array
	
	skriv3(head,temp,size);			//Calls skriv3 to store inverted array in list
	
	free(temp);			//Dealocates array
	return 0;
	}	

//Sorts list 
//Pre: Pointer to linked list, size of list
//post:List sorted	
int sort(struct nodeEl *head,int size){
	
	int k=0;
	int *temp=(int*) malloc(size*sizeof(int)); //Alocated array of same size as list
	int temp2;	
									
	skriv2(head,temp,size);  		//Calls skriv2 to store list in array, the invertion is irrelevant as the data is then sorted
	while (k==0) {				//Normal bubble sort
		k=1;
		for (int i=0;i<size-1;i++) {
			if (temp[i]>temp[i+1]){
				
				k=0;
				temp2=temp[i+1];
				temp[i+1]=temp[i];
				temp[i]=temp2;
				
			} 	
		}	
	}
	skriv3(head,temp,size);		//Calls skriv3 to store sorted array in list
	free(temp);					//Dealocates array
	return 0;
}

//Shift list left 
//Pre: Pointer to linked list, size of list
//post:List shifted left		
int shiftl(struct nodeEl *head,int size){
	
	int *temp=(int*) malloc(size*sizeof(int)); //Alocated array of same size as list
	int temp2;
	struct nodeEl *node=head;
	
	for (int i=0;i<size;i++){ //Store list in array
		temp[i]=node->el;
		node=node->next;
		}
	
	temp2=temp[0];			//Store away first element in array to keep it form being overritten in next step 
	
	for (int i=0;i<size-1;i++){ //Move all elements one step to the left
		temp[i]=temp[i+1];
	}
	temp[size-1]=temp2;			//Stores first element last
	
	skriv3(head,temp,size); 	//Calls skriv3 to store array in list
	
	free(temp);					//Dealocates array			
	return 0;	
}
	
//Shift list right 
//Pre: Pointer to linked list, size of list
//post:List shifted right
int shiftr(struct nodeEl *head,int size){
	
	int *temp=(int*) malloc(size*sizeof(int));	//Alocated array of same size as list
	int temp2,temp3;
	struct nodeEl *node=head;
	
	for (int i=0;i<size;i++){			//Store list in array
		temp[i]=node->el;
		node=node->next;
		}
	
	temp2=temp[size-1];					//Store away leat element in array to keep it form being overritten in next step 
	
	for (int i=size-2;i>=0;i--){		//Move all elements one step to the right
		temp[i+1]=temp[i];
	}
	temp[0]=temp2;						//Stores last element first
	
	skriv3(head,temp,size);				//Calls skriv3 to store array in list
	
	free(temp);						//Dealocates array	
	return 0;	
	}
	


