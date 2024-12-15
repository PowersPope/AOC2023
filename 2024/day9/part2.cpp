#include <bits/stdc++.h>
using namespace std;

pair<vector<int>, bool> forwardCheck(vector<int> inputVec, size_t chunkSize,
                                     int lastCheck) {
  vector<int> freeSpaceIdx;
  for (int i = 0; i < lastCheck; i++) {
    if (inputVec[i] == -1) {
      freeSpaceIdx.push_back(i);
      if (freeSpaceIdx.size() == chunkSize) {
        return make_pair(freeSpaceIdx, true);
      }
    } else {
      freeSpaceIdx.clear();
    }
  }
  return make_pair(freeSpaceIdx, false);
}

int main() {
  // Load in input file
  ifstream inStream;
  // inStream.open("example.txt");
  // inStream.open("example2.txt");
  // inStream.open("example3.txt");
  inStream.open("input.txt");

  // Handle error when opening today's file
  if (!inStream.is_open()) {
    cout << "File is not opened correctly!" << endl;
    return 0;
  }

  string line;
  vector<int> memFix;
  int id = 0;

  // Grab our input
  while (getline(inStream, line)) {
    // cout << line << endl;
    // Read in the line (string of ints)
    for (int i = 0; i < line.size(); i++) {
      // Grab out our block and memory information
      if (i % 2 == 0) {
        int fileblock = stoi(line.substr(i, 1));
        vector<int> fileVec(fileblock, id);
        // Expand memFix size
        memFix.reserve(memFix.size() +
                       distance(fileVec.begin(), fileVec.end()));
        // Insert our new file blocks
        memFix.insert(memFix.end(), fileVec.begin(), fileVec.end());
        // Increment our id tracker
        id++;
      } else {
        int freespace = stoi(line.substr(i, 1));
        vector<int> freeVec(freespace, -1);
        memFix.reserve(memFix.size() +
                       distance(freeVec.begin(), freeVec.end()));
        // Insert our new file blocks
        memFix.insert(memFix.end(), freeVec.begin(), freeVec.end());
      }
    }
  }

  // Display the input
  // for (const auto c : memFix) {
  //   cout << c << " ";
  // }
  // cout << endl;

  unsigned long total = 0;
  int lastCheck = memFix.size() - 1;
  int reverseContiguousSpace = 0;
  int forwardContiguousSpace = 0;
  int forwardEndIdx;
  int lastInt;
  vector<int> reverseIdx;
  pair<vector<int>, bool> out;

  // Part 2 Brief
  // Now reformat with chunking spaces
  // Look for contiguous matches of numbers that are not -1 in reverse order of
  // vector once block found another loop that looks forward through vector to
  // find -1 blocks that match number of contiguous block from before If found
  // then swap if not then move on to the first loop
  for (int i = lastCheck; i >= 0; i--) {
    int currentSpace = memFix[i];
    // If this is not an empty space then start recording
    if (currentSpace != -1 && reverseContiguousSpace == 0) {
      // Add the initial information
      reverseContiguousSpace++;
      reverseIdx.push_back(i);
    } else if (currentSpace != -1 && memFix[i + 1] == currentSpace &&
               reverseContiguousSpace > 0) {
      // increment information
      reverseContiguousSpace++;
      reverseIdx.push_back(i);
    } else if (memFix[i + 1] != currentSpace && reverseContiguousSpace > 0) {
      // Here we do the forward search
      out = forwardCheck(memFix, reverseIdx.size(), reverseIdx[0]);
      if (out.second) {
        // Here we swap the back portion with our forward section
        // cout << "Index size: " << reverseIdx.size() << " and "
        //      << reverseContiguousSpace << endl;
        for (int j = 0; j < reverseIdx.size(); j++) {
          // printf("Number %i: (%i, %i) -> (%i, %i)\n", j, out.first[j],
          //        memFix[out.first[j]], reverseIdx[j], memFix[reverseIdx[j]]);
          swap(memFix[out.first[j]], memFix[reverseIdx[j]]);
        }
        // This is for checking what we are swapping
        // cout << "-------------------" << endl;
        // cout << " Here is the Reverse Postions being Swapped: " << endl;
        // for (int j = 0; j < reverseContiguousSpace; j++) {
        //   cout << "Forward portion " << memFix[out.first[j]] << " -> "
        //        << memFix[reverseIdx[j]] << endl;
        // }
        // for (const auto c : memFix) {
        //   cout << c << " ";
        // }
        // cout << endl;
        // cout << "-------------------" << endl;
      }
      // cout << "BEFORE IF AFTER SWAP CURRENT INT IS: " << memFix[i]
      //      << " and index: " << i << endl;
      if (memFix[i] == -1) {
        // cout << "This is a -1" << endl;
        reverseContiguousSpace = 0;
        forwardContiguousSpace = 0;
        reverseIdx.clear();
      } else {
        // cout << "Current Space after swapping: " << memFix[i] << endl;
        reverseContiguousSpace = 1;
        forwardContiguousSpace = 0;
        reverseIdx.clear();
        reverseIdx.push_back(i);
      }
    } else {
      reverseContiguousSpace = 0;
      forwardContiguousSpace = 0;
      reverseIdx.clear();
    }
  }

  // Part 1
  // Now reformat in reverse
  // for (int i = memFix.size() - 1; i >= 0; i--) {
  //   // If int != -1
  //   if (memFix[i] != -1) {
  //     for (int j = 0; j < memFix.size(); j++) {
  //       if (memFix[j] == -1 && j < i) {
  //         swap(memFix[i], memFix[j]);
  //         break;
  //       }
  //     }
  //   }
  // }

  // for (const auto c : memFix) {
  //   cout << c << " ";
  // }
  // cout << endl;

  // Count the number of values
  for (int i = 0; i < memFix.size(); i++) {
    if (memFix[i] != -1) {
      unsigned long out = memFix[i] * i;
      total += out;
      // printf("%i * %i  = %lu\n", memFix[i], i, total);
    }
  }

  cout << total << endl;

  return 0;
}
