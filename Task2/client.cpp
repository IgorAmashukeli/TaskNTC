#include <cpr/cpr.h>
#include <fstream>
#include <iostream>
#include <sstream>

std::string read_text() {
  std::ifstream inputFile("text.txt");
  std::stringstream buffer;
  buffer << inputFile.rdbuf();
  return buffer.str();
}

std::string create_body(std::string_view text) {
  std::string body;
  body.reserve(9 + text.size() + 2);
  body.append("{\"text\":\"");
  body.append(text);
  body.append("\"}");
  return body;
}

void client_work() {
  std::string text = read_text();

  auto r = cpr::Post(cpr::Url{"http://localhost:8080/process_coordinates"},
                     cpr::Body{create_body(text)});

  std::cout << r.text << "\n";
}

int main() { client_work(); }