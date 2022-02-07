#include <fstream>
#include <iostream>

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

  char buffer[13];
  int n1[12] = {};
  int nTot = 0;
  while (in >> buffer) {
    for (int i = 0; i < 12; i++) {
      if (buffer[i] == '1') ++n1[i];
    }
    ++nTot;
  }
  unsigned int g = 0;
  for (int i = 11; i >= 0; i--) {
    if (n1[11 - i] - (nTot / 2) > 0) {
      g += pow(2, i);
    }
  }
  unsigned int e = 0;
  for (int i = 11; i >= 0; i--) {
    if (n1[11 - i] - (nTot / 2) < 0) {
      e += pow(2, i);
    }
  }

  cout << "Gamma : " << g << endl;
  cout << "Epsilon: " << e << endl;
  cout << "Prodotto: " << g * e << endl;

  in.close();
  return 0;
}

int pow(int n, int exp) {
  int r = 1;
  for (int i = 0; i < exp; i++) r *= n;
  return r;
}