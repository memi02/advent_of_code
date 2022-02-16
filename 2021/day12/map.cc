#include "map.h"

#include <string.h>

#include <iostream>

using namespace std;

int numPathFromAtoB_sup(cave *A, cave *B, char AlreadyVisited[25][10],
                        int numAlreadyVisited, int d = 0);

cave *createCave(char name[10], bool isBig, map *m) {
  // I create the new cave
  cave *c = new cave;
  strcpy(c->name, name);
  c->isBig = isBig;
  c->connected = 0;

  // And I add it to the map
  m->c[m->totCave] = c;
  m->totCave++;
  return c;
}

void addConnection(cave *c1, cave *c2) {
  c1->connections[c1->connected] = c2;
  c2->connections[c2->connected] = c1;
  c1->connected++;
  c2->connected++;
}

cave *searchCave(map m, char name[10]) {
  for (int i = 0; i < m.totCave; i++) {
    if (!strcmp(name, m.c[i]->name)) return m.c[i];
  }
  return NULL;
}

int numPathFromAtoB(cave *A, cave *B) {
  char AlreadyVisited[25][10];
  int numAlreadyVisited = 0;
  return numPathFromAtoB_sup(A, B, AlreadyVisited, numAlreadyVisited);
}

int numPathFromAtoB_sup(cave *A, cave *B, char AlreadyVisited[25][10],
                        int numAlreadyVisited, int d) {
  for (int i = 0; i < d; i++) cout << "  ";
  cout << "A->name:" << A->name << endl;
  for (int i = 0; i < numAlreadyVisited; i++) {
    cout << "AlreadyVisited[" << i << "]: " << AlreadyVisited[i] << endl;
  }
  cout << "numAlreadyVisited: " << numAlreadyVisited << endl;
  cout << endl;

  if (!strcmp(A->name, B->name)) {
    return 1;
  }

  int tot = 0;
  for (int i = 0; i < A->connected; i++) {
    bool toSearch = true;
    if (!A->connections[i]->isBig) {
      for (int j = 0; j < numAlreadyVisited; j++) {
        if (!strcmp(A->connections[i]->name, AlreadyVisited[j])) {
          toSearch = false;
        }
      }
    }
    if (toSearch) {
      strcpy(AlreadyVisited[numAlreadyVisited], A->name);
      tot += numPathFromAtoB_sup(A->connections[i], B, AlreadyVisited,
                                 numAlreadyVisited + 1, d + 1);
    }
  }
  return tot;
}