#include <fstream>
#include <iostream>
#include <regex>
#include <vector>
using namespace std;

void print_vec(vector<int> inVec) {
  cout << "Print Vector: ";
  for (int i = 0; i < inVec.size(); i++) {
    cout << inVec[i] << " ";
  }
  cout << endl;
}

pair<bool, int> safe(vector<int> checkVec) {
  bool safeVec = true;
  bool increase;
  bool decrease;
  int pos = 0;

  if (checkVec[1] > checkVec[0]) {
    increase = true;
    decrease = false;
  } else {
    decrease = true;
    increase = false;
  }

  for (int i = 0; i < checkVec.size() - 1; i++) {
    // If it is the first case then check if it is increasing or decreasing for
    // later checks

    // Check that it is increasing and not too large of a jump
    if (checkVec[i + 1] > checkVec[i] &&
        abs(checkVec[i + 1] - checkVec[i]) < 4 && increase) {
      // cout << "Increasing ";
      // cout << "Pos " << i << " (" << checkVec[i] << ", " << checkVec[i + 1]
      //      << ")" << endl;
      continue;
      // Check that is is decreasing and not too large of a jump
    } else if (checkVec[i + 1] < checkVec[i] &&
               abs(checkVec[i + 1] - checkVec[i]) < 4 && decrease) {
      // cout << "Decreasing ";
      // cout << "Pos " << i << " (" << checkVec[i] << ", " << checkVec[i + 1]
      //      << ")" << endl;
      continue;
      // This does not meet increasing or distance check
    } else {
      safeVec = false;
      pos = i;
      break;
    }
  }
  return make_pair(safeVec, pos);
}

bool permutationCheck(vector<int> vecInput, int pos) {
  // Here we take in our pos and check pos-1, pos, pos+1
  // if all are good then we pass
  bool isSafe = false;

  for (int i = pos - 1; i < pos + 2; i++) {
    // Generate our copy
    vector<int> tmpVec(vecInput);
    // Erase the particular position we want to try without
    if (i == -1 || i == vecInput.size()) {
      continue;
    }
    tmpVec.erase(tmpVec.begin() + i);

    // Store our output and check if this vector is safe
    pair<bool, int> vecTest = safe(tmpVec);
    tmpVec.clear();
    if (vecTest.first == true) {
      isSafe = true;
      break;
    }
    // Clear the vector
  }
  return isSafe;
}

int main() {
  // Load in file and contents into a string
  // ifstream file("./edgecase.txt");
  ifstream file("./input.txt");
  string contents((istreambuf_iterator<char>(file)),
                  istreambuf_iterator<char>());

  // Init our value holders
  stringstream ss(contents);
  int totalSum = 0;
  regex re("[0-9]+");
  smatch sm;
  string line;
  vector<int> lineVec;
  pair<bool, int> firstCheck;
  bool safeOut;

  // Iter through our ss object into our line string object
  while (getline(ss, line)) {
    // Grab our captured numbers into a vector
    while (regex_search(line, sm, re)) {
      lineVec.push_back(stoi(sm.str()));
      line = sm.suffix();
    }
    firstCheck = safe(lineVec);
    safeOut = firstCheck.first;

    if (safeOut == false) {
      safeOut = permutationCheck(lineVec, firstCheck.second);
    }

    if (safeOut) {
      totalSum++;
    }
    lineVec.clear();
  }

  // Final out
  cout << totalSum << endl;

  return 0;
}
