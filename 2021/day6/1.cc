#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

void swap(int *a, int *b);

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    cout << "Utilizzo: " << argv[0] << " <input>" << endl;
    exit(0);
  }
  fstream in;
  in.open(argv[1], ios::in);
  if (in.fail()) {
    cerr << "Errore in apertura del file di input" << endl;
    exit(0);
  }
  const int nGiorni = 9;
  int l[nGiorni] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  char buffer;
  for (in.get(buffer); !in.eof(); in.get(buffer)) {
    if (buffer != ',') {
      l[atoi(&buffer)]++;
    }
  }

  for (int i = 0; i < 80; i++) {
    // scorro tutti gli elementi avanti di una posizione
    int tmp = l[0];
    for (int j = nGiorni - 1; j >= 0; j--) {
      swap(&tmp, &l[j]);
    }
    // al termine del ciclo in tmp ho di nuovo l[0]
    // e quindi lo sommo al giorno 6 per resettare il loro "timer"
    l[6] += tmp;
  }

  int r = 0;
  for (int i = 0; i < nGiorni; i++) r += l[i];
  cout << "Risultato: " << r << endl;
  return 0;
}

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}