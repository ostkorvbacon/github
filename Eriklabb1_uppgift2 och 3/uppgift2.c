#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct node{
    
    int data;
    struct node *next;
    
    }node;

int a(node* head){
        
    node* temp=head;
    int b=temp->data;
    temp=head->next;
    while (temp!=NULL){
        
            head->data=temp->data;
            head->next=temp->next;
            head=head->next;
            temp=temp->next;
        
        
    }
    free(head);

    return b;
    
    
}

int main ()
{
    node * head=(node*)calloc(1,sizeof(node));
    node * temp=(node*)calloc(1,sizeof(node));
    
    head->data=1;
    temp->data=2;
    head->next=temp;
    head->next->next=NULL;
    printf("head %d next %d",head->data,head->next->data);

    int b=a(head);
    printf("\nhead %d b %d next %p\n",head->data,b,head->next);
    printf("head %p",head);
free(head);
free(temp);
return 0;

}



