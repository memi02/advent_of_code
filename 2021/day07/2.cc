#include <climits>
#include <fstream>
#include <iostream>

#include "queue.h"

using namespace std;

int pow(int b, int e);
void swap(int &a, int &b);
void bubblesort(int arr[], int n);

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

  queue *q = init();
  char buffer;
  int t[10];
  int tmp = 0, c = 0;
  int nNumeri = 0;
  for (in.get(buffer); !in.eof(); in.get(buffer)) {
    // cout << "buffer: " << buffer << endl;
    if (buffer == ',') {
      for (int i = c - 1; i >= 0; i--) tmp += t[i] * pow(10, c - 1 - i);
      // cout << "tmp: " << tmp << endl;
      nNumeri++;
      enqueue(&tmp, q);
      // cout << "First: " << first(q) << endl;
      c = 0;
      tmp = 0;
    } else {
      t[c] = buffer - '0';
      c++;
    }
  }
  // alla fine del ciclo devo eseguire ancora una volta per mettere l'ultimo
  // numero
  for (int i = c - 1; i >= 0; i--) tmp += t[i] * pow(10, c - 1 - i);
  nNumeri++;
  enqueue(&tmp, q);

  int *n = new int[nNumeri];
  // cout << "nNumeri: " << nNumeri << endl;
  for (int i = 0; !isEmpty(q); i++) {
    n[i] = first(q);
    dequeue(q);
    // cout << "n[" << i << "]: " << n[i] << endl;
  }
  deinit(q);

  bubblesort(n, nNumeri);
  // for (int i = 0; i < nNumeri; i++) cout << "n[" << i << "]: " << n[i] <<
  // endl;

  int med = 0;  // media + calcoli
  for (int i = 0; i < nNumeri; i++) med += n[i];
  med = med / nNumeri;

  cout << "Media: " << med << endl;

  unsigned long long int carb = ULLONG_MAX;
  for (int j = med - 5; j < med + 5; j++) {
    int ca = 0;
    for (int i = 0; i < nNumeri; i++) {
      // cout << "n[" << i << "]: " << n[i] << endl;
      ca += (pow(j - n[i], 2) + abs(j - n[i])) / 2;
      // cout << "carb aggiunto: " << abs(n[i] - med) << endl;
    }
    if (ca < carb) carb = ca;
  }
  cout << "Risultato: " << carb << endl;
  return 0;
}

int pow(int b, int e) {
  int r = 1;
  for (int i = 0; i < e; i++) r *= b;
  return r;
}

void swap(int &a, int &b) {
  int c = a;
  a = b;
  b = c;
}

void bubblesort(int arr[], int n) {
  int i, k;
  for (k = n - 1; k > 0; k--) {
    for (i = 0; i < k; i++) {
      if (arr[i] > arr[i + 1]) {
        swap(arr[i], arr[i + 1]);
      }
    }
  }
}