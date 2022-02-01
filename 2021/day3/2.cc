#include <cstdlib>
#include <fstream>
#include <iostream>

#include "stack.h"

using namespace std;

int pow(int n, int exp);

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    cout << "Utilizzo: ./es1.out <input>" << endl;
    exit(0);
  }
  fstream in;
  in.open(argv[1], ios::in);
  if (in.fail()) {
    cerr << "Errore apertura file input" << endl;
    exit(0);
  }

  // salvo tutto il contenuto del file nello stack
  node *s = init();
  char buffer[13];
  while (in >> buffer) {
    push(buffer, s);
  }

  char ox[12] = "\0\0\0\0\0\0\0\0\0\0\0";
  node *b = init();
  for (int i = 0; i < 12; i++) {
    if (onlyOneLeft(s)) {
      ox[i] = top(s)->val[i];
      continue;
    }
    int n1 = 0, nTot = 0;
    while (s->next != NULL) {
      if (top(s)->val[i] == '1') {
        ++n1;
      }
      ++nTot;
      push(top(s)->val, b);
      pop(s);
    }
    if (nTot % 2 == 0)
      ox[i] = ((n1 >= (nTot / 2)) ? '1' : '0');
    else
      ox[i] = ((n1 > (nTot / 2)) ? '1' : '0');
    while (b->next != NULL) {
      if ((top(b)->val)[i] != ox[i])
        pop(b);
      else {
        push(top(b)->val, s);
        pop(b);
      }
    }
    /*     cout << "____________ [n1 = " << n1 << ", "
             << "nTot = " << nTot << "]" << endl;
        print(s);
        cout << "____________ [" << i << "]" << endl << ox << endl; */
  }
  cout << "ox: " << ox << endl;
  unsigned int ox_n = stoi(ox, 0, 2);
  /* for (int i = 11; i >= 0; i--) {
    if (ox[11 - i] == '1') {
      ox_n += pow(2, i);
    }
  } */
  cout << "ox_n: " << ox_n << endl;

  /* resetto tutto per il calcolo del secondo valore */
  deinit(s);
  deinit(b);

  s = init();
  b = init();

  in.clear();
  in.seekg(0);

  while (in >> buffer) {
    push(buffer, s);
  }

  char co[12] = "\0\0\0\0\0\0\0\0\0\0\0";
  for (int i = 0; i < 12; i++) {
    if (onlyOneLeft(s)) {
      co[i] = top(s)->val[i];
      continue;
    }
    int n1 = 0, nTot = 0;
    while (s->next != NULL) {
      if (top(s)->val[i] == '1') {
        ++n1;
      }
      ++nTot;
      push(top(s)->val, b);
      pop(s);
    }
    if (nTot % 2 == 0)
      co[i] = ((n1 < (nTot / 2)) ? '1' : '0');
    else
      co[i] = ((n1 < (nTot / 2) + 1) ? '1' : '0');
    while (b->next != NULL) {
      if (top(b)->val[i] != co[i])
        pop(b);
      else {
        push(top(b)->val, s);
        pop(b);
      }
    }
    /*     cout << "____________ [n1 = " << n1 << ", "
             << "nTot = " << nTot << "]" << endl;
        print(s);
        cout << "____________ [" << i << "]" << endl << co << endl; */
  }
  cout << "co: " << co << endl;
  unsigned int co_n = stoi(co, 0, 2);
  /*   for (int i = 11; i >= 0; i--) {
      if (co[11 - i] == '1') {
        co_n += pow(2, i);
      }
    } */
  cout << "co_n: " << co_n << endl;

  cout << "prodotto: " << co_n * ox_n << endl;

  in.close();
  return 0;
}

int pow(int n, int exp) {
  int r = 1;
  for (int i = 0; i < exp; i++) r *= n;
  return r;
}