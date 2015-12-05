#include<stdio.h>
#include<stdlib.h>
#define MAX 5

int queue[MAX],front=-1,rear=-1;

void enqueue(int n)
{
	if((front==0 && rear == MAX-1) || front == rear +1)
	{
		printf("Overflow\n");
		return;
	}

	if(front == -1)
		front=rear=0;
	else if(rear == MAX-1)
		rear = 0;
	else 
		rear++;
	queue[rear] = n;
}

void dequeue()
{
	if(front == -1)
	{
		printf("Underflow\n");
		return;
	}

	if(front == rear)
		front=rear=-1;
	else if(front == MAX-1)
		front = 0;
	else 
		front++;
}

void display()
{	 int i;
	 if(front== -1)
	 {
		 printf("Underflow\n");
		 return;
	 }
	for(i=front;i<=rear;i++)
	{
		printf("%d\t",queue[i]);
		if(i==MAX-1 && rear != MAX-1)
			i=0;
	}	
	printf("\n");
}

void main()
{	
	int choice,item;
	printf("Input choice\n");

	while(1)
	{
		printf("1: enqueue 2: dequeue 3: display 4: exit\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: printf("input data\n");
				scanf("%d",&item);
				enqueue(item);
				break;
			case 2: dequeue();
				break;
			case 3: display();
				break;
			case 4: exit(0);

			default: printf("invalid choice\n");
		}
	}
}
