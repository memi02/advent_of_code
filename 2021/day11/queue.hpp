#ifndef QUEUE_H
#define QUEUE_H

struct dato {
  int x;
  int y;
};

struct node {
  dato val;
  node *next;
};

struct queue {
  node *first;
  node *last;
};

queue *init();
void enqueue(dato *val, queue *q);
void dequeue(queue *q);
dato first(queue *q);
void deinit(queue *q);

bool isEmpty(queue *q);

void print(queue *q);
#endif