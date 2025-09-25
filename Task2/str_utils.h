#pragma once
#include <boost/regex.hpp>
#include <unicode/brkiter.h>
#include <unicode/unistr.h>
#include <unicode/utypes.h>
#include <unordered_set>
#include <vector>
#include <iostream>

namespace tokenizer {

struct WordInfo {
    std::string word;
    size_t start_byte;
    size_t end_byte;
};

using Tokenizer = std::unique_ptr<icu::BreakIterator>;

Tokenizer PrepareSentenceTokenizer(const icu::UnicodeString &txt);
Tokenizer PrepareWordTokenizer(const icu::UnicodeString &txt);
std::vector<std::string> TokenizeToSentences(const std::string &text);
std::vector<tokenizer::WordInfo> TokenizeToWords(const std::string &text);

std::string Concat(const std::vector<std::string> &vec);
};  // namespace tokenizer

// namespace coordinate

namespace names {
bool IsCoordNumber(const std::string &word);
bool IsStopword(const std::string &word);

bool IsPolygonWord(const std::string &word);

const std::unordered_set<std::string> kPolygons = {"круговой", "замкнутый", "полигон",
                                                   "прямоугольный", "замкнутым"};

const std::unordered_set<std::string> kStopWords = {"в",
                                                    "на",
                                                    "за",
                                                    "с",
                                                    "по",
                                                    "от",
                                                    "до",
                                                    "для",
                                                    "о",
                                                    "об",
                                                    "и",
                                                    "но",
                                                    "а",
                                                    "как",
                                                    "где",
                                                    "что",
                                                    "чтобы",
                                                    "из",
                                                    "уже",
                                                    "затем",
                                                    "после",
                                                    "перед",
                                                    "или",
                                                    "над",
                                                    "без",
                                                    "n",
                                                    "e",
                                                    "атлантический",
                                                    "атлантических",
                                                    "s",
                                                    "w",
                                                    "ю",
                                                    "з",
                                                    "в",
                                                    "ш",
                                                    "д",
                                                    "мы",
                                                    "через",
                                                    "широта",
                                                    "все",
                                                    "наши",
                                                    "нашим",
                                                    "обнаружение",
                                                    "обнаружения",
                                                    "это",
                                                    "был",
                                                    "была",
                                                    "были",
                                                    "было",
                                                    "наш",
                                                    "нами",
                                                    "их",
                                                    "его",
                                                    "ее",
                                                    "им",
                                                    "ими",
                                                    "такой",
                                                    "так",
                                                    "также",
                                                    "далее",
                                                    "необходимо",
                                                    "примерно",
                                                    "приблизительно",
                                                    "особенно",
                                                    "особо",
                                                    "только",
                                                    "даже",
                                                    "весьма",
                                                    "всегда",
                                                    "однако",
                                                    "отметим",
                                                    "внимание",
                                                    "внимания",

                                                    ".",
                                                    ",",
                                                    ":",
                                                    ";",
                                                    "(",
                                                    ")",
                                                    "«",
                                                    "»",
                                                    "-",
                                                    "--",
                                                    "–",
                                                    "\"",
                                                    "'",
                                                    "''",

                                                    "км",
                                                    "м",
                                                    "морских",
                                                    "миль",
                                                    "градусов",
                                                    "секунд",
                                                    "минут",
                                                    "°",
                                                    "′",
                                                    "″",
                                                    "'",
                                                    "''",
                                                    "место",
                                                    "места",
                                                    "мест",
                                                    "координаты",
                                                    "координата",
                                                    "координат"

};
};  // namespace names

