
#include "../regex_str.h"
#include <fstream>
#include <iomanip>
#include <iostream>

std::string read_text() {
  std::ifstream inputFile("text.txt");
  std::stringstream buffer;
  buffer << inputFile.rdbuf();
  return buffer.str();
}

int main() {
  std::string str = read_text();

  auto res = regex_str::extract_substrings(str);

  for (size_t i = 0; i < res.size(); ++i) {
    std::cout << std::fixed << std::setprecision(6);
    // std::cout << res[i].lat << " " << res[i].lon << "\n";
    // td::cout << res[i].start_byte << " " << res[i].end_byte << "\n";
    std::cout << str.substr(res[i].start_byte,
                            res[i].end_byte - res[i].start_byte)
              << "\n";
  }
}