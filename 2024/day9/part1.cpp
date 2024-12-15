#include <bits/stdc++.h>
using namespace std;

int main() {
  // Load in input file
  ifstream inStream;
  // inStream.open("example.txt");
  inStream.open("input.txt");

  // Handle error when opening today's file
  if (!inStream.is_open()) {
    cout << "File is not opened correctly!" << endl;
    return 0;
  }

  string line;
  vector<int> memFix;
  int id = 0;

  // Grab our input
  while (getline(inStream, line)) {
    // cout << line << endl;
    // Read in the line (string of ints)
    for (int i = 0; i < line.size(); i++) {
      // Grab out our block and memory information
      if (i % 2 == 0) {
        int fileblock = stoi(line.substr(i, 1));
        vector<int> fileVec(fileblock, id);
        // Expand memFix size
        memFix.reserve(memFix.size() +
                       distance(fileVec.begin(), fileVec.end()));
        // Insert our new file blocks
        memFix.insert(memFix.end(), fileVec.begin(), fileVec.end());
        // Increment our id tracker
        id++;
      } else {
        int freespace = stoi(line.substr(i, 1));
        vector<int> freeVec(freespace, -1);
        memFix.reserve(memFix.size() +
                       distance(freeVec.begin(), freeVec.end()));
        // Insert our new file blocks
        memFix.insert(memFix.end(), freeVec.begin(), freeVec.end());
      }
    }
  }

  // Display the input
  // for (const auto c : memFix) {
  //   cout << c << " ";
  // }
  // cout << endl;
  unsigned long total = 0;

  // Now reformat in reverse
  for (int i = memFix.size() - 1; i >= 0; i--) {
    // If int != -1
    if (memFix[i] != -1) {
      for (int j = 0; j < memFix.size(); j++) {
        if (memFix[j] == -1 && j < i) {
          swap(memFix[i], memFix[j]);
          break;
        }
      }
    }
  }

  // for (const auto c : memFix) {
  //   cout << c << " ";
  // }
  // cout << endl;

  // Count the number of values
  for (int i = 0; i < memFix.size(); i++) {
    if (memFix[i] != -1) {
      unsigned long out = memFix[i] * i;
      total += out;
    }
  }

  cout << total << endl;

  return 0;
}
