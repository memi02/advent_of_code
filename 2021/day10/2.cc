#include <fstream>
#include <iostream>

#include "stack.h"

using namespace std;

void swap(int& a, int& b);

int main(int argc, char const* argv[]) {
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

  char b[120];
  node* s = init();
  bool isCorrupted = false;

  const int maxPoint = 120;
  unsigned long int point[maxPoint];
  for (int i = 0; i < maxPoint; i++) point[i] = 0;
  int totPoint = 0;

  while (in >> b) {
    for (int i = 0; b[i] != '\0' && !isCorrupted; i++) {
      if (b[i] == '(' || b[i] == '[' || b[i] == '{' || b[i] == '<') {
        push(b[i], s);

      } else if (b[i] == ')') {
        if (top(s)->val != '(') {
          isCorrupted = true;
        } else
          pop(s);
      } else if (b[i] == ']') {
        if (top(s)->val != '[') {
          isCorrupted = true;
        } else
          pop(s);
      } else if (b[i] == '}') {
        if (top(s)->val != '{') {
          isCorrupted = true;
        } else
          pop(s);
      } else if (b[i] == '>') {
        if (top(s)->val != '<') {
          isCorrupted = true;
        } else
          pop(s);
      }
    }
    if (!isCorrupted) {
      unsigned long int tot = 0;
      while (!isEmpty(s)) {
        if (top(s)->val == '(')
          tot = (tot * 5) + 1;
        else if (top(s)->val == '[')
          tot = (tot * 5) + 2;
        else if (top(s)->val == '{')
          tot = (tot * 5) + 3;
        else if (top(s)->val == '<')
          tot = (tot * 5) + 4;
        pop(s);
      }
      for (int i = 0; i < totPoint + 1; i++) {
        if (tot > point[i]) {
          swap(tot, point[i]);
        }
      }
      totPoint++;
    }
    deinit(s);
    s = init();
    isCorrupted = false;
  }
  for (int i = 0; i < totPoint; i++) {
    cout << point[i] << endl;
  }
  cout << "Answer: " << point[totPoint / 2] << endl;
  in.close();
  return 0;
}

void swap(int& a, int& b) {
  int tmp = a;
  a = b;
  b = tmp;
}
