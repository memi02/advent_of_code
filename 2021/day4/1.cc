#include <fstream>
#include <iostream>

#include "queue.h"

using namespace std;

int valutaTabella(int **tabella, const int nColonne, const int nRighe, queue *q,
                  int *punteggio);
// Ritorna la profondità a cui si è completata l'operazione
int riempiTabella(int **tabella, const int nColonne, const int nRighe, node *q,
                  int *lastVal);
bool tabellaCompleta(int **tabella, const int nColonne, const int nRighe);

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    cout << "Utilizzo: ./es1.out <input>" << endl;
    exit(0);
  }

  fstream in;
  in.open(argv[1], ios::in);
  if (in.fail()) {
    cout << "Errore file input" << endl;
    exit(0);
  }
  int nNumeri = 1;
  char buffer;
  int tmp = 0;
  queue *q = init();

  for (in.get(buffer); buffer != '\n'; in.get(buffer)) {
    if (buffer == ',') {
      enqueue(&tmp, q);
      tmp = 0;
      nNumeri++;
    } else {
      tmp *= 10;
      tmp += (buffer - '0');
    }
  }
  // questo inserimento è già sommato in nNumeri perchè parte da uno
  enqueue(&tmp, q);

  // mi pone esattamente all'inizio della riga contenente la prima tabella
  in.get(buffer);

  const int nColonne = 5, nRighe = 5;
  int **bingo = new int *[nColonne];
  for (int i = 0; i < nColonne; i++) {
    bingo[i] = new int[nRighe];
  }

  int i = 0, j = 0, c = 0;
  tmp = 0;
  int minDep = nNumeri + 1;
  int maxPunt = 0;
  for (in.get(buffer); !in.eof(); in.get(buffer)) {
    switch (c % 3) {
      case 0:
        // mi dice che sono nella cifra delle decine di un numero (se
        // presente)
        if (buffer != ' ')
          tmp = atoi(&buffer) * 10;
        else
          tmp = 0;
        c++;
        break;
      case 1:
        // mi dice che sono nella cifra delle unità del numero
        bingo[i][j] = atoi(&buffer) + tmp;
        c++;
        break;
      case 2:
        // mi dice che sono nello spazio che separa due numeri o nel \n tra
        // una riga e l'altra

        if (buffer == '\n') {
          i++;
          j = 0;
        } else
          j++;
        c++;
        if (i == 5) {
          // QUI SO CHE LA TABELLA è COMPELTA... QUINDI POSSO VALUTARLA
          int punteggio;
          int dep = valutaTabella(bingo, nColonne, nRighe, q, &punteggio);
          if (dep < minDep) {
            minDep = dep;
            maxPunt = punteggio;
          }
          // per il reset devo tenere in considerazione che devo leggere un
          // secondo \n, di conseguenza pongo i contatori tenendo conto che
          // saranno incrementati ancora una volta (dato che c è usato solo
          // con % 3 c = - 1 = 2)
          c = 2;
          i = -1;
          j = 0;
        }
        break;
    }
  }

  cout << "Punteggio ottenuto: " << maxPunt << endl;

  for (int i = 0; i < nColonne; i++) delete[] bingo[i];
  delete[] bingo;

  deinit(q);
  in.close();
  return 0;
}

int valutaTabella(int **tabella, const int nColonne, const int nRighe, queue *q,
                  int *punteggio) {
  int lastVal;
  int d = riempiTabella(tabella, nColonne, nRighe, q->first, &lastVal);
  int s = 0;
  for (int i = 0; i < nColonne; i++)
    for (int j = 0; j < nRighe; j++)
      if (tabella[i][j] != -1) s += tabella[i][j];
  *punteggio = s * lastVal;
  return d;
}

int riempiTabella(int **tabella, const int nColonne, const int nRighe, node *q,
                  int *lastVal) {
  for (int i = 0; i < nColonne; i++) {
    for (int j = 0; j < nColonne; j++) {
      if (q->val == tabella[i][j]) tabella[i][j] = -1;
    }
  }

  if (tabellaCompleta(tabella, nColonne, nRighe)) {
    *lastVal = q->val;
    return 0;
  }
  if (q->next == NULL) return nColonne * nRighe;
  return 1 + riempiTabella(tabella, nColonne, nRighe, q->next, lastVal);
}

bool tabellaCompleta(int **tabella, const int nColonne, const int nRighe) {
  for (int i = 0; i < nColonne; i++) {
    bool cond = true;
    for (int j = 0; j < nRighe && cond; j++)
      if (tabella[i][j] != -1) cond = false;
    if (cond) return true;
  }
  for (int j = 0; j < nRighe; j++) {
    bool cond = true;
    for (int i = 0; i < nColonne && cond; i++)
      if (tabella[i][j] != -1) cond = false;
    if (cond) return true;
  }
  return false;
}
