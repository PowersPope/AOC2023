#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
using namespace std;

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

  // init the maps
  map<int, int> counts;
  vector<int> rightNum;

  while (getline(ss, line)) {
    int delimLocation = line.find(' ');
    // Grab out items and convert to ints
    int key1 = stoi(line.substr(0, delimLocation));
    int key2 = stoi(line.substr(delimLocation, line.size()));
    // Try to add in key1 if it isn't present if not then don't do anything
    counts.try_emplace(key1, 0);
    // Now for the right side if it is present then incremement. If it isn't
    // then don't.
    rightNum.push_back(key2);
  }

  for (int i = 0; i < rightNum.size(); i++) {
    if (counts.count(rightNum[i]) > 0) {
      counts[rightNum[i]]++;
    }
  }

  // LAST BIT IS TO iter through the map (key and value) pairs and to multiply
  // them together and add them to a sum. Then this is done!
  for (const auto &[key, value] : counts) {
    totalSum += key * value;
  }

  cout << totalSum << endl;

  return 0;
}