namespace regex_str {

enum TYPE { simple, complex };

constexpr auto kFirst = R"(([+-]?\d+\.\d+) ([+-]?\d+\.\d+))";
constexpr auto kSecond = R"(([NS])(\d+\.\d+) ([WE])(\d+\.\d+))";
constexpr auto kThird = R"((\d+)-(\d+)([NS]) (\d+)-(\d+)([WE]))";
constexpr auto kFourth = R"((\d{2})(\d{2})([NS]) (\d{2,3})(\d{2})([WE]))";
constexpr auto kFourth1 = R"((\d{1,2})([NS]) (\d{1,3})([WE]))";
constexpr auto kFifth = R"(([NS])(\d{2})(\d{2})(\d{2}) ([WE])(\d{3})(\d{2})(\d{1,2}))";
constexpr auto kFifth1 = R"(([NS])(\d{2})(\d{2}) ([WE])(\d{3})(\d{1,2}))";
constexpr auto kFifth2 = R"(([NS])(\d{1,2}) ([WE])(\d{1,3}))";
constexpr auto kSixth = R"((\d{1,2})°(\d{1,2}\.\d+)'([NS]) (\d{1,3})°(\d{1,2}\.\d+)'([WE]))";
// added format, where letters are at the start
constexpr auto kSixthWithDirectionsStart =
    R"(([NS])(\d{1,2})°(\d{1,2}\.\d+)' ([WE])(\d{1,3})°(\d{1,2}\.\d+)')";
constexpr auto kSixth1 = R"((\d{1,2})°(\d{1,2})'([NS]) (\d{1,3})°(\d{1,2})'([WE]))";
constexpr auto kSixth2 =
    R"((\d{1,2})°(\d{1,2}\.\d+)'(\xD0\xA1|\xD0\xAE) (\d{1,3})°(\d{1,2}\.\d+)'(\xD0\x97|\xD0\x92))";
constexpr auto kSixth3 = R"((\d{1,2})°([NS]) (\d{1,3})°([WE]))";

constexpr auto kSeventh =
    R"((\d{1,2})°(\d{1,2})'(\d{1,2}\.\d+)''([NS]) (\d{1,3})°(\d{1,2})'(\d{1,2}\.\d+)''([WE]))";
constexpr auto kSeventhWithQuotes =
    R"((\d{1,2})°(\d{1,2})'(\d{1,2}\.\d+)\"([NS]) (\d{1,3})°(\d{1,2})'(\d{1,2}\.\d+)\"([WE]))";
constexpr auto kSeventh1 =
    R"((\d{1,2})°(\d{1,2})'(\d{1,2})''([NS]) (\d{1,3})°(\d{1,2})'(\d{1,2})''([WE]))";
constexpr auto kSeventhWithDigQuotes =
    R"((\d{1,2})°(\d{1,2})′(\d{1,2}\.\d+)″([NS]) (\d{1,3})°(\d{1,2})′(\d{1,2}\.\d+)″([WE]))";
// 7.2 IS ACTUALLY 6.1 ???
constexpr auto kEighth =
    R"((\d{1,2})°(\d{1,2}\.\d+)' (\xD1\x81|\xD1\x8E)\.\xD1\x88\. (\d{1,3})°(\d{1,2}\.\d+)' (\xD0\xB2|\xD0\xB7)\.\xD0\xB4\.)";
// almost the same as 6.2, but with a space
constexpr auto kEighth1 =
    R"((\d{1,2})°(\d{1,2}\.\d+)' (\xD0\xA1|\xD0\xAE) (\d{1,3})°(\d{1,2}\.\d+)' (\xD0\x97|\xD0\x92))";
constexpr auto kNineth =
    R"((\d{1,2})°(\d{1,2})'(\d{1,2}\.\d+)'' (\xD1\x81|\xD1\x8E)\.\xD1\x88\. (\d{1,3})°(\d{1,2})'(\d{1,2}\.\d+) (\xD0\xB2|\xD0\xB7)\.\xD0\xB4\.)";
constexpr auto kNineth1 =
    R"((\d{1,2})°(\d{1,2})'(\d{1,2}\.\d+)'' (\xD0\xA1|\xD0\xAE) (\d{1,3})°(\d{1,2})'(\d{1,2}\.\d+)' (\xD0\x97|\xD0\x92))";
constexpr auto kTenth = R"((\d{1,2})(\d{2})(\d{2}\.\d+)([NS]) (\d{1,3})(\d{2})(\d{2}\.\d+)([WE]))";
constexpr auto kEleventh = R"((\d{1,2})-(\d{1,2}.\d+)([NS]) (\d{1,3})-(\d{1,2}.\d+)([WE]))";
constexpr auto kTwelve = R"(([+-]?\d+\,\d+)°, ([+-]?\d+\,\d+)°)";
// with point not comma as in twelve
constexpr auto kTwelve1 = R"(([+-]?\d+\.\d+)°, ([+-]?\d+\.\d+)°)";
constexpr auto kThirteenth = R"(([NS])(\d+\.\d+)°, ([WE])(\d+\.\d+)°)";

std::pair<double, double> ExtractTemplate(TYPE type, const std::string &text,
                                          const char *const regex,
                                          std::vector<size_t> lat_coord = {1},
                                          std::vector<size_t> lon_coord = {2},
                                          size_t latm1_coord = 0, size_t lonm1_coord = 0,
                                          const char *const south = "", const char *const west = "",
                                          bool replace_comma = false);

std::pair<double, double> ExtractFirst(const std::string &text);
std::pair<double, double> ExtractSecond(const std::string &text);
std::pair<double, double> ExtractThird(const std::string &text);
std::pair<double, double> ExtractFourth(const std::string &text);
std::pair<double, double> ExtractFourth1(const std::string &text);
std::pair<double, double> ExtractFifth(const std::string &text);
std::pair<double, double> ExtractFifth1(const std::string &text);
std::pair<double, double> ExtractFifth2(const std::string &text);
std::pair<double, double> ExtractSixth(const std::string &text);
std::pair<double, double> ExtractSixWithDirectionsStart(const std::string &text);
std::pair<double, double> ExtractSixth1(const std::string &text);
std::pair<double, double> ExtractSixth2(const std::string &text);
std::pair<double, double> ExtractSixth3(const std::string &text);
std::pair<double, double> ExtractSeventh(const std::string &text);
std::pair<double, double> ExtractSeventhWithQuotes(const std::string &text);
std::pair<double, double> ExtractSeventh1(const std::string &text);
std::pair<double, double> ExtractSeventhWithDigQuotes(const std::string &text);
std::pair<double, double> ExtractEighth(const std::string &text);
std::pair<double, double> ExtractEighth1(const std::string &text);
std::pair<double, double> ExtractNineth(const std::string &text);
std::pair<double, double> ExtractNineth1(const std::string &text);
std::pair<double, double> ExtractTenth(const std::string &text);
std::pair<double, double> ExtractEleventh(const std::string &text);
std::pair<double, double> ExtractTwelve(const std::string &text);
std::pair<double, double> ExtractTwelve1(const std::string &text);
std::pair<double, double> ExtractThirteen(const std::string &text);

struct MatchInfo {
    size_t start_byte;
    size_t end_byte;
    double lat;
    double lon;
};

// correct order from more strict to less strict
constexpr std::array<const char *const, 26> kRegexs = {kThirteenth,
                                                       kSecond,
                                                       kFifth,
                                                       kFifth1,
                                                       kFifth2,
                                                       kSixthWithDirectionsStart,
                                                       kSeventh,
                                                       kSeventhWithQuotes,
                                                       kSeventhWithDigQuotes,
                                                       kSeventh1,
                                                       kSixth,
                                                       kSixth1,
                                                       kSixth3,
                                                       kEleventh,
                                                       kTenth,
                                                       kThird,
                                                       kFourth,
                                                       kFourth1,
                                                       kNineth1,
                                                       kSixth2,
                                                       kEighth1,
                                                       kEighth,
                                                       kNineth,
                                                       kTwelve1,
                                                       kTwelve,
                                                       kFirst};

constexpr std::array<std::pair<double, double> (*)(const std::string &), 26> kFunctions = {
    ExtractThirteen,
    ExtractSecond,
    ExtractFifth,
    ExtractFifth1,
    ExtractFifth2,
    ExtractSixWithDirectionsStart,
    ExtractSeventh,
    ExtractSeventhWithQuotes,
    ExtractSeventhWithDigQuotes,
    ExtractSeventh1,
    ExtractSixth,
    ExtractSixth1,
    ExtractSixth3,
    ExtractEleventh,
    ExtractTenth,
    ExtractThird,
    ExtractFourth,
    ExtractFourth1,
    ExtractNineth1,
    ExtractSixth2,
    ExtractEighth1,
    ExtractEighth,
    ExtractNineth,
    ExtractTwelve1,
    ExtractTwelve,
    ExtractFirst};

std::vector<MatchInfo> ExtractCoordinates(const std::string &s);

};  // namespace regex_str

