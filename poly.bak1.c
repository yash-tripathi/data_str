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

input_polynomial(TERM *poly)
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

display_polynomial(TERM *poly)
{
	while(poly!=NULL)
	{
		printf("%d .x^%d",poly->coff,poly->exp);
		if(poly->next!=NULL)
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
	if(!(poly1 = (TERM *) malloc(sizeof(TERM))))
		overflow

	if(!(poly2 = (TERM *) malloc(sizeof(TERM))))
		overflow
	
	*poly1 = *poly2 = init;

	printf("input polynomial 1\n");
	input_polynomial(poly1);
	printf("input polynomial 2\n");
	input_polynomial(poly2);
	
	poly3=add_polynomial(poly1,poly2);
	display_polynomial(poly1);
	display_polynomial(poly2);
	display_polynomial(poly3);
}

