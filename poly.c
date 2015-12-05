#include<stdio.h>
#include<stdlib.h>
#define overflow { \
		 printf("overflow\n"); \
		 exit(1); \
		 }

struct term{
	int exp;
	int coff;
	struct term *next;
};

typedef struct term TERM;

TERM * create(TERM *);
TERM * create_term();
TERM * sorted_input_polynomial();
TERM * sorted_insert(TERM *,int,int);
void input_polynomial(TERM *);
void display_polynomial(TERM *);
TERM * add_polynomial(TERM *,TERM *);

TERM *poly1,*poly2,*poly3=NULL,*ptr,init = {0,0,NULL};

TERM * create(TERM *t)
{
	if(!(ptr = (TERM *) malloc(sizeof(TERM))))
		overflow
	ptr->next = NULL;
	if(t ==NULL)
		return ptr;
	t->next = ptr;
	return ptr;
}

TERM * create_term()
{
	if(!(ptr = (TERM *) malloc(sizeof(TERM))))
	      overflow
	ptr->next = NULL;
	return ptr;
}	

TERM * sorted_insert(TERM *start,int c, int e)
{	TERM *temp=NULL,*ptr;
	while(start && start->exp >= e){
		temp = start;
		start = start->next;
	}
	
	if(!temp)
	{
		(ptr=create_term()) -> next = start;
		 ptr->coff=c;ptr->exp=e;
		 return ptr;
	}
	
	if(temp->exp == e)
	{
		temp->coff = temp->coff + c;
		return NULL;
	}
	(ptr=create_term())->next = temp->next;
	ptr->coff=c;ptr->exp=e;
	temp->next = ptr;
	return NULL;
}

TERM * sorted_input_polynomial()
{
	TERM *start=NULL,*ptr;
	int exp,coff;
	char choice='y';
	while(choice == 'y')
	{
		printf("input coeff and exponent\n");
		scanf("%d%d",&coff,&exp);

		if(!start)
		{
			start = create_term();
			start->exp = exp;start->coff=coff;
		}
			
		else
		{
			if(ptr=sorted_insert(start,coff,exp))
				start=ptr;
		}


		printf("input another term(y/n)\n");
		scanf(" %c",&choice);
	}
	return start;
}


		
void input_polynomial(TERM *poly)
{	int exp,coff;
	char choice;
	while(1)
	{	int exp,coff;
		printf("input coeff and exponent\n");
		scanf("%d%d",&coff,&exp);
		poly->exp = exp;
		poly->coff = coff;
		
		printf("input next term (y/n)\n");
		scanf(" %c",&choice);
		if(choice != 'y')
			break;
		poly = create(poly);	
	}
}

void display_polynomial(TERM *poly)
{
	while(poly!=NULL)
	{
		printf("%d .x^%d",poly->coff,poly->exp);
		if(poly->next!=NULL && poly->next->coff >= 0)
			printf(" + ");
		poly=poly->next;
	}
	printf("\n");
}

TERM * add_polynomial(TERM *p, TERM *q)
{	TERM *sum,*r=NULL;
	while(p && q)
	{	
		if(r)
			r=create(r);
		else
			sum=r=create(r);

		if(p->exp == q->exp)
		{	
			r->coff = p->coff + q->coff;
			r->exp = p->exp;
			p=p->next;q=q->next;
		}

		else if(p->exp > q->exp)
		{	
			r->coff = p->coff; 
			r->exp = p->exp;
			p = p->next;
		}
		
		else
		{	
			r->coff = q->coff;
			r->exp = q->exp;
			q = q->next;
		}
	}

	while(p || q)
	{
		r=create(r);
		if(q)
		{	
			r->coff = q->coff;
			r->exp = q->exp;
			q = q->next;
		}

		else if(p)
		{	
			r->coff = p->coff;
			r->exp = p->exp;
			p = p->next;
		}
	}
	return sum;
}	
		
void main()
{
	//if(!(poly1 = (TERM *) malloc(sizeof(TERM))))
	//	overflow

	//if(!(poly2 = (TERM *) malloc(sizeof(TERM))))
	//	overflow
	
	//*poly1 = *poly2 = init;

	printf("input polynomial 1\n");
	poly1=sorted_input_polynomial();
	printf("input polynomial 2\n");
	poly2=sorted_input_polynomial();
	
	poly3=add_polynomial(poly1,poly2);
	display_polynomial(poly1);
	display_polynomial(poly2);
	display_polynomial(poly3);
}

