#define STACKSIZE 100
#define QUEUESIZE 5
#ifndef __d_type
#define __d_type float
#endif

#ifndef __qd_type
#define __qd_type float
#endif

#define TRUE 1
#define FALSE 0
struct stack {
  int top;
  __d_type item[STACKSIZE];
};

struct queue {
  int front,rear;
  __qd_type item[QUEUESIZE];
};

typedef struct stack STACK;
typedef struct queue QUEUE;

int is_empty(STACK *);
void tpop(STACK *,__d_type *,int *);
__d_type pop(STACK *);
void tpush(STACK *,__d_type,int *);
void push(STACK *,__d_type);
void tpeek(STACK *,__d_type *,int *);
__d_type peek(STACK *);
void pour(STACK *,STACK *);
void copy(STACK *,STACK *);
void empty(STACK *);
int get_top(STACK *);
void init_stack(STACK *);
STACK * create_stack();

void enqueuef(QUEUE *,__qd_type);
void enqueuer(QUEUE *,__qd_type);
void tenqueue(QUEUE *,__qd_type,int *);
__qd_type dequeuef(QUEUE *);
__qd_type dequeuer(QUEUE *);
void tdequeue(QUEUE *,__qd_type *,int *);
QUEUE * create_queue();
int is_q_empty(QUEUE *);
void q_empty(QUEUE *);
void init_queue(QUEUE *);

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
