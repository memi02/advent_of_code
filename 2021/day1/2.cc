#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[]) {
  if (argc != 3) {
    cout << "Utilizzo ./day1.out <in> <out>" << endl;
    exit(0);
  }

  fstream in, out;
  in.open(argv[1], ios::in);
  if (in.fail()) {
    cerr << "Errore in apertura del file di input" << endl;
    exit(0);
  }
  out.open(argv[2], ios::out);
  if (out.fail()) {
    cerr << "Errore in apertura del file di output" << endl;
    exit(0);
  }

  int nInc = 0, nNInc = 0;
  int buffer;
  int arr[4] = {0, 0, 0, 0};
  in >> buffer;
  arr[0] = buffer;
  in >> buffer;
  arr[1] = buffer;
  arr[0] += buffer;
  in >> buffer;
  arr[2] = buffer;
  arr[1] += buffer;
  arr[0] += buffer;

  for (int i = 4; in >> buffer; i++) {
    arr[(i - 3) % 4] += buffer;
    arr[(i - 2) % 4] += buffer;
    arr[(i - 1) % 4] = buffer;
    if (arr[i % 4] < arr[(i - 3) % 4]) {
      out << arr[(i - 1) % 4] << " (increased)" << endl;
      ++nInc;
    } else {
      out << arr[(i - 1) % 4] << " (decreased or equal)" << endl;
      ++nNInc;
    }
  }
  cout << "la distanza è aumentata " << nInc << " volte" << endl;
  cout << "la distanza non è aumentata " << nNInc << " volte" << endl;
  return 0;
}
