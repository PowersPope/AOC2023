#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
// #include <vector>
#include <bits/stdc++.h>
using namespace std;

void printMatrix(vector<vector<int>> matrix) {
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < 2; j++) {
      cout << matrix[i][j] << " ";
    }
    cout << endl;
  }
}

void printVector(vector<int> vec) {
  for (int i = 0; i < vec.size(); i++) {
    cout << vec[i] << " ";
  }
  cout << endl;
}

vector<vector<int>> store(vector<vector<int>> inMat, string line1, int row) {

  // Match
  smatch sm;
  regex re("[0-9]+");
  int col = 0;

  while (regex_search(line1, sm, re)) {
    inMat[row][col] = stoi(sm.str());
    line1 = sm.suffix();
    col++;
  }
  return inMat;
}

vector<int> grabSequence(string inString) {
  // Match
  smatch sm;
  vector<int> vec;
  regex re("[0-9]+");

  while (regex_search(inString, sm, re)) {
    vec.push_back(stoi(sm.str()));
    inString = sm.suffix();
  }
  return vec;
}

bool checkBehind(int value, vector<int> listValues, int index) {
  // Check that value is not found in the indexes before index in listValues.
  for (int i = 0; i < index; i++) {
    if (listValues[i] == value) {
      // cout << "HIGHER VALUE: " << listValues[i] << " this value: " << value
      //      << " Position: " << index << endl;
      return false;
    }
  }
  return true;
}

bool listCheck(vector<vector<int>> mat, vector<int> vec) {
  // init variables
  bool flow = true;
  vector<int> keys;
  vector<int> values;

  // Build our single vectors to check
  for (int i = 0; i < mat.size(); i++) {
    keys.push_back(mat[i][0]);
    values.push_back(mat[i][1]);
  }
  printVector(vec);

  // Iter through the vec, {A, B, C, D}
  // Keep track of vec position. if vec[i] and i==0 then
  for (int v = 0; v < vec.size(); v++) {
    // Grab our vec value
    int vecVal = vec[v];

    // Iter through our keys and find our index values
    vector<int>::iterator iter = keys.begin();
    while ((iter = std::find_if(iter, keys.end(), [vecVal](int x) {
              return x == vecVal;
            })) != keys.end()) {
      // Grab the index position
      int idx = distance(keys.begin(), iter);
      if (v != 0) {

        bool check = checkBehind(values[idx], vec, v);
        if (check == false) {
          return false;
        }
      }
      // iter through the rest of the vector to find the next match
      iter++;
    }
  }
  return flow;
}

vector<int> reorderVector(int value, vector<int> vec, int idx) {
  // Now this is unordere we need to sort first
  // Check that value is not found in the indexes before index in listValues.
  for (int i = 0; i < idx; i++) {
    if (vec[i] == value) {
      // Swap the variables
      iter_swap(vec.begin() + i, vec.begin() + i + 1);
      i = 0;
    }
  }
  return vec;
}

pair<bool, vector<int>> listCheckPartB(vector<vector<int>> mat,
                                       vector<int> vec) {
  // init variables
  vector<int> keys;
  vector<int> values;
  bool reorder = false;

  // Build our single vectors to check
  for (int i = 0; i < mat.size(); i++) {
    keys.push_back(mat[i][0]);
    values.push_back(mat[i][1]);
  }

  // Iter through the vec, {A, B, C, D}
  // Keep track of vec position. if vec[i] and i==0 then
  for (int v = 0; v < vec.size(); v++) {
    // Grab our vec value
    int vecVal = vec[v];

    // Iter through our keys and find our index values
    vector<int>::iterator iter = keys.begin();
    while ((iter = std::find_if(iter, keys.end(), [vecVal](int x) {
              return x == vecVal;
            })) != keys.end()) {
      // Grab the index position
      int idx = distance(keys.begin(), iter);
      if (v != 0) {

        bool check = checkBehind(values[idx], vec, v);
        if (check == false) {
          // Add in the new funcitonality
          reorder = true;
          vec = reorderVector(values[idx], vec, v);
          v = 0;
        }
      }
      // iter through the rest of the vector to find the next match
      iter++;
    }
  }
  if (reorder) {
    return make_pair(true, vec);
  } else {
    return make_pair(false, vec);
  }
}

int checkMatch(vector<vector<int>> mat, vector<int> vec) {
  // init variables
  int midNum = 0;
  pair<bool, vector<int>> flowCheck;

  // Check our vec and if it works
  // flowCheck = listCheck(mat, vec); // This is part A
  flowCheck = listCheckPartB(mat, vec);

  if (flowCheck.first) {
    int idx = flowCheck.second.size() / 2;
    midNum = flowCheck.second[idx];
  }

  return midNum;
}

int main() {
  // ifstream file("./demo.txt");
  ifstream file("./input.txt");

  string contents((istreambuf_iterator<char>(file)),
                  istreambuf_iterator<char>());

  istringstream ss(contents);
  vector<vector<int>> mat(1176, vector<int>(2));
  vector<int> vecStream;

  string line;
  int row = 0;
  bool trip = false;
  int totalSum = 0;

  while (getline(ss, line)) {
    if (line == "" && trip == false) {
      trip = true;
    } else if (trip) {
      vecStream = grabSequence(line);
      totalSum += checkMatch(mat, vecStream);
    } else {
      mat = store(mat, line, row);
    }
    row++;
  }

  cout << "Final MidNum: " << totalSum << endl;

  return 0;
}