namespace coordinate {
constexpr auto kWrong = -1000.0;

std::string CoordinatesToString(double lat, double lon);

bool IsWordPolygon(const std::vector<tokenizer::WordInfo> &words,
                   const std::vector<regex_str::MatchInfo> &set, size_t k_before = 20);
};  // namespace coordinate

namespace woords_with_coords {
struct WordsForCoord {
    regex_str::MatchInfo coord;
    std::vector<std::string> context;
};
std::vector<WordsForCoord> CollectWordsAroundCoords(const std::vector<tokenizer::WordInfo> &words,
                                                    const std::vector<regex_str::MatchInfo> &coords,
                                                    size_t n_before = 2);
};  // namespace woords_with_coords

namespace coordinate_sets {

double Distance(const regex_str::MatchInfo &m1, const regex_str::MatchInfo &m2);

double FindEps(const std::vector<regex_str::MatchInfo> &vec);

std::vector<std::vector<regex_str::MatchInfo>> FindSets(
    const std::vector<regex_str::MatchInfo> &vec, double sm_dist, double byte_dist);

enum SetType { POINT, LINE, POLYGON };

const std::array<std::string, 3> kSetNames = {"points", "lines", "polygons"};

struct SetInfo {
    std::vector<regex_str::MatchInfo> set;
    SetType type;
};

bool ClosedSequence(const std::vector<regex_str::MatchInfo> &set);

std::array<std::vector<std::vector<regex_str::MatchInfo>>, 3> CalcSetInfo(
    const std::vector<tokenizer::WordInfo> &words,
    const std::vector<std::vector<regex_str::MatchInfo>> &sets);

std::string CoordinateSetToString(const std::vector<regex_str::MatchInfo> &set);

std::string ArrOfCoordinateSetsToString(const std::vector<std::vector<regex_str::MatchInfo>> &arr);
};  // namespace coordinate_sets