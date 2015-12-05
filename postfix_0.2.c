#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "structure.h"
#define MAXEXPR 50

int is_digit(char);
int is_delimiter(char);
int is_operator(char);
int is_permitted(char);
float operation(float,float,char);
float process_data(STACK *);
float eval(char *);

void main(int argc, char *argv[])
{
	char expr[MAXEXPR];
	if(argc==1 || argc >2){
		printf("see usage :\n");
		printf("post <expression>\n");
		exit(1);
	}

	printf("%s = %f\n",argv[1],eval(argv[1]));
}

int is_digit(char symbol)
{
	return (symbol >= '0' && symbol <= '9');
}

int is_delimiter(char symbol)
{
	return (symbol == ',');
}

int is_operator(char symbol)
{
	return (symbol == '+' || 
		symbol == '-' ||
		symbol == '/' ||
		symbol == '*' ||
		symbol == '^' );
}

int is_permitted(char symbol)
{
	return (is_digit(symbol) || is_operator(symbol) || is_delimiter(symbol));
}

float operation(float opr1, float opr2, char symbol)
{
	switch(symbol)
	{
		case '+' : return opr1 + opr2;
		case '-' : return opr1 - opr2;
		case '*' : return opr1 * opr2;
		case '/' : return opr1 / opr2;
		case '^' : return pow(opr1,opr2);
		default  : printf("illegal operator\n");
			   exit(1);
	}
}

float process_data(STACK *pst1)
{	float d;
	STACK *pst2;
	init_stack((pst2=create_stack()));
	pour(pst2,pst1);
	while(!is_empty(pst2)){
		d = pop(pst2);
		if(!is_empty(pst2))
			push(pst2,10*d + pop(pst2));
		else {
			push(pst2,d);
			return peek(pst2);
		}
	}
	//while(pst2->top>0){
	//	d = pop(pst2);
	//	pst2->item[pst2->top] = 10*d + pst2->item[pst2->top];
	//}
	//empty(pst1);   //pst points to stack temp this process is superfluous
			//as temp has been make empty during call to pour()
	//return pst2->item[pst2->top];
}


float eval(char *expr)
{
	STACK solution,temp;
	init_stack(&solution);init_stack(&temp);
	float value,operand1,operand2;
	while(*expr)
	{	
		if(!is_permitted(*expr)){
			fprintf(stderr,"error: invalid expression\n");
			exit(1);
		}

		if(is_digit(*expr))
			push(&temp, (float) (*expr - '0'));
		else if(is_delimiter(*expr)){
			if(!is_empty(&temp))
			push(&solution,process_data(&temp));
			else {
			expr++;continue;
			}
		}
		else {  
			operand2 = pop(&solution);
			operand1 = pop(&solution);
			value = operation(operand1,operand2,*expr);
			push(&solution,value);
		}
		expr++;
	}
	
	if(!is_empty(&temp))
		push(&solution,process_data(&temp));

	if(get_top(&solution)>0){
		printf("error: invalid postfix expression\n");
		exit(1);
	}
	return pop(&solution);
}				
