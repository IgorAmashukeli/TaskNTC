#include <boost/regex.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <unicode/brkiter.h>
#include <unicode/unistr.h>
#include <unicode/utypes.h>
#include <vector>

std::string read_text() {
  std::ifstream inputFile("text.txt");
  std::stringstream buffer;
  buffer << inputFile.rdbuf();
  return buffer.str();
}

using Tokenizer = std::unique_ptr<icu::BreakIterator>;

Tokenizer prepareTokenizer(const icu::UnicodeString &txt) {
  auto status = U_ZERO_ERROR;
  auto tok = Tokenizer(
      icu::BreakIterator::createSentenceInstance(icu::Locale{"ru_RU"}, status));
  if (U_FAILURE(status)) {
    std::cerr << "Ошибка создания BreakIterator" << std::endl;
    return nullptr;
  }
  tok->setText(txt);
  return std::move(tok);
}

std::string trim(std::string s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
          }));
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [](unsigned char ch) { return !std::isspace(ch); })
              .base(),
          s.end());

  return s;
}

std::vector<std::string> trim_vec(std::vector<std::string> vec) {
  for (size_t i = 0; i < vec.size(); ++i) {
    vec[i] = trim(std::move(vec[i]));
  }
  return vec;
}

std::string remove_line_breaks(std::string str) {
  std::replace(str.begin(), str.end(), '\n', ' ');
  std::replace(str.begin(), str.end(), '\r', ' ');
  return str;
}

std::vector<std::string> tokenize_to_sentences(std::string text) {
  text = remove_line_breaks(std::move(text));
  std::vector<std::string> result;
  auto txt = icu::UnicodeString::fromUTF8(text);
  auto tok = prepareTokenizer(txt);
  if (!tok) {
    return {};
  }

  int32_t start = tok->first(), end = tok->next();
  std::string str;
  while (end != icu::BreakIterator::DONE) {
    txt.tempSubStringBetween(start, end).toUTF8String(str);
    result.push_back(std::move(str));
    start = end;
    end = tok->next();
  }

  return result;
}

// the only eight type of coordinate could have been splitted in halfs
void fix_spliteded_eight_type(std::vector<std::string> &vec) {
  size_t i = 0;
  while (i < vec.size()) {
    if (i + 1 != vec.size() &&
        (vec[i].ends_with("с.ш.") || vec[i].ends_with("ю.ш."))) {
      vec[i] += vec[i + 1];
      vec.erase(vec.begin() + i + 1);
    } else {
      ++i;
    }
  }
}

int main() {

  auto vec = tokenize_to_sentences(read_text());
  vec = trim_vec(vec);
  fix_spliteded_eight_type(vec);
  for (const auto &str : vec) {
    std::cout << str << "\n\n";
  }
}
