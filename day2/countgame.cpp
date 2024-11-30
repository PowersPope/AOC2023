#include <iostream>
#include <fstream>
#include <regex>
#include <sstream>
#include <cstring>
#include <typeinfo>

// Functions for making this task easier
int grabGameNumber(std::string text){
  // This function will extract out the game number when our string is split on :
  // Our input looks like "Game 11:" We want to grab "11"
  std::regex re("[0-9]+");
  std::smatch m;
  std::string stringNum;
  int convertedNum;

  // run regex match on our object
  while (std::regex_search(text, m, re))
  {
    // Grab the first and only match
    stringNum = m.str(0);
    text = m.suffix().str();
  }
  // Convert our string to an int
  convertedNum = std::stoi(stringNum);
  return convertedNum;
}

std::vector<std::string> findDelim(std::string s, char delim)
{
  // Function to grab all lines and occurences that are found within delim
  int lastPos = 0;
  std::vector<std::string> delimOccurence;

  for(int i=0; i < s.size(); i++){
    if(s[i] == delim){
      size_t extractLength = i - lastPos + 1;
      delimOccurence.push_back(s.substr(lastPos, extractLength));
      lastPos = i+1;
    } else if (i == s.size()-1) {
      size_t extractLength = i - lastPos + 1;
      delimOccurence.push_back(s.substr(lastPos, extractLength));
    }
  }
  return delimOccurence;
}

bool compareDice(std::string segment, std::map<std::string, int> &diceStandards)
{
  // Grab a line segement from findDelim <vector> and compare each element against our hashmap
  std::string diceName;
  int diceNum;
  std::stringstream segss(segment);
  std::regex reName("[a-z]+");
  std::regex reNum("[0-9]+");
  std::string ss;
  std::smatch smName;
  std::smatch smNum;

  // std::cout << "SEGMENT: " << segment << std::endl;

  while (std::getline(segss, ss, ','))
  {
    if (std::regex_search(ss, smName, reName) && std::regex_search(ss, smNum, reNum)) {
    diceName = smName.str();
    diceNum = std::stoi(smNum.str());

    if (diceStandards[diceName] < diceNum){
        // std::cout << diceName << ' ' << diceNum << "Standard: " << diceStandards[diceName] << std::endl;
        return false;
      }
    }
  }
  return true;
}

bool computePossibility(std::string segment)
{
  // We want to take in a portion of the input 1 or 10 and then a string
  // eg. 10 red, 12 green
  // We want to compare red to our possibility hashmap if good then pass
  // if more than the number then fail
  std::map<std::string, int> dice;
  dice["red"] = 12;
  dice["green"] = 13;
  dice["blue"] = 14;
  bool diceBool;
  char delim = ';';
  char midDelim = ',';

  // Find out iter portions
  std::vector<std::string> breakPoints = findDelim(segment, delim);

  for (std::string pos: breakPoints){
    // Compare the dice
    // std::cout << "POS: " << pos << std::endl;
    diceBool = compareDice(pos, dice);
    if (diceBool == false){
      return false;
    }
  }
  return true;
}


int main(void){
  // Read in our file
  std::ifstream file("./file.txt");

  // Iter through our stream buffer and store into string contents
  std::string contents((std::istreambuf_iterator<char>(file)),
                       std::istreambuf_iterator<char>());

  // Now we want to iter through the contents of each line
  std::istringstream perline(contents);
  std::string line;
  bool possible;
  int totalSum = 0;
  int out;

  // Grab each line, but split by particular portion :
  while (std::getline(perline, line)){
    // Add the split item to our vector
    // store_out.push_back(line);
    int delim_pos = line.find(":");
    out = grabGameNumber(line.substr(0,delim_pos));
    possible = computePossibility(line.substr(delim_pos + 1));
    if (possible == true){
      // std::cout << out << std::endl;
      totalSum += out;
    }
  }
  std::cout << totalSum << std::endl;

  return 0;
}
