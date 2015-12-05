#include<stdio.h>
#include<stdlib.h>
#define MAX 5
int stack[MAX];
int top=-1;
/************************/
/*  Function prototype  */
/************************/
void push(int);
void pop();
void peek();
void display();
/************************/

void main()
     {
	int choice,ele,d;
	while(1)
            {
	printf("1: Push  2: Pop  3: Peek  4: Display  5: Exit\n");
	printf("Enter the choice\n");
	scanf("%d",&choice);
	switch(choice)
	     {
		case 1: printf("Entet the element\n");
			scanf("%d",&ele);
			push(ele);break;
		case 2: pop();
			break;
		case 3: peek();
			break;
		case 4: display();
			break;
		case 5: exit(0);
			break;
		default : printf("Wrong choice\n");
	     }
	    }
     } 


/*********************************/
/**** Function definition ********/
/*********************************/
void push(int value)
     {
	if(top == MAX-1)
	printf("Overflow\n");
	else
	{
	 top++;
	 stack[top] = value;
	} 
     } 

void pop()
     {
	int d;
	if(top == -1){
	printf("Underflow\n");
	}
	else{
	d = stack[top];
	top--;
	printf("deleted element = %d\n",d);
	}
     }

void peek()
     {
	if(top == -1)
	printf("Underflow\n");
	else
	printf("%d\n",stack[top]);
     } 

void display()
{
	int i;
	if(top == -1)
	printf("Empty stack\n");
	for(i=top;i>=0;i--)
	printf("%d\t",stack[i]);
	printf("\n");
}
/**********************************/
