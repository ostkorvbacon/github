#include "driv.h"
#include "node.h"

int main (){

struct nodeEl *head=NULL; //Declare headand and set it to NULL as per instructions
int val=42; 			//Declare val set it to an arbritary value!=0 to ensure the code in while is run at least once
head=start(head);		//Calls start() and saves a pointer to created list in head	

printf(" 0:Exit\n 1:Print list\n 2:Print size of list\n 3:Add last\n 4:Add at position\n 5:Remove an int\n 6:Remove a position\n 7:Empty list\n 8:Invert list\n 9:Skift left\n 10:Skift right\n 11:Sort\n 12:Print start address\n");

while (val!=0){
	
	printf("\n Choose: ");
	scanf("%d",&val);

	switch (val) {  //Menu with functins that execute the users choice
		
		case 0:
		
		case0(head);
		
			break;
		
		case 1:
		
			case1(head);
		
			break;
		
		case 2:
		
			case2();
			
			break;
		
		case 3:
		
			head=case3(head);
		
			break;
		
		case 4:
		
			head=case4(head);
		
			break;
		
		
		case 5:
		
			head=case5(head);
	
			break;

		case 6:
		
			head=case6(head);
	
			break;
		
		case 7:
		
			head=case7(head);
			break;
		
		case 8:
		
			case8(head);
			
			break;
		
		case 9:
		
			case9(head);
			
			break;
		
		case 10:
		
			case10(head);
			
			break;
		
		case 11:
		
			case11(head);
			
			break;

		case 12:
		
			case12(head);
			
			break;
			
		default:
			
			printf("\n Illegal input\n");
	}
}

return 0;

}

