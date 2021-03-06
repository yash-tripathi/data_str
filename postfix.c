#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "datastr.h"
#define MAXEXPR 50
#define DECIMAL_PT '.'

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
	return ((symbol >= '0' && symbol <= '9') || symbol==DECIMAL_PT);
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
{	
	int i=0;
	char operand[MAXEXPR];
	STACK temp;
	STACKEL stopr;
	init_stack(&temp);
	pour(&temp,pst1);
	while(!is_empty(&temp))
	{	stopr = pop(&temp);
		operand[i] = stopr.ele.cval;
		i++;
	}
	operand[i] = '\0';
	return strtofloat(operand);

}


float eval(char *expr)
{
	STACK solution,temp;
	STACKEL stc,stf;
	stc.etype=CHAR;stf.etype=FLOAT;
	init_stack(&solution);init_stack(&temp);
	float value,operand1,operand2;
	while(*expr)
	{	
		if(!is_permitted(*expr)){
			fprintf(stderr,"error: invalid expression\n");
			exit(1);
		}

		if(is_digit(*expr) || (is_sign(*expr) && is_digit(*(expr+1)))){
			stc.ele.cval = *expr;
			push(&temp,stc);
		}
		else if(is_delimiter(*expr)){
			if(!is_empty(&temp)){
				stf.ele.fval=process_data(&temp);
				push(&solution,stf);
			}
			else {
			expr++;continue;
			}
		}
		else {  
			operand2 = pop(&solution).ele.fval;
			operand1 = pop(&solution).ele.fval;
			stf.ele.fval = operation(operand1,operand2,*expr);
			push(&solution,stf);
		}
		expr++;
	}
	
	if(!is_empty(&temp)){
		stf.ele.fval = process_data(&temp);
		push(&solution,stf);
	}
	if(get_top(&solution)>0){
		printf("error: invalid postfix expression\n");
		exit(1);
	}
	return pop(&solution).ele.fval;
}				
