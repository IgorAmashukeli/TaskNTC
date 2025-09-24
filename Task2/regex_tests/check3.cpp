#include <boost/regex.hpp>
#include <iostream>

int main() {
  std::string text = "6.2 51°12.32'С 32°34.43'Ю";

  constexpr auto sixth_2 =
      R"((\d{1,2})°(\d{1,2}\.\d+)'(\xD0\xA1|\xD0\xAE) (\d{1,3})°(\d{1,2}\.\d+)'(\xD0\x97|\xD0\x92))";

  boost::regex r(sixth_2);

  bool m = boost::regex_search(text, r);

  std::cout << "Match: " << m << "\n";
}