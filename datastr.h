#define STACKSIZE 100
#define QUEUESIZE 5
#define MAXSTR 50

#ifndef __d_type
#define __d_type STACKEL
#endif

#ifndef __qd_type
#define __qd_type float
#endif

#ifndef DECIMAL_PT
#define DECIMAL_PT '.'
#endif

#define TRUE 1
#define FALSE 0
#define INT 1
#define FLOAT 2
#define CHAR 3
#define STRING 4

struct stackelement {
	union {
		int ival;
		float fval;
		char cval;
		char *pval;
	} ele;

	int etype;
};

typedef struct stackelement STACKEL;

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

/*
stack functions
*/

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

/* 
      queue function
*/
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

/*
      string function
*/
void strrev(char*,char*);
void copy_str(char*,char*);
void filter(char*,char*,char*);
int process_integral(char*);
float process_decimal(char*);
float strtofloat(char*);
int is_sign(char);

