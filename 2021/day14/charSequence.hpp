#ifndef CHAR_SEQUENCE
#define CHAR_SEQUENCE

#include <iostream>

struct character {
  char c;
  character *next;
  character *prev;

 public:
  character(char in);
  ~character();
  void print();
};
class charSequence {
  character *first;
  character *last;

 public:
  charSequence();
  ~charSequence();
  void input(char in[]);
  void input(char in);
  void insertBetweenLetters(char **sequence, char toInsert[], int lenght);

  void print();
  int length();
  int *charachterFrequences();
};

#endif
