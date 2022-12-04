#include <cstring>
#include <iostream>

#ifndef NODE_H
#define NODE_H

typedef char dato;

struct node {
  dato val;
  node *next;
};

typedef node *stack;

stack init();
void push(char n, stack &s);
bool pop(stack &s);
node *top(stack s);
void print(stack s);
void deinit(stack s);

bool onlyOneLeft(stack s);
bool isEmpty(stack s);
#endif
