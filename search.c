#include<stdio.h>
#include<stdlib.h>
#define MAX 100
int linsearch(int *a,int n,int ele)
{
	int i,f=0;
	for(i=0;i<n-1;i++)
	{
		if(a[i]==ele)
		{	
			f = 1;
			break;
		}
	}
	if ( f==1 )
		return i;
	else 
		return -1;
}

int binsearch(int *a,int n,int ele)
{
	int lower=0,upper=n-1,i,mid;
	while( lower <= upper )
	{
		mid = (upper + lower)/2;
		if(ele > a[mid])
			lower = mid+1;
		else if(ele < a[mid])
			upper = mid-1;
		else
		{
			i = mid;
			return i;
		}
	}
	i = -1;
	return i;
}

void swap(int *x,int *y)
{
	int tmp;
	tmp = *x;
	*x = *y;
	*y = tmp;
}
	
void selsort(int *a,int n)
{
	int i,j,min;
	for(i = 0;i < n-1;i++)
	{
		min = i;
		for(j = i+1;j<n;j++)
		{
			if(a[j] < a[min])
				min = j;
		}
		swap(&a[min],&a[i]);
	}
}

void bubblesort(int *a,int n)
{
	int f = 0,i,j;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(a[j]>a[j+1])
				swap(&a[j],&a[j+1]);
			f=1;
		}
		if(f==0)
			break;
	}
}

void insertionsort(int *a,int n)
{
	int i,j,key;
	for(i=1;i<n;i++)
	{
		key = a[i];
		j = i-1;
		while(j >= 0 && a[j]>key)
		{
			a[j+1]=a[j];
			j--;
		}
		a[j+1] = key;
	}
}

void merge(int *a,int l,int m ,int r)
{
	int i,j,k,R[m+1],L[m+1];
	int n1 = m-l+1;
	int n2 = r - m;
	for(i=0;i<n1;i++)
		L[i] = a[l+i];
	for(j=0;j<n2;j++)
		R[j] = a[m+j+1];
	i=j=0;k=l;
	while(i<n1 && j<n2)
	{
		if(L[i]<=R[j])
		{
			a[k]=L[i];
			i++;
		}
		else
		{
			a[k]=R[j];
			j++;
		}
		k++;
	}
	while(i<n1)
	{
		a[k]=L[i];
		i++;k++;
	}
	while(j<n2)
	{
		a[k]=R[j];
		j++;k++;
	}
}

void mergesort(int *a,int l,int r)
{
	if(l<r)
	{
		int m = (l+r)/2;
		mergesort(a,l,m);
		mergesort(a,m+1,r);
		merge(a,l,m,r);
	}
}

int partition(int *a,int p,int r)
{
	int x,i,j;
	x = a[r];
	i = p-1;
	for(j=p;j<r;j++)
	{
		if(a[j]<=x)
		{
			i++;
			swap(&a[i],&a[j]);
		}
	}
	swap(&a[i+1],&a[r]);
	return i+1;
}

void quicksort(int *a,int p,int r)
{
	int q;
	if(p<r)
	{
		q = partition(a,p,r);
		quicksort(a,p,q-1);
		quicksort(a,q+1,r);
	}
}

int heap_left(int index)
{
		return 2*index;
}
int heap_right(int index)
{
		return (2*index + 1);
}

void max_heapify(int *a,int i,int heapsize)
{
	int r,l,largest;
	l = heap_left(i+1);l--;
	r = heap_right(i+1);r--;
	if(l<heapsize && a[l] > a[i])
		largest = l;
	else
		largest = i;
	if(r<heapsize && a[r] > a[largest])
		largest = r;
	if(largest != i)
	{
		swap(&a[i],&a[largest]);
		max_heapify(a,largest,heapsize);
	}
}

void build_max_heap(int *a,int heapsize)
{
	int i;
	for(i = (heapsize/2 -1);i>=0;i--)
		max_heapify(a,i,heapsize);
}

void heapsort(int *a,int heapsize)
{
	int i;
	build_max_heap(a,heapsize);
	for(i = heapsize-1;i>=1;i--)
	{
		swap(&a[0],&a[i]);
		heapsize--;
		max_heapify(a,0,heapsize);
	}
}

sort_choice(int *array,int len,int ch)
{
	switch(ch)
	{
		case 1:	bubblesort(array,len);
		        break;
		case 2: selsort(array,len);
			break;
		case 3: insertionsort(array,len);
			break;
		case 4: mergesort(array,0,len-1);
			break;
		case 5: quicksort(array,0,len-1);
			break;
		case 6: heapsort(array,len);
			break;
		default : printf("Invalid choice\n");
	}
}

void main()
{
	int arr[MAX],n,x,i,choice,schoice;
	printf("Input no of element\n");
	scanf("%d",&n);
	printf("Input array\n");
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
	printf("Input choice\n");
	while(1)
	{	
		printf("1: linear search 2: binary search 3: sort 4: exit\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: printf("Input element to search\n");
				scanf("%d",&x);
				if(linsearch(arr,n,x) == -1)
					printf("element not found\n");
				else	
					printf("element found at index : %d\n",linsearch(arr,n,x));
				break;
			case 2: printf("Input element to search\n");
				scanf("%d",&x);
				selsort(arr,n);
				if(binsearch(arr,n,x) == -1)
					printf("element not found\n");
				else
					printf("element found at index : %d\n",binsearch(arr,n,x));
				break;
			case 3: printf("1. bubble 2. selection 3. insertion 4. merge 5. quick 6, heap\n");
				scanf("%d",&schoice);
				sort_choice(arr,n,schoice);
				for(i=0;i<n;i++)
					printf("%d\t",arr[i]);
				printf("\n");
				break;
			case 4: exit(0);
		}
	}
}

