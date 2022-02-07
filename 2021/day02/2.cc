#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    cout << "Utlilizzo: ./es2.out <input> <output>" << endl;
    exit(0);
  }

  fstream in, out;
  in.open(argv[1], ios::in);
  if (in.fail()) {
    cerr << "Errore in apertura del file di input" << endl;
    exit(0);
  }
  out.open(argv[2], ios::out);
  if (out.fail()) {
    cerr << "Errore in apertura del file di output" << endl;
    exit(0);
  }

  int h = 0, d = 0, a = 0;
  char buffer[16];
  while (in >> buffer) {
    int n;
    in >> n;
    switch (buffer[0]) {
      case 'f':
        h += n;
        d += a * n;
        break;
      case 'd':
        a += n;
        break;
      case 'u':
        a -= n;
        break;
    }
  }
  cout << "Profondità: " << d << endl;
  cout << "Spostamento orizzontale: " << h << endl;
  cout << "Prodotto: " << d * h << endl;

  in.close();
  out.close();
  return 0;
}
