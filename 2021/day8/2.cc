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
    cout << "Failed to open the input file" << endl;
    exit(0);
  }

  char buffer[8];
  int c = 0;

  long int sum = 0;

  char translator[7];  // in 0 there's the translation of a, in 1 of b ...
  int count[7] = {0};
  int one[2];
  int four[4];

  while (in >> buffer) {
    // cout << buffer << " ";
    if (c < 10) {
      if (strlen(buffer) == 2) {
        for (int i = 0; i < 2; i++) {
          one[i] = buffer[i] - 'a';
        }
      } else if (strlen(buffer) == 4) {
        for (int i = 0; i < 4; i++) {
          four[i] = buffer[i] - 'a';
        }
      }
      for (int i = 0; i < strlen(buffer); i++) {
        count[buffer[i] - 'a']++;
      }
    } else if (c == 10) {
      // in base al numero di volte che ogni lettera compare sono in grado di
      // definire quale dei segmenti rappresenta
      for (int i = 0; i < 7; i++) {
        switch (count[i]) {
          case 4:
            translator[4] = i + 'a';
            break;
          case 6:
            translator[1] = i + 'a';
            break;
          case 8:
            bool f = false;
            for (int j = 0; j < 2; j++)
              if (i == one[j]) f = true;
            if (f) translator[2] = i + 'a';
            break;
        }
      }
    } else if (c > 10) {
      // cout << "Strlen: " << strlen(buffer) << endl;
      switch (strlen(buffer)) {
          // 1
        case 2:
          sum += 1 * pow(10, 14 - c);
          break;
        // 4
        case 4:
          sum += 4 * pow(10, 14 - c);
          break;
        // 7
        case 3:
          sum += 7 * pow(10, 14 - c);
          break;
        // 8
        case 7:
          sum += 8 * pow(10, 14 - c);
          break;
        // 0 6 9
        case 6: {
          bool isE = false, isC = false;
          for (int i = 0; i < 7; i++) {
            if (buffer[i] == translator[4]) isE = true;
            if (buffer[i] == translator[2]) isC = true;
          }
          // 6
          if (!isC) sum += 6 * pow(10, 14 - c);
          // 9
          if (!isE) sum += 9 * pow(10, 14 - c);
          // nel caso dello 0 non dovrei sommare nulla
        } break;
        // 2 3 5
        case 5: {
          bool isE = false, isB = false;
          for (int i = 0; i < 7; i++) {
            if (buffer[i] == translator[4]) isE = true;
            if (buffer[i] == translator[1]) isB = true;
          }
          // 2
          if (isE) sum += 2 * pow(10, 14 - c);
          // 3
          if (!isB && !isE) sum += 3 * pow(10, 14 - c);
          // 5
          if (isB) sum += 5 * pow(10, 14 - c);
        } break;
      }
      // cout << "Sum: " << sum << endl;
      if (c == 14) {
        c = -1;
        for (int i = 0; i < 7; i++) {
          count[i] = 0;
        }
      };
    }
    c++;
  }
  cout << "Result: " << sum << endl;
}

int pow(int b, int e) {
  int r = 1;
  for (int i = 0; i < e; i++) {
    r *= b;
  }
  return r;
}