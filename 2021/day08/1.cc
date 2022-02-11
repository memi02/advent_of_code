#include <cstring>
#include <fstream>
#include <iostream>

#include "queue.h"

using namespace std;

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    cout << "Utilizzo: " << argv[0] << endl;
    exit(0);
  }
  fstream in;
  in.open(argv[1], ios::in);
  if (in.fail()) {
    cout << "Errore apertura file di input" << endl;
    exit(0);
  }

    char buffer[8];
  int c = 0;
  int counter = 0;
  for (in >> buffer; !in.eof(); in >> buffer) {
    if (c > 10) {
      if (c == 14) {
        c = -1;
      };
      if (strlen(buffer) == 2 || strlen(buffer) == 4 || strlen(buffer) == 3 ||
          strlen(buffer) == 7) {
        counter++;
      }
    }
    c++;
  }
  cout << "Risultato: " << counter << endl;
}