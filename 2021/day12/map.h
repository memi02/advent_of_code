#ifndef MAP_H
#define MAP_H

struct cave {
  bool isBig;
  char name[10];
  cave *connections[25];
  int connected;
};

struct map {
  cave *c[25];
  int totCave;
};

cave *createCave(char name[10], bool isBig, map *m);
void addConnection(cave *c1, cave *c2);

cave *searchCave(map m, char name[10]);

int numPathFromAtoB(cave *A, cave *B);

#endif
