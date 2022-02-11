#include <fstream>
#include <iostream>

using namespace std;

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

  // allocating the height map
  int xMax, yMax;
  cout << "Input height and width of the height map" << endl;
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

  // searching for low points
  int tot = 0;
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

      if (isMin) tot += heightmap[i][j] + 1;

      if (isMin) {
        cout << "i: " << i << ", j: " << j << endl;
        // cout << heightmap[i][j] << endl;
      }
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

  cout << "Answer: " << tot << endl;

  // rappresenting the heightmap
  // for (int j = 0; j < yMax; j++) {
  //   for (int i = 0; i < xMax; i++) {
  //     cout << heightmap[i][j];
  //   }
  //   cout << endl;
  // }
  // deallocating the height map
  for (int i = 0; i < xMax; i++) delete[] heightmap[i];
  delete[] heightmap;
  in.close();
  return 0;
}
