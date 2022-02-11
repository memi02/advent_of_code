#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

struct point {
  int x;
  int y;
};

void convertiInNumeri(char *str, const int strMax, int *n1, int *n2);

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    cout << "Utilizzo: " << argv[0] << " <input>" << endl;
    exit(0);
  }
  fstream in;
  in.open(argv[1], ios::in);
  if (in.fail()) {
    cout << "Errore in apertura del file di input" << endl;
    exit(0);
  }

  const int maxBuffer = 10;
  char buffer[maxBuffer];
  int c = 0;
  point p1, p2;

  const int nRighe = 1000, nColonne = 1000;
  int tab[nColonne][nRighe];
  for (int i = 0; i < nColonne; i++)
    for (int j = 0; j < nRighe; j++) tab[i][j] = 0;

  for (in >> buffer; !in.eof(); in >> buffer) {
    switch (c) {
      case 0:
        convertiInNumeri(buffer, maxBuffer, &p1.x, &p1.y);
        c++;
        break;
      case 1:
        c++;
        break;
      case 2:
        convertiInNumeri(buffer, maxBuffer, &p2.x, &p2.y);
        c = 0;
        if (p1.x == p2.x) {
          // cout << "p1: " << p1.x << ", " << p1.y << endl
          //      << "p2: " << p2.x << ", " << p2.y << endl
          //      << endl;
          if (p2.y < p1.y) swap(p1.y, p2.y);
          for (; p1.y <= p2.y; p1.y++) {
            (tab[p1.x][p1.y])++;
          }
        } else if (p1.y == p2.y) {
          // cout << "p1: " << p1.x << ", " << p1.y << endl
          //      << "p2: " << p2.x << ", " << p2.y << endl
          //      << endl;
          if (p2.x < p1.x) swap(p1.x, p2.x);
          for (; p1.x <= p2.x; p1.x++) {
            (tab[p1.x][p2.y])++;
          }
        }
        // cout << "p1: " << p1.x << ", " << p1.y << endl
        //      << "p2: " << p2.x << ", " << p2.y << endl
        //      << endl;
        break;
    }
  }

  int count = 0;
  for (int i = 0; i < nColonne; i++) {
    for (int j = 0; j < nRighe; j++) {
      if (tab[i][j] > 1) count++;
    };
  }
  cout << "Risultato: " << count << endl;
  return 0;
}

void convertiInNumeri(char *str, const int strMax, int *n1, int *n2) {
  // innanzitutto cerco la virgola e la sostituisco con un carattere
  // terminatore, per creare virtualmente due stringhe, segnadomi la sua
  // posizione
  char *comma = NULL;
  for (int i = 0; i < strMax; i++) {
    if (str[i] == ',') comma = &str[i];
  }
  *comma = '\0';
  *n1 = atoi(str);
  *n2 = atoi(comma + 1);
}