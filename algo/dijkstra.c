#include<stdio.h>
#include<limits.h>
#define INFINITY INT_MAX
#define MAXNODES 10
#define MEMBER 1
#define NONMEMBER 0

int w_graph[MAXNODES][MAXNODES];

void init_graph(int weight[][MAXNODES])
{
	int i=0,j=0;
	for(i=0;i<MAXNODES;i++)
		for(j=0;j<MAXNODES;j++)
			weight[i][j]=INFINITY;
}
void join(int weight[][MAXNODES],int e1,int e2,int w)
{
	weight[e1][e2] = w;
}

void input_graph(int weight[][MAXNODES])
{
	int e1,e2,w;
	char next_edge = 'y';
	init_graph(weight);
	printf("input edge and weight in order (e1,e2,w) \n");
       	while(next_edge == 'y' || next_edge =='Y')
	{
		scanf("%d%d%d",&e1,&e2,&w);
		join(weight,e1,e2,w);
		printf("input next_edge (y/n)\n");
		scanf(" %c",&next_edge);
	}
}
	

void shortpath(int weight[][MAXNODES],int s,int t,int *pd,int precede[])
{
	int distance[MAXNODES],perm[MAXNODES];
	int current,i,k,dc;
	int smalldist,newdist;

	//initialization of perm and distance
       
	for(i=0;i<MAXNODES;++i){
		perm[i] = NONMEMBER;
		distance[i] = INFINITY;
	}

	//initializing source node

	perm[s] = MEMBER;
	distance[s] = 0;
	current = s;
	while (current != t) {
		smalldist = INFINITY;
		dc = distance[current];
		
		for(i = 0;i < MAXNODES; i++){
			if(perm[i] == NONMEMBER){
				if(weight[current][i] == INT_MAX)
					newdist = INT_MAX;
				else
					newdist = dc + weight[current][i];
				if(newdist < distance[i]) {
					//distance from s to i is less than distancd[i]
					distance[i] = newdist;
					precede[i] = current;
				}

				//getting the smallest distance
				if(distance[i] < smalldist){
					smalldist = distance[i];
					k = i;
				}

			}
		} //end for
		current = k;
		perm[current] = MEMBER;
	} //end while
	
	*pd = distance[t];
} //end shortpath procedure


	

void main()
{
	int src,dest,predecessor[MAXNODES],d,i;
	//initialize predecessor
	for(i=0;i<MAXNODES;i++)
		predecessor[i] = -1; //no shortest path found thus no predecessor at starting

	printf("Input graph\n");
	input_graph(w_graph);
	printf("input source and destination node\n");
	scanf("%d%d",&src,&dest);
	shortpath(w_graph,src,dest,&d,predecessor);
	printf("distance = %d\n",d);
	printf("path \n");
	for(i=0;i<MAXNODES;i++)
		printf("%d\t",predecessor[i]);
	printf("\n");
}

