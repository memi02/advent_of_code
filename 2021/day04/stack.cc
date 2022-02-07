#include "stack.h"

node *init() {
  node *first = new node;
  first->next = NULL;

  return first;
}

void push(const dato *n, node *s) {
  node *t = s->next;
  s->next = new node;
  s->val = *n;
  s->next->next = t;
}

bool pop(node *s) {
  if (s->next == NULL) return false;

  node *t = s->next;

  s->next = s->next->next;

  delete t;
  return true;
}

node *top(node *s) { return s->next; }

void print(node *s) {
  if (s->next == NULL) return;
  std::cout << s->next->val << std::endl;
  print(s->next);
}

void deinit(node *s) {
  if (s != NULL) {
    deinit(s->next);
    delete s;
  }
}

bool onlyOneLeft(node *s) { return (s->next->next == NULL) ? true : false; }