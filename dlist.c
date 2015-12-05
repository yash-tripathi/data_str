#include<stdio.h>
#include<stdlib.h>

struct node {
	int data;
	struct node *next,*prev;
};

typedef struct node NODE;

static NODE *start=NULL,*last,*temp,*nnode,*avail,*pnode,*ndel;

void insertbeg(int item)
{
	avail=(NODE *) malloc(sizeof(NODE));
	if(avail == NULL)
	{
		printf("Overflow\n");
		return;
	}
	else
		nnode=avail;
	nnode->data = item;
	nnode->next = start;
	nnode->prev = NULL;
	if(start!=NULL)
		start->prev = nnode;
	start = nnode;
}

void insertlast(int item)
{
	avail = (NODE *) malloc(sizeof(NODE));
	if(avail == NULL)
	{
		printf("Overflow\n");
		return;
	}
	else
		nnode=avail;
	nnode->data = item;
	nnode->next = NULL;
	last = start;
	if(start == NULL)
	{
		nnode->prev = NULL;
		start = nnode;
		return;
	}
	while(last->next != NULL)
		last = last->next;
	last->next = nnode;
	nnode->prev = last;
}

void insertpos(NODE *pnode,int item)
{
	if(pnode==NULL){
		printf("node does not exist\n");
		return;
	}
	avail = (NODE *) malloc(sizeof(NODE));
	if(avail == NULL)
	{
		printf("Overflow\n");
		return;
	}
	else 
		nnode = avail;
	nnode->data = item;
	nnode->next = pnode->next;
	pnode->next = nnode;
	nnode->prev = pnode;
	if(nnode->next != NULL)
		nnode->next->prev = nnode;
}

NODE * search(int n)
{	int i;
	if(start == NULL)
	{
		printf("underflow\n");
		return;
	}

	temp = start;

	for(i=1;i<n;i++)
	{	temp=temp->next;
		if(temp == NULL){
			printf("node not found\n");
			return NULL;
		}
	}

	return temp;
}

void delete(NODE *ndel)
{
	if(start == NULL)
	{
		printf("Underflow\n");
		return;
	}

	if(start == ndel)
		start=start->next;
	if(ndel->next != NULL)
		ndel->next->prev=ndel->prev;
	if(ndel->prev != NULL)
		ndel->prev->next=ndel->next;
	free(ndel);
}

void display()
{
	if(start == NULL)
	{
		printf("underflow\n");
		return;
	}
	temp = start;
	while(temp != NULL)
	{
		printf("%d\t",temp->data);
		temp=temp->next;
	}
	printf("\n");
}

void main()
{
	int choice,n,p;
	printf("input choice\n");

	while(1)
	{
		printf("1. insertbeg 2. insertlast 3. insertpos 4. delete 5. display 6. exit\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: printf("input data\n");
				scanf("%d",&n);
				insertbeg(n);
				break;
			case 2: printf("input data\n");
				scanf("%d",&n);
				insertlast(n);
				break;
			case 3: printf("input data and position\n");
				scanf("%d%d",&n,&p);
				pnode = search(p);
				insertpos(pnode,n);
				break;
			case 4: printf("input node to delete\n");
				scanf("%d",&p);
				ndel = search(p);
				delete(ndel);
				break;
			case 5: if(start == NULL) printf("Hello\n");
				display();
				break;
			case 6: exit(0);
				break;
			default : printf("invalid choice\n");
		}
	}
}
				
