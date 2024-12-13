#include <bits/stdc++.h>
using namespace std;

// Allowed Math Operations
const vector<char> MAOP1 = {'*', '+', '|'};
const vector<unsigned long> key = {0, 1, 2};

// open our input and make the line to read in
// ifstream file("./example.txt");
ifstream file("./input.txt");
// ifstream file("./e1.txt");
string line;

unsigned long Compute(char c, unsigned long a, unsigned long b) {
  switch (c) {
  case '+':
    return a + b;
  case '*':
    return a * b;
  case '|':
    return stoul(to_string(a) + to_string(b));
  default:
    throw runtime_error("No such operator");
  }
}

vector<vector<unsigned long>> totalCombinations(size_t inputLength,
                                                size_t operatorLength) {
  // Calculate the number of opeations
  unsigned long N = inputLength - 1;
  unsigned long total = (unsigned long)pow(operatorLength, N);
  vector<vector<unsigned long>> result;
  result.reserve(total);

  for (int i = 0; i < total; i++) {
    int num = i;
    vector<unsigned long> combination(N, 0);

    for (int pos = N - 1; pos >= 0; pos--) {
      combination[pos] = num % 3;
      num /= 3;
    }
    result.push_back(combination);
  }
  return result;
}

unsigned long permute(string x, unsigned long y) {
  // Take total (y) and out values (x) and perform mutation
  vector<unsigned long> a;
  regex re("[0-9]+");
  smatch sm;

  // Search through our input x and find numbers add to our
  // vector a
  while (regex_search(x, sm, re)) {
    a.push_back(stoi(sm.str()));
    x = sm.suffix();
  }

  // running sum init
  unsigned long total = 0;

  // Calculate our possibilities
  vector<vector<unsigned long>> combinations =
      totalCombinations(a.size(), key.size());

  // Generate a value to iterator towards for our combinations
  unsigned long numOperations = (unsigned long)pow(key.size(), a.size() - 1);

  for (unsigned long op = 0; op < numOperations; op++) {
    vector<unsigned long> combo = combinations[op];
    for (unsigned long val = 0; val < a.size() - 1; val++) {
      // unsigned long initial;
      if (val == 0) {
        total = Compute(MAOP1[combo[val]], a[val], a[val + 1]);
        // Break if we are above y
        if (total > y) {
          break;
        }
      } else {
        total = Compute(MAOP1[combo[val]], total, a[val + 1]);
        // Break if we are above y
        if (total > y) {
          break;
        }
      }
    }
    if (total == y) {
      return total;
    }
    total = 0;
  }
  return 0;
}

int main() {
  unsigned long count = 0;

  if (file.is_open()) {

    while (getline(file, line)) {
      // Lets grab out delimiter between total and conditions
      size_t pos = line.find(':');
      unsigned long y = stoll(line.substr(0, pos));
      count += permute(line.substr(pos + 2, line.size()), y);
    }

    file.close();
  }
  printf("%lu\n\n", count);
  return 0;
}
