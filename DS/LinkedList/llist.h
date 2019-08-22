#ifndef LLIST_H
#define LLIST_H

struct Node
{
	int value;
	struct Node* next;
};

typedef struct Node* Node;

int loopFunc(Node n);
Node midFunc(Node n);
Node flipFunc(Node n);
Node comminFunc(Node n1,Node n2);

#endif