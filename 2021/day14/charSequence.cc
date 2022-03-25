#include "charSequence.h"

character::character(char in) {
  c = in;
  next = NULL;
  prev = NULL;
}

character::~character() {}

void character::print() { std::cout << c; }

charSequence::charSequence() {
  first = NULL;
  last = NULL;
}
charSequence::~charSequence() {
  character *tmp = first;
  while (tmp->next != NULL) {
    tmp = tmp->next;
    delete tmp->prev;
  }
  delete tmp;
}

void charSequence::input(char in[]) {
  for (int i = 0; in[i] != '\0'; i++) {
    input(in[i]);
  }
}

void charSequence::input(char in) {
  character *tmp = new character(in);
  tmp->prev = NULL;
  tmp->next = last;

  if (first == NULL) first = tmp;
  last = tmp;
}

void charSequence::insertBetweenLetters(char **in, char toInsert[], int lenght) {
  for (character *s = first; s->next != NULL; s = s->next) {
    // std::cout << "Analizing character:  " << s->c << " and " << s->next->c << std::endl;
    bool exitLoop = false;
    for (int i = 0; i < lenght && !exitLoop; i++) {
      // std::cout << "Searching for sequence: " << in[i] << std::endl;
      if (s->c == in[i][0] && s->next->c == in[i][1]) {
        // std::cout << "Sequence found, inserting letter " << toInsert[i] << std::endl;
        character *tmp = new character(toInsert[i]);
        tmp->next = s->next;
        tmp->prev = s;

        tmp->next->prev = tmp;
        tmp->prev->next = tmp;

        s = tmp;  // this way I avoid trying to reinsert a letter using this one (I can do it because it's garanteed that I have a
        // letter after this one)
        exitLoop = true;  // When I find one match, I know I can exit, because there won't be other ones
      }
    }
  }
}

void charSequence::print() {
  character *tmp = first;
  while (tmp != NULL) {
    tmp->print();
    tmp = tmp->next;
  }
  std::cout << std::endl;
}

int charSequence::length() {
  int c = 0;
  character *tmp = first;
  while (tmp != NULL) {
    c++;
    tmp = tmp->next;
  }
  return c;
}

int *charSequence::charachterFrequences() {
  int *out = new int[26];
  for (int i = 0; i < 26; i++) out[i] = 0;

  character *tmp = first;
  while (tmp != NULL) {
    out[tmp->c - 'A']++;

    tmp = tmp->next;
  }

  return out;
}