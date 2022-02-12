#include <fstream>
#include <iostream>

#include "stack.h"

using namespace std;

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
  int tot = 0;
  while (in >> b) {
    for (int i = 0; b[i] != '\0' && !isCorrupted; i++) {
      if (b[i] == '(' || b[i] == '[' || b[i] == '{' || b[i] == '<') {
        push(b[i], s);

      } else if (b[i] == ')') {
        if (top(s)->val != '(') {
          tot += 3;
          isCorrupted = true;
        } else
          pop(s);
      } else if (b[i] == ']') {
        if (top(s)->val != '[') {
          tot += 57;
          isCorrupted = true;
        } else
          pop(s);
      } else if (b[i] == '}') {
        if (top(s)->val != '{') {
          tot += 1197;
          isCorrupted = true;
        } else
          pop(s);
      } else if (b[i] == '>') {
        if (top(s)->val != '<') {
          tot += 25137;
          isCorrupted = true;
        } else
          pop(s);
      }
    }
    deinit(s);
    s = init();
    isCorrupted = false;
  }

  cout << "Answer: " << tot << endl;
  in.close();
  return 0;
}
