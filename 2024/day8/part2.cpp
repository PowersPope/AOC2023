#include <bits/stdc++.h>
using namespace std;

struct Node {
  // Construct to store node locations (x,y)
  int x, y;
  char node;
  // They are sorted in order of lowest to highest node location order
  bool operator<(const Node &other) const {
    return tie(x, y, node) < tie(other.x, other.y, other.node);
  }
};

bool checkInBounds(int ny, int nx, int rowN, int colN) {
  return (nx <= colN && ny >= 0 && ny < rowN && nx >= 0);
}

int main() {
  ifstream inStream;
  // inStream.open("example2.txt");
  // inStream.open("example.txt");
  inStream.open("input.txt");

  if (!inStream.is_open()) {
    // Make sure our file is open and we can load our data in
    cout << "File did not open" << endl;
    return 0;
  }

  // Init our variables
  string line;
  int row = 0;
  set<Node> Nodes;
  int colLength;

  // This is for visualziation for debugging
  vector<vector<char>> mat;

  // Load our file into a matrix (unconfirmed size)
  while (getline(inStream, line)) {
    vector<char> linerow;
    for (int col = 0; col < line.size(); col++) {
      // Grab out the unique character
      char x = line[col];
      linerow.push_back(x);
      // If it isn't just a placeholder then move on
      if (x != '.') {
        Nodes.insert({col, row, x});
      }
      colLength = col;
    }
    // Update our row for (y)
    mat.push_back(linerow);
    row++;
  }

  map<string, int> uniqueNum;
  int count = 0;

  for (const auto &n1 : Nodes) {
    for (const auto &n2 : Nodes) {
      if (n1.node == n2.node && n1.x != n2.x && n1.y != n2.y) {
        // printf("NODE 1: %c, x: %i, y: %i\n", n1.node, n1.x, n1.y);
        // printf("NODE 2: %c, x: %i, y: %i\n", n2.node, n2.x, n2.y);
        // Calculate the difference
        int dx = n1.x - n2.x;
        int dy = n1.y - n2.y;
        // printf("dx: %i, dy: %i\n", dx, dy);

        // See if adding to the upper number would be better or worse
        if (n1.y > n2.y) {
          // Add the node towers which are anti nodes now
          string upString = to_string(n1.y) + "-" + to_string(n1.x);
          string downString = to_string(n2.y) + "-" + to_string(n2.x);
          uniqueNum.try_emplace(upString, 0);
          uniqueNum.try_emplace(downString, 0);
          if (uniqueNum[upString] == 0) {
            uniqueNum[upString]++;
            count++;
          }
          if (uniqueNum[downString] == 0) {
            uniqueNum[downString]++;
            count++;
          }
          // Now perform regular logic
          bool upCheck = true;
          bool bottomCheck = true;
          int scale = 1;
          while (upCheck) {
            int dyny = (scale * dy) + n1.y;
            int dxnx = (scale * dx) + n1.x;
            upCheck = checkInBounds(dyny, dxnx, row, colLength);
            // cout << "UP CHECK: " << upCheck << endl;
            // printf("dyny: %i, dxnx: %i\n", dyny, dxnx);
            string upString = to_string(dyny) + "-" + to_string(dxnx);
            uniqueNum.try_emplace(upString, 0);
            // If things are true then add them
            if (upCheck && uniqueNum[upString] == 0) {
              // Add in check
              mat[dyny][dxnx] = '#';
              uniqueNum[upString]++;
              count++;
              // cout << "---------UPPER-----------------" << endl;
              // for (const auto r : mat) {
              //   for (const auto c : r) {
              //     cout << c << " ";
              //   }
              //   cout << endl;
              // }
              // cout << "-----------------" << endl;
            }
            scale++;
          }
          scale = 1;
          while (bottomCheck) {
            int dyny2 = n2.y - (scale * dy);
            int dxnx2 = n2.x - (scale * dx);
            bottomCheck = checkInBounds(dyny2, dxnx2, row, colLength);
            string downString = to_string(dyny2) + "-" + to_string(dxnx2);
            uniqueNum.try_emplace(downString, 0);
            // cout << "Bottom CHECK: " << bottomCheck << endl;
            // printf("dyny2: %i, dxnx2: %i\n", dyny2, dxnx2);
            if (bottomCheck && uniqueNum[downString] == 0) {
              // Add in check
              mat[dyny2][dxnx2] = '#';
              uniqueNum[downString]++;
              count++;
              // cout << "---------BOTTOM-----------------" << endl;
              // for (const auto r : mat) {
              //   for (const auto c : r) {
              //     cout << c << " ";
              //   }
              //   cout << endl;
              // }
              // cout << "-----------------" << endl;
            }
            scale++;
          }
        }
        // cout << "-----------------" << endl;
        // for (const auto r : mat) {
        //   for (const auto c : r) {
        //     cout << c << " ";
        //   }
        //   cout << endl;
        // }
        // cout << "-----------------" << endl;
      }
    }
  }

  for (const auto r : mat) {
    for (const auto c : r) {
      cout << c << " ";
    }
    cout << endl;
  }

  // for (const auto &p : upperLetterNode) {
  //   printf("X: %i, Y: %i, UpperLetter: %c\n", p.x, p.y, p.node);
  // }
  cout << count << endl;

  return 0;
}
