#include<stdio.h>
#include<stdlib.h>
#include"tree.h"
struct Node
{
	int value;
	struct Node* left;
	struct Node* right;
};

void inOrder(Tree t,operationFunction op)
{
	if(!t)
		return;
	inOrder(t->left,op);
	op(t);
	inOrder(t->right,op);
}
void postOrder(Tree t,operationFunction op)
{
	if(!t)
		return;
	postOrder(t->left,op);
	postOrder(t->right,op);
	op(t);
}
void preOrder(Tree t,operationFunction op)
{
	if(!t)
		return;
	op(t);
	preOrder(t->left,op);
	preOrder(t->right,op);
}

void (*func[])(Tree t,operationFunction op) = {inOrder,postOrder,preOrder}; 

int create(Tree* t)
{
	*t=(Tree)malloc(sizeof(struct Node));
	if(t)
		return 1;
	return 0;
}

Tree newTree(Tree* t,int val)
{
	create(t);
	if(!t)
		return NULL;
	(*t)->value=val;
	(*t)->right=NULL;
	(*t)->left=NULL;
	return *t;
}

Tree insert(Tree t,int val)
{
	if(!t)
	{
		newTree(&t,val);
		return t;
	}
	if(val>t->value)
	{
		t->right=insert(t->right,val);
	}
	else
	{
		t->left=insert(t->left,val);
	}
	return t;
}

Tree search(Tree t,int val)
{
	if(!t)
	{
		return NULL;
	}
	if(t->value==val)
	{
		return t;
	}
	if(val>t->value)
	{
		return search(t->right,val);
	}
	else
	{
		return search(t->left,val);
	}
}

Tree findMin(Tree t)
{
	Tree tmp=NULL;
	while(t->left)
	{
		tmp=t;
		t=t->left;
	}
	if(tmp)
	{
		tmp->left=t->right;
	}
	return t;
}

Tree findMax(Tree t)
{
	Tree tmp=NULL;
	while(t->right)
	{
		tmp=t;
		t=t->right;
	}
	if(tmp)
	{
		tmp->right=t->left;
	}
	return t;

}

Tree delete(Tree t,int val)
{
	Tree tmp;
	if(!t)
	{
		return NULL;
	}
	if(t->value==val)
	{
		if((!t->left)&&(!t->right))
		{
			free(t);
			return NULL;
		}
		if(t->left)
		{
			tmp=findMax(t->left);
			if(tmp==t->left)
				t->left=tmp->left;
			t->value=tmp->value;
			free(tmp);
		}
		else
		{
			tmp=findMin(t->right);
			if(tmp==t->right)
				t->right=tmp->right;
			t->value=tmp->value;
			free(tmp);
		}
		return t;
	}
	if(val>t->value)
	{
		t->right=delete(t->right,val);
	}
	else
	{
		t->left=delete(t->left,val);
	}
	return t;
}

int destroy(Tree t)
{
	if(t)
	{
		destroy(t->left);
		destroy(t->right);
		free(t);
	}
}

void walk(Tree t,operationFunction op,int order)
{
	if((order>=0)&&(order<3))
		(*func[order])(t,op);
}
void printTree(Tree t)
{
	printf("%d\n",t->value);
}
