#include <string.h>

#include <fstream>
#include <iostream>

using namespace std;

int pow(int b, int e);
void print(bool **paper, int height, int width);

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

  const int MAXHEIGHT = 895;
  const int MAXWIDTH = 1311;
  bool **paper = new bool *[MAXWIDTH];
  for (int i = 0; i < MAXWIDTH; i++) paper[i] = new bool[MAXHEIGHT];

  int currentHeight = MAXHEIGHT, currentWidth = MAXWIDTH;
  char b[20];
  int x = 0;
  int y = 0;
  int maxX = 0, maxY = 0;
  bool isX = true;
  int counter = 0;
  while (in >> b) {
    // counter++;
    // cout << "no seg fault n." << counter << endl;
    // cout << "b: " << b << endl;
    if (b[0] == '*') {
      in >> b;
      in >> b;

    } else if (b[0] != 'f') {
      if (isX) {
        for (int i = 0; i < strlen(b); i++) {
          x += (b[i] - '0') * pow(10, strlen(b) - i - 1);
        }
        if (x > maxX) maxX = x;
        // cout << "read value (x): " << x << endl;
        isX = false;
      } else {
        for (int i = 0; i < strlen(b); i++) {
          y += (b[i] - '0') * pow(10, strlen(b) - i - 1);
        }
        if (y > maxY) maxY = y;
        // cout << "read value (y): " << y << endl;

        paper[x][y] = true;
        isX = true;
        x = 0;
        y = 0;
      }
    } else {
      // I position myself to have in b the data i need
      in >> b;
      in >> b;
      int foldPosition = 0;
      for (int i = 2; i < strlen(b); i++) {
        foldPosition += (b[i] - '0') * pow(10, strlen(b) - i - 1);
      }

      if (b[0] == 'x') {
        for (int j = 0; j < currentHeight; j++) {
          for (int i = 1;
               i < min(currentWidth - foldPosition + 1, foldPosition + 1);
               i++) {
            paper[foldPosition - i][j] =
                (paper[foldPosition - i][j] || paper[foldPosition + i][j]);
          }
        }
        currentWidth = currentWidth - (foldPosition + 1);
      } else {
        for (int i = 0; i < currentWidth; i++) {
          for (int j = 1;
               j < min(currentHeight - foldPosition + 1, foldPosition + 1);
               j++) {
            paper[i][foldPosition - j] =
                (paper[i][foldPosition - j] || paper[i][foldPosition + j]);
          }
        }
        currentHeight = currentHeight - (foldPosition + 1);
      }
      // print(paper, currentHeight, currentWidth);
    }
  }

  print(paper, currentHeight, currentWidth);

  for (int i = 0; i < MAXWIDTH; i++) delete[] paper[i];
  delete[] paper;
  in.close();
  return 0;
}

int pow(int b, int e) {
  int r = 1;
  for (int i = 0; i < e; i++) r *= b;
  return r;
}

void print(bool **paper, int height, int width) {
  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      cout << (paper[i][j] ? "#" : ".");
    }
    cout << endl;
  }
  cout << endl;
}
