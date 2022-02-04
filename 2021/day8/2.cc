#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

int pow(int b, int e);
bool contains(char *container, int l_container, char *content, int l_content);

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

  char one[3];
  char four[5];
  char fourMinusOne[3];

  while (in >> buffer) {
    // cout << buffer << " ";
    if (c < 10) {
      if (strlen(buffer) == 2) {
        for (int i = 0; i < 2; i++) {
          one[i] = buffer[i];
        }
      } else if (strlen(buffer) == 4) {
        for (int i = 0; i < 4; i++) {
          four[i] = buffer[i];
        }
      }
    } else if (c == 10) {
      // cout << "One: " << one << endl;
      // cout << "Four: " << four << endl;

      {
        int k = 0;
        for (int i = 0; i < 4; i++) {
          bool found = false;
          for (int j = 0; j < 2; j++) {
            if (four[i] == one[j]) found = true;
          }
          if (!found) {
            fourMinusOne[k] = four[i];
            k++;
          }
        }
        fourMinusOne[2] = '\0';
      }
      // cout << "FourMinusOne: " << fourMinusOne << endl << endl;
    } else if (c > 10) {
      // cout << "Buffer: " << buffer << endl;
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
          // if it contains the one is
          if (contains(buffer, 7, four, 5)) {
            // 9
            sum += 9 * pow(10, 14 - c);
          } else if (contains(buffer, 7, fourMinusOne, 3)) {
            // 6
            sum += 6 * pow(10, 14 - c);
          }
          // 0
          // I don't need to do anything, because I would sum 0
        } break;
        // 2 3 5
        case 5: {
          if (contains(buffer, 6, one, 3)) {
            // 3
            sum += 3 * pow(10, 14 - c);
          } else if (contains(buffer, 8, fourMinusOne, 3)) {
            // 5
            sum += 5 * pow(10, 14 - c);
          } else {
            // 2
            sum += 2 * pow(10, 14 - c);
          }
        } break;
      }
      // cout << "Sum: " << sum << endl << endl;
      if (c == 14) {
        c = -1;
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

// bool contains(char *container, int l_container, char *content, int l_content)
// {
//   for (int i = 0; i < l_container - 1; i++) {
//     cout << "Evaluating container value: " << container[i] << endl;
//     bool found = false;
//     for (int j = 0; j < l_content - 1; j++) {
//       cout << "matching content: " << content[j] << endl;
//       if (container[i] == content[j]) found = true;
//     }
//     cout << "Found: " << ((found) ? "true" : "false") << endl;
//     if (!found) return false;
//   }
//   return true;
// }

bool contains(char *container, int l_container, char *content, int l_content) {
  for (int i = 0; i < l_content - 1; i++) {
    // cout << "To find: " << content[i] << endl;
    bool found = false;
    for (int j = 0; j < l_container - 1; j++) {
      // cout << "Searching: " << container[j] << endl;
      if (content[i] == container[j]) {
        found = true;
        break;
      }
    }
    // cout << "Found: " << ((found) ? "true" : "false") << endl;
    if (!found) return false;
  }
  return true;
}