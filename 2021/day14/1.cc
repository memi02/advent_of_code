#include <limits.h>
#include <string.h>

#include <cstring>
#include <fstream>
#include <iostream>

#include "charSequence.h"

using namespace std;

int max(int *arr, int length);
int min(int *arr, int length);

int main(int argc, char const *argv[]) {
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

  // I read the starting sequence
  char sequenceStarter[25];
  in >> sequenceStarter;

  charSequence *sequence = new charSequence;
  sequence->input(sequenceStarter);

  const int MAXELEMENTS = 100;
  char **toFind = new char *[MAXELEMENTS];
  for (int i = 0; i < MAXELEMENTS; i++) toFind[i] = new char[3];

  char toInsert[MAXELEMENTS];

  char b[3];

  int c = 0;
  while (in >> b) {
    strcpy(toFind[c], b);
    in >> b;  // I read the ->, wich i don't need
    in >> b;  // I read the charachter to insert

    toInsert[c] = b[0];
    c++;
  }

  // I print the same thing from the input document, to be sure they're right
  // sequence->print();
  // cout << endl;
  // for (int i = 0; i < c; i++) {
  //   cout << toFind[i] << " -> " << toInsert[i] << endl;
  // }

  for (int i = 0; i < 25; i++) {
    sequence->insertBetweenLetters(toFind, toInsert, c);
    cout << endl << "cycle n. " << i << endl;
    int *f = sequence->charachterFrequences();
    for (int i = 0; i < 26; i++)
      if (f[i] != 0) cout << char('A' + i) << ": " << f[i] << endl;
  }

  cout << "Sequence lenght: " << sequence->length() << endl;

  int *frequences = sequence->charachterFrequences();
  // for (int i = 0; i < 26; i++) {
  //   cout << char('A' + i) << ": " << frequences[i] << endl;
  // }

  cout << "Answer: " << max(frequences, 26) - min(frequences, 26) << endl;

  for (int i = 0; i < MAXELEMENTS; i++) delete[] toFind[i];
  delete[] toFind;
}

int max(int *arr, int length) {
  int max = 0;
  for (int i = 0; i < length; i++) {
    if (max < arr[i]) max = arr[i];
  }
  return max;
}

int min(int *arr, int length) {
  int min = INT_MAX;
  for (int i = 0; i < length; i++) {
    if (min > arr[i] && arr[i] > 0) min = arr[i];
  }
  return min;
}