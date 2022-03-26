#include <limits.h>
#include <string.h>

#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

unsigned long long int max(unsigned long long int *arr, int length);
unsigned long long int min(unsigned long long int *arr, int length);

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

  char base[25];
  in >> base;

  const int NUM_COUPLES = 101;
  char toFind[NUM_COUPLES][3];
  char toInput[NUM_COUPLES];
  unsigned long long int numFound[NUM_COUPLES];

  for (int i = 0; i < NUM_COUPLES; i++) {
    toFind[i][0] = toFind[i][1] = toFind[i][2] = toInput[i] = '\0';
    numFound[i] = 0;
  }

  unsigned long long int numLetter[26];
  for (int i = 0; i < 26; i++) numLetter[i] = 0;

  char b[3];

  for (int i = 0; in >> b; i++) {
    strcpy(toFind[i], b);

    in >> b;  // I don't need to save the ->
    in >> b;

    toInput[i] = b[0];
  }

  // I look to find all the couples of letters already existing
  for (int i = 0; base[i + 1] != '\0'; i++) {
    for (int j = 0; toFind[j][0] != '\0'; j++) {
      if (base[i] == toFind[j][0] && base[i + 1] == toFind[j][1]) {
        numFound[j]++;
      }
    }
  }

  // I save the number of the letter already existing
  for (int i = 0; base[i] != '\0'; i++) {
    numLetter[base[i] - 'A']++;
  }
  /*   for (int i = 0; toFind[i][0] != '\0'; i++) {
      cout << toFind[i] << " -> " << toInput[i] << " [" << numFound[i] << "]" << endl;
    } */

  // for (int i = 0; i < 26; i++) cout << char('A' + i) << ": " << numLetter[i] << endl;

  for (int c = 0; c < 40; c++) {
    unsigned long long int numFound_tmp[NUM_COUPLES];
    for (int i = 0; i < NUM_COUPLES; i++) numFound_tmp[i] = 0;
    for (int i = 0; toFind[i][0] != '\0'; i++) {
      // I increase the number of letters found
      numLetter[toInput[i] - 'A'] += numFound[i];
      // cout << "Adding to the count of " << char(toInput[i]) << " " << numFound[i] << " from " << toFind[i] << endl;

      // And I count the new couples that are created
      for (int j = 0; toFind[j][0] != '\0'; j++) {
        if (toFind[i][0] == toFind[j][0] && toInput[i] == toFind[j][1]) {
          numFound_tmp[j] += numFound[i];
          // cout << "Match between " << toFind[i][0] << toInput[i] << " and " << toFind[j][0] << toFind[j][1] << endl;
        }
        if (toInput[i] == toFind[j][0] && toFind[i][1] == toFind[j][1]) {
          numFound_tmp[j] += numFound[i];
          // cout << "Match between " << toInput[i] << toFind[i][1] << " and " << toFind[j][0] << toFind[j][1] << endl;
        }
      }
    }

    // I reset the number of found, because all the one that were couples can't be anymore
    for (int i = 0; i < NUM_COUPLES; i++) numFound[i] = numFound_tmp[i];
    cout << endl << "cycle num. " << c << endl;
    /* for (int i = 0; toFind[i][0] != '\0'; i++) {
      cout << toFind[i] << " -> " << toInput[i] << " [" << numFound[i] << "]" << endl;
    }*/
    for (int i = 0; i < 26; i++)
      if (numLetter[i] != 0) cout << char('A' + i) << ": " << numLetter[i] << endl;
  }

  // for (int i = 0; i < 26; i++) cout << char('A' + i) << ": " << numLetter[i] << endl;
  cout << "min: " << min(numLetter, 26) << ", max: " << max(numLetter, 26) << endl;
  cout << "Answer: " << max(numLetter, 26) - min(numLetter, 26) << endl;
}

unsigned long long int max(unsigned long long int *arr, int length) {
  unsigned long long int max = 0;
  for (int i = 0; i < length; i++) {
    if (max < arr[i]) max = arr[i];
  }
  return max;
}

unsigned long long int min(unsigned long long int *arr, int length) {
  unsigned long long int min = ULONG_MAX;
  for (int i = 0; i < length; i++) {
    if (min > arr[i] && arr[i] > 0) min = arr[i];
  }
  return min;
}