#include <fstream>
#include <iostream>

// #include "queue.h"

using namespace std;

enum side { Up, Down, Left, Right };

int basin_size(int x, int y, const int xMax, const int yMax, int **heightmap);

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << "<input_file>" << endl;
    exit(0);
  }
  fstream in;
  in.open(argv[1], ios::in);
  if (in.fail()) {
    std::cerr << "Error opening input file" << endl;
    exit(0);
  }

  // allocating the height map
  int xMax, yMax;
  std::cout << "Input height and width of the height map" << endl;
  cin >> xMax >> yMax;
  int **heightmap = new int *[xMax];
  for (int i = 0; i < xMax; i++) heightmap[i] = new int[yMax];

  // reading the input
  {
    char buffer;
    int i = 0, j = 0;
    while (in.get(buffer)) {
      if (buffer == '\n') {
        j++;
        i = 0;
      } else {
        heightmap[i][j] = buffer - '0';
        i++;
      }
    }
  }

  // I will start searching for low points and using -2 to identify them

  for (int j = 0; j < yMax; j++) {
    for (int i = 0; i < xMax; i++) {
      bool isMin = true;
      if (i != 0)
        if (heightmap[i - 1][j] <= heightmap[i][j]) isMin = false;
      if (i != xMax - 1)
        if (heightmap[i + 1][j] <= heightmap[i][j]) isMin = false;
      if (j != 0)
        if (heightmap[i][j - 1] <= heightmap[i][j]) isMin = false;
      if (j != yMax - 1)
        if (heightmap[i][j + 1] <= heightmap[i][j]) isMin = false;

      if (isMin) {
        heightmap[i][j] = -2;
      }

      // if (isMin) {
      //   std::cout << "i: " << i << ", j: " << j << endl;
      //   // cout << heightmap[i][j] << endl;
      // }
      // if (isMin) {
      //   cout << heightmap[i][j] << " : ";
      //   if (i != 0) cout << heightmap[i - 1][j];
      //   if (i != xMax - 1) cout << heightmap[i + 1][j];
      //   if (j != 0) cout << heightmap[i][j - 1];
      //   if (j != yMax - 1) cout << heightmap[i][j + 1];
      //   cout << endl;
      // }
    }
  }

  // cycling over the map and calculating basin dimension starting from the low
  // point
  int top3[3];
  for (int i = 0; i < 3; i++) top3[i] = 0;
  for (int j = 0; j < yMax; j++) {
    for (int i = 0; i < xMax; i++) {
      if (heightmap[i][j] == -2) {
        // whenever i find a low i calculate the size of his basin
        int tmp = basin_size(i, j, xMax, yMax, heightmap);
        // and try to put the size in a top 3
        for (int k = 0; k < 3; k++) {
          if (tmp > top3[k]) {
            int t = top3[k];
            top3[k] = tmp;
            tmp = t;
          }
        }
      }
    }
  }

  int tot = 1;
  for (int i = 0; i < 3; i++) {
    cout << "top3[" << i << "]: " << top3[i] << endl;
    tot *= top3[i];
  }

  cout << "Answer: " << tot << endl;

  // rappresenting the heightmap
  // for (int j = 0; j < yMax; j++) {
  //   for (int i = 0; i < xMax; i++) {
  //     if (heightmap[i][j] == -1)
  //       cout << "B";
  //     else
  //       cout << heightmap[i][j];
  //   }
  //   cout << endl;
  // }

  // deallocating the height map
  for (int i = 0; i < xMax; i++) delete[] heightmap[i];
  delete[] heightmap;
  in.close();
  return 0;
}

int basin_size(int x, int y, const int xMax, const int yMax, int **heightmap) {
  // exit conditions (if i find a barrier (9) or a already evaluated number
  // (-1))
  if (heightmap[x][y] == 9 || heightmap[x][y] == -1) return 0;
  heightmap[x][y] = -1;

  int tot = 0;

  if (x != 0) tot += basin_size(x - 1, y, xMax, yMax, heightmap);
  if (x != xMax - 1) tot += basin_size(x + 1, y, xMax, yMax, heightmap);
  if (y != 0) tot += basin_size(x, y - 1, xMax, yMax, heightmap);
  if (y != yMax - 1) tot += basin_size(x, y + 1, xMax, yMax, heightmap);

  return tot + 1;
}
