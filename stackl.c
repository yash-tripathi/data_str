#include<stdio.h>
#include<stdlib.h>
struct STACK{
	int data;
	struct STACK *next;
};

typedef struct STACK stack;
stack *top=NULL,*ptr,*avail,*temp;

void push(int n)
{
	avail = (stack *) malloc(sizeof(stack));
	if(avail == NULL)
	{
		printf("Overflow\n");
		return;
	}
	ptr = avail;
	ptr -> data = n;

	ptr->next = top;   //no separate condition needed for empty stack if top is NULL it goes to ptr->next
	top = ptr;
}

void pop()
{	int d;
	if(top == NULL)
	{
		printf("Underflow\n");
		return;
	}
	
	temp = top;
	printf("deleted element is %d\n",temp->data);
	top = top->next;
	free(temp);
}

void display()
{
	if(top == NULL)
	{
		printf("Underflow\n");
		return;
	}

	temp = top;
	while(temp != NULL)
	{
		printf("%d\t",temp->data);
		temp=temp->next;
	}
	printf("\n");
}

void peek()
{
	if(top == NULL)
	{
		printf("Underflow\n");
		return;
	}

	printf("%d\n",top->data);
}

void main()
{
	int choice,item;
	printf("input choice\n");
	while(1)
	{
		printf("1: push 2: pop 3: peek 4: display 5: exit\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: printf("input data\n");
				scanf("%d",&item);
				push(item);
				break;
			case 2: pop();
				break;
			case 3: peek();
				break;
			case 4: display();
				break;
			case 5: exit(0);
			
			default : printf("invalid choice\n");
		}
	}
}
