#include "queue.h"

#include <iostream>

queue *init() {
  queue *q = new queue;
  q->first = NULL;
  q->last = q->first;

  return q;
}

void enqueue(dato *val, queue *q) {
  node *n = new node;
  n->val = *val;
  n->next = NULL;

  if (q->first == NULL) {
    q->first = n;
    q->last = n;
  } else {
    q->last->next = n;
    q->last = n;
  }
}

void dequeue(queue *q) {
  if (q->first == NULL) {
    std::cerr << "Lista già vuota..." << std::endl;
    return;
  }
  node *tmp = q->first;
  q->first = q->first->next;

  delete tmp;
}

dato first(queue *q) { return q->first->val; }

void deinit(queue *q) {
  while (q->first != NULL) {
    dequeue(q);
  }
  delete q;
}

void print(queue *q) {
  node *tmp = q->first;
  while (tmp != NULL) {
    std::cout << "x: " << tmp->val.x << ", y: " << tmp->val.y << std::endl;
    tmp = tmp->next;
  }
  std::cout << std::endl;
}
