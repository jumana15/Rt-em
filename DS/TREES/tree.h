#ifndef TREE_H
#define TREE_H

typedef struct Node* Tree;

typedef void (*operationFunction)(Tree t);

int createNode(Tree* t);
Tree newTreeNode(Tree* t,int val);
Tree insertNode(Tree t,int val);
Tree searchNode(Tree t,int val);
Tree deleteNode(Tree t,int val);
int destroy(Tree t);
void walk(Tree t,operationFunction op,int order);
void printTree(Tree t);

#endif