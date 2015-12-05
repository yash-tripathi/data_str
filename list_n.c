#include<stdio.h>
#include<stdlib.h>

struct node{
	int data;
	struct node *next;
};

typedef struct node NODE;

void create();
void display();
void insertbeg();
void insertpos();
void insertlast();
void delbeg();
void delpos();
void dellast();
void search();

NODE *start=NULL,*last,*temp,*ptr;

void create()
{
	int n;
	if(start==NULL){
	printf("input data\n");
	scanf("%d",&n);
	ptr = (NODE *) malloc(sizeof(NODE));
	ptr->data = n;
	ptr->next = NULL;
	start = ptr;
	}
	else
		insertlast();
}
void display()
{
	if(start == NULL)
		printf("Underflow\n");
	else
	{
		temp = start;
		while(temp!=NULL)
		{
			printf("%d\t",temp->data);
			temp = temp->next;
		}
		printf("\n");
	}
}

void insertbeg()
{	if(start == NULL){
		create();
		return;
	}
	int n;
	ptr = (NODE *) malloc(sizeof(NODE));
	printf("Input data\n");
	scanf("%d",&n);
	ptr->data = n;
	
	ptr->next = start;
	start = ptr;
}

void insertlast()
{	if(start == NULL){
		create();
		return;
	}
	int n;
	ptr = (NODE *) malloc(sizeof(NODE));
	printf("Input data\n");
	scanf("%d",&n);

	ptr->data = n;
	ptr->next = NULL;
	temp = start;
	while(temp->next!=NULL)
		temp=temp->next;
	temp->next = ptr;
}

void insertpos()
{
	if(start == NULL){
		create();
		return;
	}
	int n,p;
	ptr = (NODE *) malloc(sizeof(NODE));
	printf("Input data\n");
	scanf("%d",&n);
	printf("Input node\n");
	scanf("%d",&p);
	ptr->data = n;	
	temp = start;
	while(temp->data != p){
		temp = temp->next;
		if(temp==NULL) {
			printf("node not found\n");
			return;
		}
	}
	ptr->next= temp->next;
	temp->next = ptr;
}

void delbeg()
{
	if(start==NULL){
		printf("Underflow\n");
		return;
	}
	temp = start;

	start = start->next;
	free(temp);
}

void dellast()
{
	if(start==NULL){
		printf("Underflow\n");
		return;
	}
	temp = start;
	
	while(temp->next != NULL){
		last = temp;
		temp = temp->next;
	}
	
	last->next = NULL;
	free(temp);
}

void delpos()
{	int n;
	if(start == NULL){
		printf("Underflow\n");
		return;
	}
	temp = start;
	printf("Input node to delete\n");
	scanf("%d",&n);

	while(temp->data!=n){
	ptr = temp;
	temp = temp->next;
		if(temp==NULL){
		printf("node not found\n");
		return;
		}
	}
	ptr->next = temp->next;
	free(temp);
}
void search()
{	int f=1,n;
	if(start==NULL){
		printf("Underflow\n");
		return;
	}
	printf("Input element to search\n");
	scanf("%d",&n);
	temp = start;
	while(temp->data!=n){
		temp=temp->next;
		if(temp==NULL){
			f=0;break;
		}
	}
	if(f==0)
		printf("Element not found\n");
	else   	
		printf("Element found\n");
}
void main()
{
	int choice;
	printf("Input choice\n");

	while(1)
	{
		printf("1:create 2:insert_beg 3:insert_pos 4:insert_last 5:del_beg  6:del_pos 7:del_last 8:search 9:display 10:exit\n");

		scanf("%d",&choice);

		switch(choice)
		{
			case 1: create();
				break;
			case 2: insertbeg();
				break;
			case 3: insertpos();
				break;
			case 4: insertlast();
				break;
			case 5: delbeg();
				break;
			case 6: delpos();
				break;
			case 7: dellast();
				break;
			case 8: search();
				break;
			case 9: display();
				break;
			case 10: exit(0);
				break;
			default: printf("invalid choice\n");
		}
	}
}
