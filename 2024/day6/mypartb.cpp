#include <bits/stdc++.h>
using namespace std;

void printVec(vector<string> s) {
  for (string c : s) {
    cout << c << endl;
  }
}
struct State {
  // Construct a state object to hold our variables
  int x, y, dir;
  bool operator<(const State &other) const {
    return tie(x, y, dir) < tie(other.x, other.y, other.dir);
  }
};

// Directions to change:
// 0 = up
// 1 = right
// 2 = down
// 3 = left
static const int DX[4] = {0, 1, 0, -1};
static const int DY[4] = {-1, 0, 1, 0};

bool isValid(int x, int y, const vector<string> &grid) {
  // Check to make sure that we are not going out of the limits of our system.
  // Also, that we are passing through any sort of blockage
  // return (y >= 0 && y < (int)grid.size() && x >= 0 && (int)grid[0].size() &&
  //         grid[y][x] != '#');
  return (y < 0 || y >= grid.size() || x < 0 || x >= grid[0].size());
}

tuple<set<State>, bool> causesLoop(int startX, int startY, vector<string> &grid,
                                   bool orig) {
  // const vector<string> &grid, bool orig) {
  bool loop = true, turn = false;
  int x = startX, y = startY, dir = 0;
  set<State> visited;
  static const char pos[4] = {'^', '>', 'v', '<'};

  while (loop) {
    State current = {x, y, dir};
    if (visited.count(current) && !orig) {
      // cout << "THIS ITERATION IS TRUE (Blocakge Found)" << endl;
      // cout << "------------------------------" << endl;
      // printVec(grid);
      // cout << "------------------------------" << endl;
      // for (const auto &p : visited) {
      //   printf("X: %i, Y: %i, Direciton: %i\n", p.x, p.y, p.dir);
      // }
      return make_tuple(visited, true);
    }
    if (!turn) {
      visited.insert(current);
    }

    // We increment upwards in the dir direction
    int nx = x + DX[dir], ny = y + DY[dir];
    // cout << nx << " " << ny << endl;
    // If our movement is not valid then we change direction
    // if (!isValid(nx, ny, grid)) { //&& (grid[y][x] != '#'))
    if (isValid(nx, ny, grid)) {
      loop = false;
    } else if (grid[ny][nx] == '#') {
      // cout << "Change Dir" << endl;
      dir = (dir + 1) % 4;
      grid[y][x] = pos[dir];
      turn = true;
      // cout << "&&&&&&&&&&&&&&" << endl;
      // printVec(grid);
      // cout << "&&&&&&&&&&&&&&" << endl;
    } else {
      // if (orig) {
      grid[ny][nx] = pos[dir];
      grid[y][x] = 'X';
      // }
      x = nx;
      y = ny;
      turn = false;
      // cout << "$$$$$$$$$$$$$$" << endl;
      // printVec(grid);
      // cout << "$$$$$$$$$$$$$$" << endl;
    }
  }
  // if (orig) {
  //   for (const auto &p : visited) {
  //     printf("X: %i, Y: %i, Direciton: %i\n", p.x, p.y, p.dir);
  //   }
  // }
  // printVec(grid);
  // cout << ' ' << endl;
  return make_tuple(visited, false);
}

map<string, int> uniqueLine;

int main() {
  vector<string> grid;
  vector<string> origGrid;
  // ifstream file("demo.txt");
  // ifstream file("input.txt");
  // ifstream file("extra1.txt");
  // ifstream file("extra2.txt");
  ifstream file("extraN.txt");
  // ifstream file("extra3.txt");
  string contents((istreambuf_iterator<char>(file)),
                  istreambuf_iterator<char>());
  istringstream ss(contents);
  string line;

  while (getline(ss, line)) {
    // cout << line << endl;
    grid.push_back(line);
  }

  origGrid = grid;

  // int startX = 96, startY = 41;
  // int startX = 1, startY = 4;
  int startX = 2, startY = 4;
  // int startX = 4, startY = 6;
  // int startX = 1, startY = 13;

  set<State> origPath;
  set<State> newPath;
  bool loopFound;
  tie(origPath, loopFound) = causesLoop(startX, startY, grid, true);

  // printVec(grid);

  grid = origGrid;

  int count = 0;
  for (const auto &p : origPath) {
    // Place a zero here if it isn't present
    // printf("X: %i, Y: %i, grid item: %c\n", p.x, p.y, grid[p.y][p.x]);
    if (grid[p.y][p.x] == '.') {
      char original = grid[p.y][p.x];
      // grid[p.y][p.x] = 'O'; // Place obstruction
      // cout << "XXXXXXXXXXXXXXXXXXXXXX" << endl;
      // printVec(grid);
      // cout << "XXXXXXXXXXXXXXXXXXXXXX" << endl;
      grid[p.y][p.x] = '#'; // Place obstruction
      string unique = to_string(p.y) + "-" + to_string(p.x);
      uniqueLine.try_emplace(unique, 0);
      if (uniqueLine[unique] == 0) {
        // printf("GOT IN (%i, %i)\n", p.x, p.y);
        tie(newPath, loopFound) = causesLoop(startX, startY, grid, false);
        if (loopFound) {
          // string unique = to_string(p.y) + to_string(p.x);
          // uniqueLine.try_emplace(unique, 0);
          // printf("Loop Found: (%i, %i) Map: %i\n", p.x, p.y,
          // uniqueLine[unique]);
          // if (uniqueLine[unique] == 0) {
          // printf("Coords (%i, %i)\n", p.x, p.y);
          // printVec(grid);
          // cout << "-------------------" << endl;
          count++;
          uniqueLine[unique]++;
        }
        // } else {
        //   cout << "DOUBLE COUNT VALUE" << endl;
        //   printf("Coords (%i, %i)\n", p.x, p.y);
        //   printVec(grid);
        //   cout << "-------------------" << endl;
        //   uniqueLine[p.y + p.x]++;
        // }
      }
      // grid[p.y][p.x] = original; // Remove obstruction
      // cout << "*******************" << endl;
      // printVec(grid);
      // cout << "*******************" << endl;
      grid = origGrid;
    }
  }

  // printVec(grid);
  cout << count << endl;
  return 0;
}
