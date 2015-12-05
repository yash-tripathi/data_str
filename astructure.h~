#define STACKSIZE 100
#ifndef __d_type
#define __d_type float
#endif
#define TRUE 1
#define FALSE 0
struct stack {
  int top;
  __d_type item[STACKSIZE];
};

typedef struct stack STACK;

int is_empty(STACK *);
__d_type pop(STACK *);
void push(STACK *,__d_type);
__d_type peek(STACK *);
void pour(STACK *,STACK*);
void empty(STACK *);
int get_top(STACK *);
void init_stack(STACK *);

STACK * create_stack();

int is_empty(STACK *ps)
{
  return (ps->top == -1);
}

void tpop(struct stack *ps,__d_type *px,int *und)
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
