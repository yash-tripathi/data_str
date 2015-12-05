#include<stdio.h>
#include<stdlib.h>
struct NODE {
	int data;
	struct NODE *father,*left,*right;
};

typedef struct NODE node;

int info(node *nd)
{	
	if(nd)
	return nd->data;
	return;
}

node * father(node *nd)
{
	return nd->father;
}
node * left(node *nd)
{
	return nd->left;
}
node * right(node *nd)
{
	return nd->right;
}
node * brother(node *nd)
{
	if(!father(nd))
		return NULL;
	if(isleft(nd))
		return right(father(nd));
	return left(father(nd));
}

int isleft(node *nd)
{
	return father(nd) && nd == left(father(nd));
}
int isright(node *nd)
{
	return father(nd) && nd == right(father(nd));
}

void init_tree(node *nd)
{
	nd->father=nd->left=nd->right=NULL;
}

node * create()
{
	node *ptr;
	if(!(ptr=(node *) malloc(sizeof(node)))){
		printf("buffer overflow\n");
		exit(1);
	}
	return ptr;
}

node * maketree(int x)
{
	node *new;
	new = create();
	init_tree(new);
	new->data = x;
	return new;
}

void setleft(node *p,int x)
{
	if(!p)
		printf("void insertion\n");
	else if(p->left)
		printf("invalid insertion\n");
	else{
		p->left = maketree(x);
		p->left->father = p;
	}
}

void setright(node *p,int x)
{
	if(!p)
		printf("void insertion\n");
	if(p->left)
		printf("invalid insertion\n");
	else{
		p->right = maketree(x);
		p->right->father = p;
	}
}

node * search(node *p,int k)
{
	if ( !p || k == info(p)) 
		return p;
	if (k < info(p))
		return search(left(p),k);
	else
		return search(right(p),k);
}

node * minimum(node *x)
{
	while(left(x))
		x = left(x);
	return x;
}

node * maximum(node *x)
{
	while(right(x))
		x = right(x);
	return x;
}

node * successor(node *x)
{
	node *y;
	if(right(x))
		return minimum(right(x));
	y=father(x);
	while(y && x == right(y)){
		x = y;
		y = father(y);
	}
	return y;
}

node * predecessor(node *x)
{
	node *y;
	if(left(x))
		return maximum(left(x));;
	y=father(x);
	while(y && x == left(y)){
		x = y;
		y = father(y);
	}
	return y;
}

void insert(node **T,int z)
{
	node *x,*y,*new;
	new = create();
	init_tree(new);
	new->data = z;
	y = NULL;
	x = *T;
	while(x)
	{
		y = x;
		if(z < x->data)
			x = left(x);
		else
			x = right(x);
	}
	new->father = y;
	if(!y)
		*T=new;
	else {
		if(z < info(y))
		y->left = new;
		else
		y->right = new;
	}
}

node * delete(node **T,int z)
{	
	node *d,*y,*x=NULL;
	d = search(*T,z);
	if(!d){
		printf("empty tree\n");
		return NULL;
	}
	if(!left(d) || !right(d))
		y = d;
	else
		y = successor(d);
	if(left(y) != NULL)
		x = left(y);
	else 
		x = right(y);
	if(x != NULL)
		x->father = y->father;
	if(father(y) == NULL)
		*T = x;
	else if(y == left(father(y)))
		father(y)->left = x;
	else
		father(y)->right = x;
	if(y!=d)
		d->data = y->data;
	return d;
}

void preorder(node *tree)
{
	if(tree!=NULL){
		printf("%d\t",tree->data);
		preorder(tree->left);
		preorder(tree->right);
	}
}

void inorder(node *tree)
{
	if(tree!=NULL){
		inorder(tree->left);
		printf("%d\t",tree->data);
		inorder(tree->right);
	}
}

void postorder(node *tree)
{
	if(tree!=NULL){
		postorder(tree->left);
		postorder(tree->right);
		printf("%d\t",tree->data);
	}
}

void main()
{
	node *TREE=NULL,*n,*d;
	int choice,key;
	//n = create();
	printf("input choice\n");
	while(1)
	{
		printf("1: insert 2:delete 3:search 4:inorder 5: search 6: exit\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1: printf("input key\n");
				scanf("%d",&key);
				//init_tree(n);
				//n->data = key;
				insert(&TREE,key);
				break;
			case 2: printf("input key\n");
				scanf("%d",&key);
				d = delete(&TREE,key);
				if(d)
					printf("deleted element is %d\n",d->data);
				break;
			case 3: printf("input key\n");
				scanf("%d",&key);
				d = search(TREE,key);
				if(d)
					printf("element %d found\n",d->data);
				break;
			case 4: printf("inorder,pre,post\n");
				inorder(TREE);
				printf("\n");
				preorder(TREE);
				printf("\n");
				postorder(TREE);
				printf("\n");
				break;
			case 5: printf("Input key to search\n");
				scanf("%d",&key);
				d = search(TREE,key);
				printf("%d",d->data);
				break;
			case 6:	exit(1);
			
			default: printf("invalid choice\n");
		}
	}
}
