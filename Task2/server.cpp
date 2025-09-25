#include "str_utils.h"
#include <cassert>
#include <crow.h>
#include <string>
#include <unicode/brkiter.h>
#include <unicode/unistr.h>
#include <unicode/utypes.h>
#include <vector>

enum { PREF_SENT_SIZE = 200 };

crow::json::wvalue FindSets(const std::string &s) {
    crow::json::wvalue res;

    auto coords = regex_str::ExtractCoordinates(s);
    auto words = tokenizer::TokenizeToWords(s);

    auto sets = coordinate_sets::FindSets(coords, coordinate_sets::FindEps(coords), 500);

    auto set_marks = coordinate_sets::CalcSetInfo(words, sets);

    for (size_t i = 0; i < set_marks.size(); ++i) {
        res[coordinate_sets::kSetNames[i]] =
            coordinate_sets::ArrOfCoordinateSetsToString(set_marks[i]);
    }

    return res;
}

crow::json::wvalue FindCoordinate200Sentences(const std::string &s) {
    crow::json::wvalue res;

    auto sentences = tokenizer::TokenizeToSentences(s);
    for (const auto &sentence : sentences) {
        auto coordinates = regex_str::ExtractCoordinates(sentence);
        for (const auto &coordinate : coordinates) {
            res[coordinate::CoordinatesToString(coordinate.lat, coordinate.lon)] =

                // times 2, because cyrillic
                sentence.substr(0, PREF_SENT_SIZE * 2);
        }
    }
    return res;
}

crow::json::wvalue FindCoordinateNames(const std::string &s) {
    crow::json::wvalue res;
    auto words = tokenizer::TokenizeToWords(s);
    auto coordinates = regex_str::ExtractCoordinates(s);
    auto results = woords_with_coords::CollectWordsAroundCoords(words, coordinates, 2);
    for (const auto &wor_cord : results) {
        res[coordinate::CoordinatesToString(wor_cord.coord.lat, wor_cord.coord.lon)] =
            tokenizer::Concat(wor_cord.context);
    }

    return res;
}

crow::json::wvalue Process(std::string str) {

    crow::json::wvalue res = {};

    res["sets"] = FindSets(str);
    res["coordinates_sentences"] = FindCoordinate200Sentences(str);
    res["coordinates_names"] = FindCoordinateNames(str);

    return res;
}

crow::json::wvalue PostProccessing(const crow::request &req) {
    auto rv = crow::json::load(req.body);
    auto txt = rv["text"];
    auto str = txt.s();

    return Process(std::move(str));
}

void ServerWork() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/process_coordinates").methods("POST"_method)(PostProccessing);

    app.port(8080).multithreaded().run();
}

int main() {
    ServerWork();
}