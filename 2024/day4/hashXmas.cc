#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<char>> storeFile(string filename, const int rowLength,
                               const int colLength) {
  ifstream inFile(filename);

  // Generate our matrix
  vector<vector<char>> matrix(rowLength, vector<char>(colLength));

  // Variables
  string line;
  int row = 0;

  // iter through line
  while (getline(inFile, line) && row < rowLength) {
    for (int col = 0; col < colLength && col < line.length(); col++) {
      matrix[row][col] = line[col];
    }
    row++;
  }

  // Close our file
  inFile.close();

  return matrix;
}

vector<vector<char>> sliceMatrix(vector<vector<char>> matrix, int Rbegin,
                                 int Cbegin) {
  // Slice our matrix

  vector<vector<char>> slicedMatrix;

  for (int i = 0; i < 3; i++) {
    vector<char> row;
    for (int j = 0; j < 3; ++j) {
      row.push_back(matrix[Rbegin + i][Cbegin + j]);
    }
    slicedMatrix.push_back(row);
  }
  return slicedMatrix;
}

int calculateMas(vector<vector<char>> matrix, int rowN, int colN) {
  // Now we are going to iter through each 1234 rows and 1234 cols. In a square
  // search manner
  int matches = 0;
  bool rightSide = 0;
  bool leftSide = 0;
  vector<char> xmas = {'M', 'A', 'S'};
  vector<char> rxmas = {'S', 'A', 'M'};

  vector<char> rightDiag = {matrix[0][0], matrix[1][1], matrix[2][2]};
  vector<char> leftDiag = {matrix[0][2], matrix[1][1], matrix[2][0]};
  rightSide = (xmas == rightDiag || rxmas == rightDiag);
  leftSide = (xmas == leftDiag || rxmas == leftDiag);
  if (leftSide && rightSide) {
    matches++;
  }

  return matches;
}

int calculateMatch(vector<vector<char>> matrix, int rowN, int colN) {
  // Now we are going to iter through each 1234 rows and 1234 cols. In a square
  // search manner
  int matches = 0;
  vector<char> xmas = {'X', 'M', 'A', 'S'};
  vector<char> rxmas = {'S', 'A', 'M', 'X'};

  // Now we can do separate checks
  if (rowN == 0) {
    for (int row = 0; row < 4; row++) {
      matches += (xmas == matrix[row] || rxmas == matrix[row]);
    }
  } else {
    matches += (xmas == matrix[3] || rxmas == matrix[3]);
  }
  if (colN == 0) {
    for (int col = 0; col < 4; col++) {
      vector<char> colVec;
      for (int r = 0; r < 4; r++) {
        colVec.push_back(matrix[r][col]);
      }
      matches += (xmas == colVec || rxmas == colVec);
    }
  } else {
    vector<char> colVec;
    for (int r = 0; r < 4; r++) {
      colVec.push_back(matrix[r][3]);
    }
    matches += (xmas == colVec || rxmas == colVec);
  }
  vector<char> rightDiag = {matrix[0][0], matrix[1][1], matrix[2][2],
                            matrix[3][3]};
  vector<char> leftDiag = {matrix[0][3], matrix[1][2], matrix[2][1],
                           matrix[3][0]};
  matches += (xmas == rightDiag || rxmas == rightDiag);
  matches += (xmas == leftDiag || rxmas == leftDiag);

  return matches;
}

void printlines(vector<vector<char>> mat, int rowN) {
  for (int i = rowN; i < rowN + 3; i++) {
    for (int j = 0; j < mat.size(); j++) {
      cout << mat[i][j] << " ";
    }
    cout << endl;
  }
}

int main() {
  // File that we are going to parse
  string file = "./input.txt";
  const int N = 140;
  vector<vector<char>> mat;
  vector<vector<char>> slicedMat;
  int matchNum = 0;

  // Generate our matrix of values
  mat = storeFile(file, N, N);

  int lastAmount = N % 4;
  int rowLast;
  int colLast;
  if (lastAmount != 0) {
    colLast = lastAmount + 1;
    rowLast = lastAmount;
  } else {
    colLast = 3;
    rowLast = 2;
  }

  // Itr through and slice our matrix
  // for (int rowN = 0; rowN < N - (rowLast + 1); rowN++) {
  //   for (int colN = 0; colN < N - colLast; colN++) {
  for (int rowN = 0; rowN < N - 2; rowN++) {
    for (int colN = 0; colN < N - 2; colN++) {
      cout << "ROW NUM: " << rowN << endl;
      cout << "col NUM: " << colN << endl;
      cout << "Col Last: " << colLast << " Row Last: " << rowLast << endl;
      cout << "FULL 4 LINES: " << endl;
      printlines(mat, rowN);
      slicedMat = sliceMatrix(mat, rowN, colN);
      // matchNum += calculateMatch(slicedMat, rowN, colN);
      matchNum += calculateMas(slicedMat, rowN, colN);

      // Testing Output
      cout << "NEW COLUMN: " << colN << "Row: " << rowN << endl;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          cout << slicedMat[i][j] << " ";
        }
        cout << endl;
      }
    }
  }
  cout << "XMAS FOUND: " << matchNum << endl;

  return 0;
}
