#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "iastructure.h"
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

int is_sign(char symbol)
{
	return (symbol == '+' || symbol == '-');
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

void strrev(char *instr,char *outstr)
{
	char *a;
	a = instr;
	while(*instr)
                instr++;
	instr--;
        while(instr>=a){
                *outstr = *instr;
                instr--,outstr++;
        }
	*outstr='\0';
}

void copy_str(char *str1,char *str2)
{
	while(*str1)
	{
		*str2=*str1;
		str1++;str2++;
	
	}
	*str2='\0';
}

void filter(char *stream,char *integral,char *decimal)
{	
	/*
	   initialize both parts to null strings.
	*/
	*integral=*decimal='\0';	
	while(*stream != '\0' && *stream != DECIMAL_PT){
		*integral=*stream;
		stream++;integral++;
	}
	*integral='\0';
	if(*stream == DECIMAL_PT)
	{	
		stream++;			//jump the decimal pt and copy the rest of the string to decimal
		strcpy(decimal,stream);
	}
}

int process_integral(char *pc)
{
	int d=0;
	while(*pc){
                d = d*10 + (*pc - '0');
		pc++;
	}
	return d;
}

float process_decimal(char *pc)
{
	float d=0;char rpc[MAXEXPR],*prpc;
	strrev(pc,rpc);
	prpc = rpc;
	while(*prpc){
		d=d/10 + (*prpc-'0');
		prpc++;
	}
	return d/10;
}

float strtofloat(char *str)
{	
	char sign='+' ;float value; 		//assuming no sign as positive
	if(is_sign(*str)){
		sign=*str;
		str++;
	}
	char integ[MAXEXPR],deci[MAXEXPR];
	filter(str,integ,deci);
	value = process_integral(integ)+process_decimal(deci);
	if(sign=='+') return value;
	return -value;
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
