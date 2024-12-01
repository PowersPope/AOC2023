#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>

// For this task today we need to generate a script that reads in a line
// Grabs the first and last number (if only 1 number then it is both first and last)
// Combine them to make a two digit number
// Then sum them all together.
// Everything inbetween is either an integer or a lower case char
//

//Define a counting function
int grabNumbers(std::string text, std::regex const & expr)
{
  // Init our match and number storing variables
  std::smatch match;
  std::string first_number;
  std::string final_number;
  // Our out variable and the iteration i
  int out_number;
  int i = 0;

  // Our hash map
  std::map<std::string, std::string> wordToInt;
  wordToInt["zero"] = "0";
  wordToInt["one"] = "1";
  wordToInt["two"] = "2";
  wordToInt["three"] = "3";
  wordToInt["four"] = "4";
  wordToInt["five"] = "5";
  wordToInt["six"] = "6";
  wordToInt["seven"] = "7";
  wordToInt["eight"] = "8";
  wordToInt["nine"] = "9";

  // Accumulate the number of matches
  while (std::regex_search(text, match, expr))
  {
    // If the first entry then store
    if (i == 0){
      if (match.str(0).length() > 1){
        first_number = wordToInt[match.str(0)];
      } else {first_number = match.str(0);}

    } else{
      // Add whatever the last match was
      if (match.str(0).length() > 1){
        final_number = wordToInt[match.str(0)];
      } else {final_number = match.str(0);}
    }
    // Iterate up and move along our text
    i++;
    text = match.suffix().str();
  }
  // If there are multiple add the first and last
  // If there isn't then just add the same number twice
  if (i > 1){
    out_number = std::stoi(std::string(first_number) + final_number);
  } else {
    out_number = std::stoi(std::string(first_number) + first_number);
  }
  return out_number;
}

int main()
{
  // First we have to load in our file into variable in
  std::ifstream in("./input.txt");

  // Iter through our stream buffer and store into string contents
  std::string contents((std::istreambuf_iterator<char>(in)),
                       std::istreambuf_iterator<char>());

  // We want to now go through our contents using stringstream
  std::istringstream iss(contents);
  std::string line;
  int out;

  // Match any number
  std::regex pattern("[0-9]|zero|one|two|three|four|five|six|seven|eight|nine");

  // Get each individual line within our contents/file
  while (std::getline(iss, line))
  {
    out += grabNumbers(line, pattern);
  }
  std::cout << "Total: " << out << std::endl;

  return 0;
}
