#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "astructure.h"
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

void filter(STACK *stream,STACK *integral,STACK *decimal)
{	
	STACK temp;
	init_stack(&temp);
	while(!is_empty(stream) && (int) peek(stream)!=DECIMAL_PT)
		push(&temp,pop(stream));
	
	if(is_empty(stream))
		copy_stack(&temp,integral);
	else
	{	
		pour(decimal,&temp);
		pop(stream);
		if(is_empty(stream))
			push(integral,0);
		else
			while(!is_empty(stream))
				push(integral,pop(stream));
	}
}

int process_integral(STACK *ps)
{
	float d;
	while(!is_empty(ps)){
                d = pop(ps);
                if(!is_empty(ps))
                        push(ps,10*d + pop(ps));

                else {
                        push(ps,d);
                        return (int) peek(ps);
                }
        }
}

float process_decimal(STACK *ps)
{
	float d;
	while(!is_empty(ps)){
		d=pop(ps);
		if(!is_empty(ps))
			push(ps,d/10 + pop(ps));
		else {
			push(ps,d/10);
			return peek(ps);
		}
	}
}

float process_data(STACK *pst1)
{	float d;
	STACK integ,deci;
	init_stack(&integ);init_stack(&deci);
	filter(pst1,&integ,&deci);
	return process_integral(&integ)+process_decimal(&deci);

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
			if(*expr == DECIMAL_PT)
				push(&temp, (float) DECIMAL_PT);
			else
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
