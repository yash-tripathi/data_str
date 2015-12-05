#define __d_type char
#define DELIMITER ','
#define MAXEXPR 50
#include<stdio.h>
#include<stdlib.h>
#include "astructure.h"

int is_operand(char symbol)
{
        return (symbol >= '0' && symbol <= '9');
}

int is_operator(char symbol)
{
        return (symbol == '+' || 
                symbol == '-' ||
                symbol == '/' ||
                symbol == '*' ||
                symbol == '^' ||
		symbol == ')' ||
		symbol == '(' );
}

int get_order(char op)
{       int i;
        static int oper[5]={'+','-','*','/','^'};
        static int order[5]={'1','1','2','2','3'};
        for(i=0;i<5;i++)
                if(oper[i] == op)
                        break;
        return order[i];
}

int precedence(char op1,char op2)
{
        int i;
        static int oper[5]={'+','-','*','/','^'};
        static int order[5]={'1','1','2','2','3'};
        if(op1 == '(')
                return 0;
        if(op2 == '(')
                return 0;
        if(op2 == ')')
                return 1;
        if(op1 == ')')
                return -1;
        return (get_order(op1) >= get_order(op2));
}

void in_to_post(char *infix,char *postfix)
{
	
	int inpos,und;
	int postpos=0;
	char ptopsymb = '+';
	char isymb;
	STACK opstack;
	init_stack(&opstack);

	while((isymb=*infix)!='\0')
	{       if(isymb == ' ') infix++;
		else if(is_operand(isymb))
		{
			while((isymb=*infix)!='\0' && !is_operator(*infix)){
				postfix[postpos++] = isymb;
				infix++;
			}
			postfix[postpos++] = DELIMITER;
		}
		else{
			tpop(&opstack,&ptopsymb,&und);
			while (!und && precedence(ptopsymb,isymb))
			{
				postfix[postpos++] = ptopsymb;
				postfix[postpos++] = DELIMITER;
				tpop(&opstack,&ptopsymb,&und);
			}
			
			if(!und)
				push(&opstack,ptopsymb);
			if(und || isymb != ')')
				push(&opstack,isymb);
			else
				ptopsymb = pop(&opstack);
			infix++;
		}
	}

	while(!is_empty(&opstack)){
		postfix[postpos++]=pop(&opstack);
		postfix[postpos++]= DELIMITER;
	}
	postfix[--postpos] = '\0';
	return;
	
}
	
void main(int argc, char *argv[])
{
        char poststr[MAXEXPR];
        if(argc==1 || argc >2){
                printf("see usage :\n");
                printf("in2pos <expression>\n");
                exit(1);
        }
	in_to_post(argv[1],poststr);
        printf("%s\n",poststr);
}
