#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    cout << "Utilizzo ./day1.out <file>" << endl;
    exit(0);
  }

  fstream in;
  in.open(argv[1], ios::in);
  if (in.fail()) {
    cerr << "Errore in apertura del file di input" << endl;
    exit(0);
  }

  int nInc = 0;
  int buffer, tmp;
  in >> tmp;
  cout << tmp << " : primo elemento, impossibile confrontare" << endl;
  while (in >> buffer) {
    if (buffer > tmp) {
      cout << buffer << " (increased)" << endl;
      ++nInc;
    } else
      cout << buffer << " (decreased or equal)" << endl;
    tmp = buffer;
  }
  cout << "la distanza è aumentata " << nInc << " volte" << endl;
  return 0;
}
