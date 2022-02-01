#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

int pow(int b, int e);

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    cout << "Usage: " << argv[0] << endl;
    exit(0);
  }
  fstream in;
  in.open(argv[1], ios::in);
  if (in.fail()) {
    cout << "Error occourred while opening the input file..." << endl;
    exit(0);
  }
  char line[100];
  while (in.getline(line, 100)) {
    // I read all of the numbers

    // I convert all of the numbers, trying to understand their meaning
    // I translate the given sequence

    line[59];  // the position of the |
  }
  in.close();
}

int pow(int b, int e) {
  int r = 1;
  for (int i = 0; i < e; i++) {
    r *= b;
  }
  return r;
}