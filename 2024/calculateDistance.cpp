#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

int distance(vector<int> vec1, vector<int> vec2) {
  // Compute the distance total
  int total = 0;

  for (int i = 0; i < vec1.size(); i++) {
    total += abs(vec1[i] - vec2[i]);
  }

  return total;
}

// Make our main funciton
int main(void) {
  // First we need to load in our dataset
  // ifstream file("./demo.txt");
  ifstream file("./realInput.txt");

  // extract the contents
  string contents((istreambuf_iterator<char>(file)),
                  istreambuf_iterator<char>());
  istringstream ss(contents);
  string line;
  int totalSum = 0;
  vector<int> leftNum;
  vector<int> rightNum;

  while (getline(ss, line)) {
    int delimLocation = line.find(' ');
    // Grab out items and convert to ints
    leftNum.push_back(stoi(line.substr(0, delimLocation)));
    rightNum.push_back(stoi(line.substr(delimLocation, line.size())));
  }
  // Sort our list of numbers
  sort(leftNum.begin(), leftNum.end());
  sort(rightNum.begin(), rightNum.end());

  // Compute our distance
  totalSum = distance(leftNum, rightNum);

  cout << totalSum << endl;

  return 0;
}
