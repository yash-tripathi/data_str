#include"datastr.h"
/*
   function definitions
*/

int is_empty(STACK *ps)
{
  return (ps->top == -1);
}

void tpop(STACK *ps,__d_type *px,int *und)
{
  if(is_empty(ps))
    {
      *und = TRUE;
      return;
    }
  *und = FALSE;
  *px = ps->item[ps->top--];
  return;
}

__d_type pop(STACK *ps)
{
  if(is_empty(ps))
    {
      printf("stack underflow\n");
      exit(1);
    }
  return (ps->item[ps->top--]);
}

void tpush(STACK *ps,__d_type x,int *ovr)
{
  if(ps->top == STACKSIZE -1){
    *ovr=TRUE;
    return;
  }
  ovr = FALSE;
  ps->item[++(ps->top)]=x;
  return;
}

void push(STACK *ps,__d_type x)
{
  if(ps->top == STACKSIZE -1){
    printf("stack overflow\n");
    exit(1);
  }
  ps->item[++(ps->top)]=x;
  return;
}

void tpeek(STACK *ps,__d_type *px,int *und)
{
  if(is_empty(ps)){
    *und=TRUE;
    return;
  }
  *und = FALSE;
  *px = ps->item[ps->top];
  return;
}

__d_type peek(STACK *ps)
{
  if(is_empty(ps)){
    printf("stack underflow\n");
    exit(1);
  }
  return ps->item[ps->top];
}

void pour(STACK *ps_a,STACK *ps_b)
{
  while(ps_b->top != -1)
    push(ps_a,pop(ps_b));
}

void empty(STACK *ps)
{
  ps->top = -1;
}

STACK * create_stack()
{
	STACK *ps;
	if(!(ps=(STACK *) malloc(sizeof(STACK)))){
	       printf("buffer overflow\n");
	       exit(1);
	}
	return ps;
}

int get_top(STACK *ps)
{
	return ps->top;
}

void init_stack(STACK *ps)
{
	ps->top = -1;
}

void copy_stack(STACK *ps1,STACK *ps2)
{
	STACK temp;init_stack(&temp);
	pour(&temp,ps1);
	pour(ps2,&temp);
}

/* here starts the queue specific function */

void enqueuef(QUEUE *pq,__qd_type x)
{
  if(pq->front == pq->rear +1 || (pq->front == 0 && pq->rear == QUEUESIZE-1)){
    printf("queue overflow\n");
    return;
  }
  else if(pq->front == -1)
    pq->front=pq->rear=0;
  else if(pq->front == 0 && pq->rear != QUEUESIZE-1)
    pq->front = QUEUESIZE-1;
  else
    (pq->front)--;
  pq->item[pq->front]=x;
}

void enqueuer(QUEUE *pq,__qd_type x)
{
  if(pq->front == pq->rear +1 || (pq->front == 0 && pq->rear == QUEUESIZE-1)){
    printf("queue overflow\n");
    return;
  }
  else if(pq->front == -1)
    pq->front=pq->rear=0;
  else if(pq->rear == QUEUESIZE-1 && pq->front != 0)
    pq->rear=0;
  else
    ++(pq->rear);
  pq->item[pq->rear]=x;
}

__qd_type dequeuef(QUEUE *pq)
{
  __qd_type temp;
  if(pq->front == -1){
    printf("underflow\n");
    return;
  }
  temp = pq->item[pq->front];
  if(pq->front == pq->rear)
    pq->front=pq->rear=-1;
  else if(pq->front == QUEUESIZE-1)
    pq->front=0;
  else
    ++(pq->front);
  return temp;
}

__qd_type dequeuer(QUEUE *pq)
{
  __qd_type temp;
  if(pq->front == -1){
    printf("underflow\n");
    return;
  }
  temp = pq->item[pq->front];
  if(pq->front == pq->rear)
    pq->front=pq->rear=-1;
  else if(pq->rear==0)
    pq->rear=QUEUESIZE-1;
  else
    --(pq->rear);
  return temp;
}

QUEUE * create_queue()
{
	QUEUE *pq;
	if(!(pq=(QUEUE *) malloc(sizeof(QUEUE)))){
	       printf("buffer overflow\n");
	       exit(1);
	}
	return pq;
}

void init_queue(QUEUE *pq)
{
	pq->front=pq->rear=-1;
}

int is_q_empty(QUEUE *pq)
{
  return (pq->front==-1);
}

void q_empty(QUEUE *pq)
{
  pq->front=pq->rear=-1;
}


//string related functions

int is_sign(char symbol)
{
	return (symbol == '+' || symbol == '-');
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
		copy_str(stream,decimal);
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
	float d=0;char rpc[MAXSTR],*prpc;
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
	char integ[MAXSTR],deci[MAXSTR];
	filter(str,integ,deci);
	value = process_integral(integ)+process_decimal(deci);
	if(sign=='+') return value;
	return -value;
}
