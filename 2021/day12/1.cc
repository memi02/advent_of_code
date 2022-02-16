#include <fstream>
#include <iostream>

#include "map.h"

using namespace std;

bool isUpperCase(char c);

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << "<input_file>" << endl;
    exit(0);
  }
  fstream in;
  in.open(argv[1], ios::in);
  if (in.fail()) {
    cout << "Error opening input file" << endl;
    exit(0);
  }

  char b;
  char name1[10], name2[10];
  bool isOne = true;
  int i = 0;

  map m;
  m.totCave = 0;

  while (in.get(b)) {
    if (b != '\n' && b != '-') {
      if (isOne)
        name1[i] = b;
      else
        name2[i] = b;
      i++;
    } else if (b == '-') {
      name1[i] = '\0';
      i = 0;
      isOne = false;
    } else if (b == '\n') {
      name2[i] = '\0';
      /* I need to add the cave if they are not present yet
      and create a connection between them */
      cave *cave1 = searchCave(m, name1);
      cave *cave2 = searchCave(m, name2);

      if (cave1 == NULL) cave1 = createCave(name1, isUpperCase(name1[0]), &m);
      if (cave2 == NULL) cave2 = createCave(name2, isUpperCase(name2[0]), &m);

      addConnection(cave1, cave2);

      i = 0;
      isOne = true;
    }
  }
  // To print out every cave inserted
  for (int i = 0; i < m.totCave; i++) {
    cout << "cave: " << m.c[i]->name << endl;
    cout << "isBig: " << ((m.c[i]->isBig) ? "true" : "false") << endl;
    cout << "connected: " << m.c[i]->connected << endl;
    for (int j = 0; j < m.c[i]->connected; j++) {
      cout << "connection n." << j << ": " << m.c[i]->connections[j]->name
           << endl;
    }
    cout << endl;
  }
  char start[6] = "start", end[4] = "end";
  int tot = numPathFromAtoB(searchCave(m, start), searchCave(m, end));

  cout << "Answer:" << tot << endl;

  in.close();
  return 0;
}

bool isUpperCase(char c) {
  if ('A' <= c && c <= 'Z') return true;
  return false;
}
