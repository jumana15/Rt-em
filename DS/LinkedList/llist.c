#include<stdio.h>
#include<stdlib.h>
#include"llist.h"

int loopFunc(Node n)
{
	Node i=n,j=n;
	if((!n)||(!n->next)||(!n->next->next))
		return 0;
	do
	{
		i=i->next;
		j=j->next->next;
	}
	while((j->next)&&(j->next->next)&&(i->next)&&(i!=j));
	if(i==j)
		return 1;
	return 0;
}

Node midFunc(Node n)
{
	Node i=n,j=n;
	if((!n)||(!n->next)||(!n->next->next))
		return NULL;
	do
	{
		i=i->next;
		j=j->next->next;
	}
	while((j->next)&&(j->next->next));
	return i;
}

/*Node FlipFuncRec(Node n,Node b)
{
	Node tmp;
	if(!n->next)
	{
		b=n;
		return n;
	}
	tmp=FlipFunc(n->next,b);
	tmp->next=n;
	n->next=NULL;
	return n;
}*/

Node flipFunc(Node n)
{
	Node tmp,tmp2;
	if(!n)
		return NULL;
	tmp=n->next;
	tmp2=NULL;
	while(tmp)
	{
		n->next=tmp2;
		tmp2=n;
		n=tmp;
		tmp=tmp->next;
	}
	n->next=tmp2;
	return n;
}

Node comminFunc(Node n1,Node n2)
{
	int i=0,counter1=0,counter2=0;
	Node node1=n1,node2=n2;
	while((n1)&&(n2))
	{
		counter1++;
		n1=n1->next;
		counter2++;
		n2=n2->next;
	}
	if(n1)
	{
		while(n1)
		{
			counter1++;
			n1=n1->next;
		}
		for(i=0;i<counter1-counter2;i++)
		{
			node1=node1->next;
		}
	}
	if(n2)
	{
		while(n2)
		{
			counter2++;
			n2=n2->next;
		}
		for(i=0;i<counter2-counter1;i++)
		{
			node2=node2->next;
		}
	}
	while(node2->next)
	{
		if(node1==node2)
		{
			return node1;
		}
		node1=node1->next;
		node2=node2->next;
	}
	return NULL;
}
