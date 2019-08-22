#include<stdio.h>
#include<stdlib.h>
#include "llist.h"

int main()
{
	Node tmp,a=NULL,b=NULL,c=NULL,m=NULL,n=NULL,o=NULL,p=NULL,r=NULL,s=NULL;
	a=(Node)malloc(sizeof(struct Node));
	b=(Node)malloc(sizeof(struct Node));
	c=(Node)malloc(sizeof(struct Node));
	m=(Node)malloc(sizeof(struct Node));
	n=(Node)malloc(sizeof(struct Node));
	o=(Node)malloc(sizeof(struct Node));
	p=(Node)malloc(sizeof(struct Node));
	r=(Node)malloc(sizeof(struct Node));
	s=(Node)malloc(sizeof(struct Node));
	tmp=(Node)malloc(sizeof(struct Node));
	a->value=1;
	a->next=b;
	b->value=2;
	b->next=c;
	c->value=3;
	c->next=m;
	m->value=4;
	m->next=n;
	n->value=5;
	n->next=o;
	o->value=6;
	o->next=p;
	p->value=7;
	p->next=NULL;
	/*Find the Commin Node*/
	/**/
	r->value=8;
	r->next=s;
	s->value=9;
	s->next=m;
	tmp=comminFunc(a,r);
	printf("Node value=%d\n",tmp->value);
	/**/
	/*Flip List*/
	/*
	tmp=flipFunc(a);
	printf("First Node value=%d\n",tmp->value);
	*/
	/*Check Loop*/
	/*
	printf("Loop=%d\n",loopFunc(a));
	p->next=c;
	printf("Loop=%d\n",loopFunc(a));
	*/
	/*Find the Middle*/
	/*
	tmp=midFunc(a);
	printf("Node value=%d\n",tmp->value);
	*/
	free(a);
	free(b);
	free(c);
	free(m);
	free(n);
	free(o);
	free(p);
	free(r);
	free(s);
	return 0;
}