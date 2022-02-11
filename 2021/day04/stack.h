#include <cstring>
#include <iostream>

#ifndef NODE_H
#define NODE_H

typedef int dato;

struct node {
  dato val;
  node *next;
};

node *init();
void push(const int *n, node *s);
bool pop(node *s);
node *top(node *s);
void print(node *s);
void deinit(node *s);

bool onlyOneLeft(node *s);

#endif
