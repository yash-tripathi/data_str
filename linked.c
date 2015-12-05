#include<stdio.h>
#include<stdlib.h>

struct node
{
	int data;
	struct node *next;
};

struct node *start=NULL,*ptr,*head,*last,*temp;

void create();
void display();
void insert();
void del();
void main()
{
	int ch;
	while(1)
	{
		printf("1: Create 2: Display 3: Insert 4: delete 5: Exit\n");
		printf("Enter your choice\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: create();
				break;
			case 2: display();
				break;
			case 3: insert();
				break;
			case 4: 
				del();
				break;
			case 5: exit(0);
		}
	}
}


void create()
{
	int n;
	printf("Enter the data\n");
	scanf("%d",&n);
	ptr = (struct node*) malloc(sizeof(struct node));

	ptr-> data = n;
	ptr-> next = NULL;

	if(start == NULL)
	{
		start = ptr;
		last = ptr;
	}

	else
	{
		last->next = ptr;
		last = ptr;
	}
}

void display()
{
	if(start == NULL)
	printf("Underflow\n");
	else
	{
		head = start;
		while(head!=NULL)
		{
			printf("%d\t",head->data);
			head=head->next;
		}
		printf("\n");
	}
}

void insert()
{
	int ch,n;
	printf("1: Beginning 2: End 3: After an element\n");
	printf("Enter your choice\n");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1: if(start == NULL)
			printf("Underflow\n");
			else
			{
				ptr = (struct node *)malloc(sizeof(struct node));
				printf("Enter data\n");
				scanf("%d",&n);
				ptr->data = n;
				ptr->next = start;
				start = ptr;
			}
			break;
		case 2: if(start == NULL)
			printf("Underflow\n");
			else
			{
				ptr = (struct node *)malloc(sizeof(struct node));
				printf("Enter data\n");
				scanf("%d",&n);
				ptr->data=n;
				last->next=ptr;
				last = ptr;
			}
			break;
	}
}

void del()
{
	int ch,n;
	printf("Enter your choice\n");
	scanf("%d",&ch);
	switch(ch)
	{
	 case 1:if(start==NULL)
		printf("Underflow\n");
		temp = start;
		start = start->next;
		free(temp);
		break; 

	 case 2:if(start==NULL)
		printf("Underflow\n");
		temp = last;
		last = start;
		while(last->next->next != NULL )
			last = last->next;
		last->next = NULL;
		free(temp);
		break;

	 case 3:if(start==NULL)
		printf("Underflow\n");
		printf("Input element\n");
		scanf("%d",&n);
		temp=start;
		while(temp->data!=n)
		{
			ptr = temp;
			temp=temp->next;
		}
		ptr->next = temp->next;
		free(temp);
		break;
	default: printf("Invalid choice\n");
	}
}
