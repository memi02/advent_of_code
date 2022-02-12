#include "stack.h"

node *init() { return NULL; }

void push(dato n, stack &s) {
  node *t = new node;
  t->next = s;
  t->val = n;
  s = t;
}

bool pop(stack &s) {
  if (s == NULL) return false;
  node *t = s->next;
  delete s;
  s = t;
  return true;
}

node *top(stack s) { return s; }

void print(stack s) {
  if (s == NULL) {
    std::cout << std::endl;
    return;
  }
  std::cout << s->val;
  print(s->next);
}

void deinit(stack s) {
  if (s == NULL) return;
  deinit(s->next);
  delete s;
}

bool onlyOneLeft(stack s) { return (s->next == NULL) ? true : false; }

bool isEmpty(stack s) { return (s == NULL) ? true : false; }