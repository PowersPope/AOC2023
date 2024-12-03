#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
using namespace std;

int mul(int x, int y) { return x * y; }

int addValues(vector<string> matchVec) {
  int sumVal = 0;
  regex num("[0-9]+");
  smatch match;
  int val1;
  int val2;

  for (int i = 0; i < matchVec.size(); i += 2) {
    val1 = stoi(matchVec[i]);
    val2 = stoi(matchVec[i + 1]);
    sumVal += mul(val1, val2);
  }
  return sumVal;
}

int main() {
  // read in file and contents
  ifstream file("./input.txt");

  string contents((istreambuf_iterator<char>(file)),
                  istreambuf_iterator<char>());

  // Init variables used through file
  istringstream ss(contents);
  string line;
  int totalSum = 0;
  regex re("mul\\(([0-9]{1,3}),([0-9]{1,3})\\)|do\\(\\)|don't\\(\\)");
  smatch sm;
  vector<string> mulVec;
  string gate = "do()";

  // While:  that reads in our contents into lines and stores a regex match for
  // our line and stores it in a vector
  while (getline(ss, line)) {
    while (regex_search(line, sm, re)) {
      // Update gate if these show up
      if (sm.str() == "do()" || sm.str() == "don't()") {
        gate = sm.str();
        line = sm.suffix();
        continue;
      }

      if (gate != "don't()") {
        mulVec.push_back(sm[1]);
        mulVec.push_back(sm[2]);
        line = sm.suffix();
      } else {
        line = sm.suffix();
      }
    }
    // Print and check our output
    // cout << "Captured Output: ";
    // for (int i = 0; i < mulVec.size(); i++) {
    //   cout << mulVec[i] << " ";
    // }
    // cout << endl;
    totalSum = addValues(mulVec);
  }
  cout << "Total Output: " << totalSum << endl;
  // Function: that takes our vector outputs before and then performs
  // multiplication and adds them Output is returned and added to the total

  return 0;
}
