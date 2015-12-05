#include<stdio.h>

void tower(int n,char beg,char aux,char end)
{
	if(n == 1) {
		printf("move disk %d: %c -> %c\n",n,beg,end);
		return;
	}

	tower(n-1,beg,end,aux);
	printf("move disk %d: %c -> %c\n",n,beg,end);
	tower(n-1,aux,beg,end);
}

void main()
{
	int disk;
	printf("input no of disks \n");
	scanf("%d",&disk);
	printf("the solution is\n");
	tower(disk,'A','B','C');
}
