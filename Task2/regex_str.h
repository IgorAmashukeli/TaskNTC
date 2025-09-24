#pragma once
#include <boost/regex.hpp>
#include <unicode/brkiter.h>
#include <unicode/unistr.h>
#include <unicode/utypes.h>
#include <vector>

namespace regex_str {

enum TYPE { simple, complex };

constexpr auto wrong = -1000.0;

constexpr auto first = R"(([+-]?\d+\.\d+) ([+-]?\d+\.\d+))";
constexpr auto second = R"(([NS])(\d+\.\d+) ([WE])(\d+\.\d+))";
constexpr auto third = R"((\d+)-(\d+)([NS]) (\d+)-(\d+)([WE]))";
constexpr auto fourth = R"((\d{2})(\d{2})([NS]) (\d{2,3})(\d{2})([WE]))";
constexpr auto fourth_1 = R"((\d{1,2})([NS]) (\d{1,3})([WE]))";
constexpr auto fifth =
    R"(([NS])(\d{2})(\d{2})(\d{2}) ([WE])(\d{3})(\d{2})(\d{1,2}))";
constexpr auto fifth_1 = R"(([NS])(\d{2})(\d{2}) ([WE])(\d{3})(\d{1,2}))";
constexpr auto fifth_2 = R"(([NS])(\d{1,2}) ([WE])(\d{1,3}))";
constexpr auto sixth =
    R"((\d{1,2})°(\d{1,2}\.\d+)'([NS]) (\d{1,3})°(\d{1,2}\.\d+)'([WE]))";
// added format, where letters are at the start
constexpr auto sixth_with_directions_start =
    R"(([NS])(\d{1,2})°(\d{1,2}\.\d+)' ([WE])(\d{1,3})°(\d{1,2}\.\d+)')";
constexpr auto sixth_1 =
    R"((\d{1,2})°(\d{1,2})'([NS]) (\d{1,3})°(\d{1,2})'([WE]))";
constexpr auto sixth_2 =
    R"((\d{1,2})°(\d{1,2}\.\d+)'(\xD0\xA1|\xD0\xAE) (\d{1,3})°(\d{1,2}\.\d+)'(\xD0\x97|\xD0\x92))";
constexpr auto sixth_3 = R"((\d{1,2})°([NS]) (\d{1,3})°([WE]))";

constexpr auto seventh =
    R"((\d{1,2})°(\d{1,2})'(\d{1,2}\.\d+)''([NS]) (\d{1,3})°(\d{1,2})'(\d{1,2}\.\d+)''([WE]))";
constexpr auto seventh_with_quotes =
    R"((\d{1,2})°(\d{1,2})'(\d{1,2}\.\d+)\"([NS]) (\d{1,3})°(\d{1,2})'(\d{1,2}\.\d+)\"([WE]))";
constexpr auto seventh_1 =
    R"((\d{1,2})°(\d{1,2})'(\d{1,2})''([NS]) (\d{1,3})°(\d{1,2})'(\d{1,2})''([WE]))";
constexpr auto seventh_with_dig_quotes =
    R"((\d{1,2})°(\d{1,2})′(\d{1,2}\.\d+)″([NS]) (\d{1,3})°(\d{1,2})′(\d{1,2}\.\d+)″([WE]))";
// 7.2 IS ACTUALLY 6.1 ???
constexpr auto eighth =
    R"((\d{1,2})°(\d{1,2}\.\d+)' (\xD1\x81|\xD1\x8E)\.\xD1\x88\. (\d{1,3})°(\d{1,2}\.\d+)' (\xD0\xB2|\xD0\xB7)\.\xD0\xB4\.)";
// almost the same as 6.2, but with a space
constexpr auto eighth_1 =
    R"((\d{1,2})°(\d{1,2}\.\d+)' (\xD0\xA1|\xD0\xAE) (\d{1,3})°(\d{1,2}\.\d+)' (\xD0\x97|\xD0\x92))";
constexpr auto nineth =
    R"((\d{1,2})°(\d{1,2})'(\d{1,2}\.\d+)'' (\xD1\x81|\xD1\x8E)\.\xD1\x88\. (\d{1,3})°(\d{1,2})'(\d{1,2}\.\d+) (\xD0\xB2|\xD0\xB7)\.\xD0\xB4\.)";
constexpr auto nineth_1 =
    R"((\d{1,2})°(\d{1,2})'(\d{1,2}\.\d+)'' (\xD0\xA1|\xD0\xAE) (\d{1,3})°(\d{1,2})'(\d{1,2}\.\d+)' (\xD0\x97|\xD0\x92))";
constexpr auto tenth =
    R"((\d{1,2})(\d{2})(\d{2}\.\d+)([NS]) (\d{1,3})(\d{2})(\d{2}\.\d+)([WE]))";
constexpr auto eleventh =
    R"((\d{1,2})-(\d{1,2}.\d+)([NS]) (\d{1,3})-(\d{1,2}.\d+)([WE]))";
constexpr auto twelve = R"(([+-]?\d+\,\d+)°, ([+-]?\d+\,\d+)°)";
// with point not comma as in twelve
constexpr auto twelve_1 = R"(([+-]?\d+\.\d+)°, ([+-]?\d+\.\d+)°)";
constexpr auto thirteenth = R"(([NS])(\d+\.\d+)°, ([WE])(\d+\.\d+)°)";

std::pair<double, double>
extract_template(TYPE type, const std::string &text, const char *const regex,
                 std::vector<size_t> lat_coord = {1},
                 std::vector<size_t> lon_coord = {2}, size_t latm1_coord = 0,
                 size_t lonm1_coord = 0, const char *const south = "",
                 const char *const west = "", bool replace_comma = false);

std::pair<double, double> extract_first(const std::string &text);
std::pair<double, double> extract_second(const std::string &text);
std::pair<double, double> extract_third(const std::string &text);
std::pair<double, double> extract_fourth(const std::string &text);
std::pair<double, double> extract_fourth_1(const std::string &text);
std::pair<double, double> extract_fifth(const std::string &text);
std::pair<double, double> extract_fifth_1(const std::string &text);
std::pair<double, double> extract_fifth_2(const std::string &text);
std::pair<double, double> extract_sixth(const std::string &text);
std::pair<double, double>
extract_six_with_directions_start(const std::string &text);
std::pair<double, double> extract_sixth_1(const std::string &text);
std::pair<double, double> extract_sixth_2(const std::string &text);
std::pair<double, double> extract_sixth_3(const std::string &text);
std::pair<double, double> extract_seventh(const std::string &text);
std::pair<double, double> extract_seventh_with_quotes(const std::string &text);
std::pair<double, double> extract_seventh_1(const std::string &text);
std::pair<double, double>
extract_seventh_with_dig_quotes(const std::string &text);
std::pair<double, double> extract_eighth(const std::string &text);
std::pair<double, double> extract_eighth_1(const std::string &text);
std::pair<double, double> extract_nineth(const std::string &text);
std::pair<double, double> extract_nineth_1(const std::string &text);
std::pair<double, double> extract_tenth(const std::string &text);
std::pair<double, double> extract_eleventh(const std::string &text);
std::pair<double, double> extract_twelve(const std::string &text);
std::pair<double, double> extract_twelve_1(const std::string &text);
std::pair<double, double> extract_thirteen(const std::string &text);

struct MatchInfo {
  size_t start_byte;
  size_t end_byte;
  double lat;
  double lon;
};

// correct order from more strict to less strict
constexpr std::array<const char *const, 26> regexs = {
    thirteenth,
    second,
    fifth,
    fifth_1,
    fifth_2,
    sixth_with_directions_start,
    seventh,
    seventh_with_quotes,
    seventh_with_dig_quotes,
    seventh_1,
    sixth,
    sixth_1,
    sixth_3,
    eleventh,
    tenth,
    third,
    fourth,
    fourth_1,
    nineth_1,
    sixth_2,
    eighth_1,
    eighth,
    nineth,
    twelve_1,
    twelve,
    first};

constexpr std::array<std::pair<double, double> (*)(const std::string &), 26>
    functions = {extract_thirteen,
                 extract_second,
                 extract_fifth,
                 extract_fifth_1,
                 extract_fifth_2,
                 extract_six_with_directions_start,
                 extract_seventh,
                 extract_seventh_with_quotes,
                 extract_seventh_with_dig_quotes,
                 extract_seventh_1,
                 extract_sixth,
                 extract_sixth_1,
                 extract_sixth_3,
                 extract_eleventh,
                 extract_tenth,
                 extract_third,
                 extract_fourth,
                 extract_fourth_1,
                 extract_nineth_1,
                 extract_sixth_2,
                 extract_eighth_1,
                 extract_eighth,
                 extract_nineth,
                 extract_twelve_1,
                 extract_twelve,
                 extract_first};

std::vector<MatchInfo> extract_substrings(const std::string &s);

}; // namespace regex_str