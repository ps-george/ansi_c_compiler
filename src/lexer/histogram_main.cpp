#include "histogram.hpp"

#include <algorithm>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string.h>
#include <unordered_map>
#include <vector>

typedef std::unordered_map<std::string, unsigned> histogram_type;

// Define the instance of the variable that is declared in the header
TokenValue yylval;

int main() {
  histogram_type histogram;
  double sum = 0.000;

  std::cout.setf(std::ios::fixed, std::ios::floatfield);
  std::cout.precision(3);

  while (1) {
    TokenType type = (TokenType)yylex();
    int hc = 0;
    std::string s = "";
    switch (type) {
    case (None):
      break; // No more tokens
    case (Number):
      // We have a number. The value will be
      // in yylval.numberValue
      sum = sum + yylval.numberValue;
      break;
    case (Word):
    case (Quoted):
      s = (std::string)(*yylval.wordValue);
      // if (type==Word) s.erase (std::remove (s.begin(), s.end(), ' '),
      // s.end());
      if (type == Quoted)
        s.erase(std::remove(s.begin(), s.end(), '"'), s.end());
      if (s == "") {
        break;
      }
      hc = histogram.count(s);
      // We have a string. The value is in a string
      // _pointed to_ by yylval.stringValue. Note that
      // the string is allocated by the lexer, but
      // deallocated by us.

      // add yylval.wordValue to histogram
      if (hc > 0) {
        // found
        histogram[s]++;
      } else {
        histogram.insert({s, 1});
        // not found
      }
      // std::cerr << "Inserted word into histogram" << std::endl;
      // Free the pointer yylval.wordValue to stop leaks
      delete yylval.wordValue;
      break;
    default:
      assert(0); // There are only four token types.
      return 1;
    }
    if (type == None)
      break;
  }
  //print out `sum` to cout with three decimal digits
  std::cout << sum << std::endl;

  // This sorts the histogram TODO: Find out how
  std::vector<std::pair<std::string, double>> sorted(histogram.begin(),
                                                     histogram.end());
  // std::cerr << "Put histogram into vector called sorted." << std::endl;

  std::sort(sorted.begin(), sorted.end(),
            [](const std::pair<std::string, double> &a,
               const std::pair<std::string, double> &b) {
              if (a.second > b.second)
                return true;
              if (a.second < b.second)
                return false;
              return a.first < b.first;
            });

  std::stringstream ss;
  auto it = sorted.begin();
  while (it != sorted.end()) {
    std::string name = it->first;
    // remove_chars_from_string(name,"\"");
    unsigned count = it->second;
    // Print out `name` and `count` to cout
    // Maybe craft stringstream then print to cout in one go
    std::cout << "\"" << name << "\" " << count << "\n";

    ++it;
  }

  return 0;
}
