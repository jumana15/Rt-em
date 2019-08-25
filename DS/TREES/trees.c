#include<stdio.h>
#include<stdlib.h>

struct Node
{
	int value;
	struct Node* left;
	struct Node* right;
};

typedef struct Node* Tree;

typedef void (*operationFunc)(Tree t);

void inOrder(Tree t)
{
	if(!t)
		return;
	inOrder(t->left);
	printf("%d\n",t->value);
	inOrder(t->right);
}
void postOrder(Tree t)
{
	if(!t)
		return;
	inOrder(t->left);
	inOrder(t->right);
	printf("%d\n",t->value);
}
void preOrder(Tree t)
{
	if(!t)
		return;
	printf("%d\n",t->value);
	inOrder(t->left);
	inOrder(t->right);
}

void (*func[])(Tree t,operationFunc op) = {inOrder,postOrder,preOrder}; 

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

Tree delete(Tree t,int val)
{
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
			/*tmp=deepMax(t);
			t->value=tmp->val;
			if(tmp->left)
				tmp->value*/
			t->value=t->left->value;
			free(t->left);
			t->left=NULL;
		}
		else
		{
			t->value=t->right->value;
			free(t->right);
			t->right=NULL;
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

void walk(Tree t,operationFunc op,int order)
{
	if((order>=0)&&(order<3))
		(*func[order])(t,op);
}

int main()
{
    int x,num,flag=1;
    Tree t;
    /*elementDestroy d=destroyFunc;
    elementCompare c=cmpFunc;*/
    while(1)
    {
        printf("Choose option:\n1->Create Array.\n2->Insert.\n3->Delete.\n4->Print.\n5->Destroy.\nElse->stop.\n");
        scanf("%d",&x);
        switch(x)
        {
            case 1:
            	printf("Enter a number:\n");
            	scanf("%d",&num);
                newTree(&t,num);
                break;
            case 2:
            	printf("Enter a number:\n");
          		scanf("%d",&num);
                insert(t,num);
                break;
            case 3:
            	printf("Enter a number:\n");
            	scanf("%d",&num);
                delete(t,num);
                break;
            case 4:
                walk(func,0,t);
                break;
            case 5:
                destroy(t);
                t=NULL;
                break;
            default:
                flag=0;
                break;
        }
        if(!flag)
            break;
    }
    return 0;
}
