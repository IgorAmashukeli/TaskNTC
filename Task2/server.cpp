#include "regex_str.h"
#include <cassert>
#include <crow.h>
#include <unicode/brkiter.h>
#include <unicode/unistr.h>
#include <unicode/utypes.h>
#include <vector>

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

std::vector<std::string> tokenize_to_sentences(const std::string &text) {
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

// not finished yet
std::vector<std::pair<std::vector<regex_str::MatchInfo>, std::string>>
find_sets(const std::string &s) {}

std::vector<std::pair<regex_str::MatchInfo, std::string>>
find_coordinate_200_sentences(const std::string &s) {}

std::vector<std::pair<regex_str::MatchInfo, std::string>>
find_coordinate_names(const std::string &s) {}

crow::json::wvalue process(std::string str) {

  std::vector<std::pair<std::vector<regex_str::MatchInfo>, std::string>>
      third_ans = find_sets(str);

  std::vector<std::pair<regex_str::MatchInfo, std::string>> fourth_ans =
      find_coordinate_200_sentences(str);

  std::vector<std::pair<regex_str::MatchInfo, std::string>> fifth_ans =
      find_coordinate_names(str);

  crow::json::wvalue res;
  res["sets"] = third_ans;
  res["coordinates_sentences"] = fourth_ans;
  res["coordinates_names"] = fifth_ans;

  return res;
}

crow::json::wvalue post_proccessing(const crow::request &req) {
  return process(crow::json::load(req.body)["text"].s());
}

void server_work() {
  crow::SimpleApp app;

  CROW_ROUTE(app, "/process_coordinates")
      .methods("POST"_method)(post_proccessing);

  app.port(8080).multithreaded().run();
}

int main() { server_work(); }