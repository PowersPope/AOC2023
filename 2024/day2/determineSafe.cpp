#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

using namespace std;

bool checkKeepIncreasing(vector<int> vec) {
  bool out = true;

  for (int i = 0; i < vec.size() - 1; i++) {
    if (vec[i + 1] < vec[i]) {
      out = false;
      break;
    }
  }
  return out;
}

bool checkKeepDecreasing(vector<int> vec) {
  bool out = true;

  for (int i = 0; i < vec.size() - 1; i++) {
    if (vec[i + 1] > vec[i]) {
      out = false;
      break;
    }
  }
  return out;
}

bool checkSafety(string seg) {
  // specify our out
  bool out = true;
  // setup regex expression
  regex re("[0-9]+");
  smatch sm;
  int previous = 0;
  int current = 0;
  int difference = 0;
  vector<int> storage;

  while (regex_search(seg, sm, re)) {
    // check to see if our numbers are increasing
    // decreasing or only jumping by 1, 2, 3.
    storage.push_back(stoi(sm.str()));
    seg = sm.suffix();
  }

  // Compute Increase or Decrease
  bool boolIncrease = checkKeepIncreasing(storage);
  bool boolDecrease = checkKeepDecreasing(storage);

  // Now chek for extra
  for (int i = 0; i < storage.size() - 1; i++) {
    // First check it is increasing
    if (storage[i] > storage[i + 1] && boolDecrease) {
      if (abs(storage[i] - storage[i + 1]) >= 4) {
        out = false;
        break;
      }
    } else if (storage[i] < storage[i + 1] && boolIncrease) {
      if (abs(storage[i] - storage[i + 1]) >= 4) {
        out = false;
        break;
      }
    } else {
      out = false;
      break;
    }
  }
  return out;
}

int main(void) {
  // We need to read in the file
  ifstream file("./input.txt");

  // Read through the lines
  string contents((istreambuf_iterator<char>(file)),
                  istreambuf_iterator<char>());

  // Make a stream string object
  istringstream ss(contents);

  // init variables
  int totalSum = 0;
  string line;
  bool safe;

  while (getline(ss, line)) {
    safe = checkSafety(line);
    if (safe == true) {
      totalSum += 1;
    }
  }

  cout << totalSum << endl;

  return 0;
}
