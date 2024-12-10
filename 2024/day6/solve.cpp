#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

vector<vector<char>> createHash(string file, int N) {
  // Generate matrix to hold our map
  vector<vector<char>> matrix(N, vector<char>(N));

  // Load in file
  ifstream inFile(file);

  string contents((istreambuf_iterator<char>(inFile)),
                  istreambuf_iterator<char>());
  istringstream ss(contents);

  string line;
  int row = 0;

  while (getline(ss, line)) {
    vector<char> charVar(line.begin(), line.end());
    matrix[row] = charVar;
    row++;
  }
  return matrix;
}

pair<vector<int>, char> findPosition(vector<vector<char>> inMat) {
  // iter through and find match
  vector<int> a(2);
  for (int i = 0; i < inMat.size(); i++) {
    for (int j = 0; j < inMat.size(); j++) {
      char currentPos = inMat[i][j];
      if (currentPos == '^' || currentPos == '>' || currentPos == '<' ||
          currentPos == 'v') {
        a[0] = i;
        a[1] = j;
        return make_pair(a, currentPos);
      }
    }
  }
  // Off the map
  a[0] = -1;
  a[1] = -1;
  cout << "OFF THE MAP " << endl;
  return make_pair(a, '!');
}

bool objectInFront(char x) {
  if (x == '#') {
    // printf("Next Object is %c we need to turn", x);
    return true;
  }
  // printf("Next Object is %c, we will continue", x);
  return false;
}

bool checkInBounds(char pos, int row, int col, int limit) {
  if ((col >= limit && pos == '>') || (col <= -1 && pos == '<') ||
      (row >= limit && pos == 'v') || (row <= -1 && pos == '^')) {
    printf("GOING OUT OF BOUNDS: Current Position (%i, %i). Pos: %c\n", row,
           col, pos);
    return false;
  }
  printf("InBounds: Current Position (%i, %i). Pos: %c\n", row, col, pos);
  cout << "(col >= limit && pos == '>')" << (col >= limit && pos == '>')
       << endl;
  cout << "(col <= 0 && pos == '<')" << (col <= 0 && pos == '<') << endl;
  cout << "(row >= limit && pos == 'v')" << (row >= limit && pos == 'v')
       << endl;
  cout << "(row <= 0 && pos == '^')" << (row <= 0 && pos == '^') << endl;
  return true;
}
void printMat(vector<vector<char>> gameMap) {
  for (vector<char> r : gameMap) {
    for (char c : r) {
      cout << c << " ";
      ;
    }
    cout << endl;
  }
}

int countUniqueSteps(vector<vector<char>> inMap) {
  // Count the number of unique steps that guard takes
  int count = 0;
  for (vector<char> r : inMap) {
    for (char c : r) {
      if (c == '*') {
        count++;
      }
    }
  }
  return count;
}

char directionChange(char currentChar) {
  // Rotate our guard 90degrees, based on current pos
  map<char, char> charMap;
  charMap['>'] = 'v';
  charMap['^'] = '>';
  charMap['<'] = '^';
  charMap['v'] = '<';

  return charMap[currentChar];
}

int main() {
  // generate a hash
  int N = 130;
  // int N = 10;
  // vector<vector<char>> mat = createHash("./demo.txt", N);
  vector<vector<char>> mat = createHash("./input.txt", N);

  // printMat(mat);

  // Now lets find our position
  pair<vector<int>, char> pos = findPosition(mat);
  // This is for current storing and moving
  int row = pos.first[0];
  int col = pos.first[1];
  // This is for updating
  vector<int> prev(2);
  prev[0] = pos.first[0];
  prev[1] = pos.first[1];
  // Store checks
  bool front;
  bool inBound;
  int count = 0;
  // cout << row << " " << col << endl;

  inBound = checkInBounds(pos.second, row, col, N);
  // Check position and move
  while (inBound) {
    // Check direction and object infront
    printf("Current Pos: (%i, %i) and Position: %c\n", row, col, mat[row][col]);
    if (mat[row][col] == '>') {
      //  Upate next step
      col++;
    } else if (mat[row][col] == '<') {
      col--;
    } else if (mat[row][col] == '^') {
      row--;
    } else {
      row++;
    }
    // cout << row << " " << col << endl;
    // Check conditions
    inBound = checkInBounds(mat[prev[0]][prev[1]], row, col, N);
    if (!inBound) {
      break;
    }
    front = objectInFront(mat[row][col]);
    // Conditional checks
    if (!front) {
      inBound = checkInBounds(mat[prev[0]][prev[1]], row, col, N);
      if (!inBound) {
        break;
      }
      mat[row][col] = mat[prev[0]][prev[1]];
      mat[prev[0]][prev[1]] = '*';
      // After update Image
      cout << "---------- Step ----------" << endl;
      printMat(mat);
      cout << "  " << endl;
      // update prev
      prev[0] = row;
      prev[1] = col;
    } else if (front) {
      // Here I write the logic for turning
      mat[prev[0]][prev[1]] = directionChange(mat[prev[0]][prev[1]]);
      row = prev[0];
      col = prev[1];
      printMat(mat);
    }
  }
  printMat(mat);
  count = countUniqueSteps(mat) + 1;
  printf("Number of steps our Guard takes: %i\n", count);

  return 0;
}
