#define __qd_type int
#include<stdio.h>
#include<stdlib.h>
#include "astructure.h"

void display(QUEUE *pq)
{        int i;
         if(pq->front== -1)
         {
                 printf("Underflow\n");
                 return;
         }
        for(i=pq->front;i<=pq->rear;i++)
        {
                printf("%d\t",pq->item[i]);
                if(i==QUEUESIZE-1 && pq->rear != QUEUESIZE-1)
                        i=0;
        }       
        printf("\n");
}

void main()
	{	
		QUEUE p;
		init_queue(&p);
		int choice,ele,d;
		while(1)
		{
			printf("1: enqueue  2: dequeue  3: display 4: exit\n");
			printf("Input choice\n");
			scanf("%d",&choice);

			switch(choice)
			{
				case 1: printf("Input element\n");
					scanf("%d",&ele);
					enqueuer(&p,ele);
					break;
				
				case 2: d=dequeuef(&p);
					if(!is_q_empty(&p))
					printf("deleted element is %d\n",d);
				        break;

				case 3: display(&p);
					break;
				
				case 4: exit(0);
					break;
				
				default: printf("Invalid choice\n");
			}
		}
	}

		
