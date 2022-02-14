#include <fstream>
#include <iostream>

#include "queue.h"

using namespace std;

void Increase(int x, int y, int tab[10][10], queue* q);

int main(int argc, char const* argv[]) {
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
  int tab[10][10];
  int i = 0, j = 0;
  while (in.get(b)) {
    if (b == '\n') {
      j++;
      i = 0;
    } else {
      tab[i][j] = b - '0';
      i++;
    }
  }

  int tot = 0;
  for (int turn = 0; turn < 100; turn++) {
    queue* toFlash = init();
    /*
    First, the energy level of each octopus increases by 1.
    */
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        Increase(i, j, tab, toFlash);
      }
    }
    /*
    Then, any octopus with an energy level greater than 9 flashes.This
    increases the energy level of all adjacent octopuses by 1, including
    octopuses that are diagonally adjacent.If this causes an octopus to have an
    energy level greater than 9, it also flashes.This process continues as long
    as new octopuses keep having their energy level increased beyond 9.( An
    octopus can only flash at most once per step.)
    */
    while (!isEmpty(toFlash)) {
      dato flashing = first(toFlash);
      if (flashing.x != 0 && flashing.y != 0) {
        Increase(flashing.x - 1, flashing.y - 1, tab, toFlash);
      }
      if (flashing.x != 0) {
        Increase(flashing.x - 1, flashing.y, tab, toFlash);
      }
      if (flashing.x != 0 && flashing.y != 9) {
        Increase(flashing.x - 1, flashing.y + 1, tab, toFlash);
      }
      if (flashing.y != 9) {
        Increase(flashing.x, flashing.y + 1, tab, toFlash);
      }
      if (flashing.x != 9 && flashing.y != 9) {
        Increase(flashing.x + 1, flashing.y + 1, tab, toFlash);
      }
      if (flashing.x != 9) {
        Increase(flashing.x + 1, flashing.y, tab, toFlash);
      }
      if (flashing.x != 9 && flashing.y != 0) {
        Increase(flashing.x + 1, flashing.y - 1, tab, toFlash);
      }
      if (flashing.y != 0) {
        Increase(flashing.x, flashing.y - 1, tab, toFlash);
      }

      dequeue(toFlash);
    }
    /*
    Finally, any octopus that flashed during
    this step has its energy level set to 0, as it used all of its energy to
    flash.
    */
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        if (tab[i][j] > 9) {
          tab[i][j] = 0;
          tot++;
        }
      }
    }
    cout << "Turn: " << turn << endl;
    for (int j = 0; j < 10; j++) {
      for (int i = 0; i < 10; i++) {
        if (tab[i][j] != 0)
          cout << tab[i][j];
        else
          cout << " ";
      }
      cout << endl;
    }
    cout << endl;
  }
  cout << "Answer: " << tot << endl;

  in.close();
  return 0;
}

void Increase(int x, int y, int tab[10][10], queue* q) {
  tab[x][y]++;
  if (tab[x][y] == 10) {
    dato tmp = {x, y};
    enqueue(&tmp, q);
  }
}
