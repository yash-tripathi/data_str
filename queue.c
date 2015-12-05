#include<stdio.h>
#include<stdlib.h>
#define MAX 5

int queue[MAX];
int rear=-1,front=-1;

/**********************************/
/*******Function_Prototype*********/
/**********************************/
void enqueue(int);
void dequeue();
void display();

/******End_Function_Prototype******/
/**********************************/


/**********************************/
/******Begin_main()_function*******/
/**********************************/
void main()
	{	
		int choice,ele;
		while(1)
		{
			printf("1: enqueue  2: dequeue  3: display 4: exit\n");
			printf("Input choice\n");
			scanf("%d",&choice);

			switch(choice)
			{
				case 1: printf("Input element\n");
					scanf("%d",&ele);
					enqueue(ele);
					break;
				
				case 2: dequeue();
				        break;

				case 3: display();
					break;
				
				case 4: exit(0);
					break;
				
				default: printf("Invalid choice\n");
			}
		}
	}

/********End_main()_function*******/
/**********************************/



/**********************************/
/*******Function_Definition********/
/**********************************/


/************enqueue()*************/
void enqueue(int val)
{
	if(rear == MAX -1)
		printf("Overflow\n");
	else if (rear == -1 && front == -1)
	{
		front = rear = 0;
		queue[rear]=val;
	}
	else
	{
		rear++;
		queue[rear]=val;
	}
}


/************dequeue()*************/
void dequeue()
{	
	int d;
	if(front == -1)
		printf("Underflow\n");
	else 
	{
		d = queue[front];
		printf("Element deleted = %d\n",d);
		front++;
	}
	if(front > rear)
		front = rear = -1;
}


/************display()*************/
void display()
{
	int i;
	if(front == -1)
		printf("Underflow\n");
	else
	{
		for(i = front; i<= rear;i++)
			printf("%d\t",queue[i]);
		printf("\n");
	}
}


/*****End_Function_Definition******/
/**********************************/
		
