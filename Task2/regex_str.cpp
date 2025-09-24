#include "regex_str.h"

std::pair<double, double> regex_str::extract_template(
    TYPE type, const std::string &text, const char *const regex,
    std::vector<size_t> lat_coord, std::vector<size_t> lon_coord,
    size_t latm1_coord, size_t lonm1_coord, const char *const south,
    const char *const west, bool replace_comma) {

  boost::regex r(regex);
  boost::smatch m;
  if (boost::regex_search(text, m, r)) {

    std::array<double, 3> divisors = {1, 60.0, 3600.0};
    double lat = 0;
    double lon = 0;
    if (lat_coord.size() != lon_coord.size()) {
      return {wrong, wrong};
    }
    for (size_t i = 0; i < lat_coord.size(); ++i) {
      std::string lat_str = m[lat_coord[i]].str();
      std::string lon_str = m[lon_coord[i]].str();
      if (replace_comma) {
        std::replace(lat_str.begin(), lat_str.end(), ',', '.');
        std::replace(lon_str.begin(), lon_str.end(), ',', '.');
      }
      if (i >= 1 && (std::stod(lat_str) > 60 || std::stod(lon_str) > 60)) {
        return {wrong, wrong};
      }

      lat += std::stod(lat_str) / divisors[i];
      lon += std::stod(lon_str) / divisors[i];
    }
    if (type == TYPE::complex) {
      if (m[latm1_coord] == south) {
        lat *= -1;
      }
      if (m[lonm1_coord] == west) {
        lon *= -1;
      }
    }

    if (!(lat >= -90.0 && lat <= 90.0 && lon >= -180.0 && lon <= 180.0)) {
      return {wrong, wrong};
    }

    return {lat, lon};
  }
  return {wrong, wrong};
}

std::pair<double, double> regex_str::extract_first(const std::string &text) {
  return regex_str::extract_template(simple, text, first);
}
std::pair<double, double> regex_str::extract_second(const std::string &text) {
  return regex_str::extract_template(complex, text, second, {2}, {4}, 1, 3, "S",
                                     "W");
}
std::pair<double, double> regex_str::extract_third(const std::string &text) {
  return regex_str::extract_template(complex, text, third, {1, 2}, {4, 5}, 3, 6,
                                     "S", "W");
}
std::pair<double, double> regex_str::extract_fourth(const std::string &text) {
  return regex_str::extract_template(complex, text, fourth, {1, 2}, {4, 5}, 3,
                                     6, "S", "W");
}
std::pair<double, double> regex_str::extract_fourth_1(const std::string &text) {
  return regex_str::extract_template(complex, text, fourth_1, {1}, {3}, 2, 4,
                                     "S", "W");
}
std::pair<double, double> regex_str::extract_fifth(const std::string &text) {
  return regex_str::extract_template(complex, text, fifth, {2, 3, 4}, {6, 7, 8},
                                     1, 5, "S", "W");
}
std::pair<double, double> regex_str::extract_fifth_1(const std::string &text) {
  return regex_str::extract_template(complex, text, fifth_1, {2, 3}, {5, 6}, 1,
                                     4, "S", "W");
}
std::pair<double, double> regex_str::extract_fifth_2(const std::string &text) {
  return regex_str::extract_template(complex, text, fifth_2, {2}, {4}, 1, 3,
                                     "S", "W");
}
std::pair<double, double> regex_str::extract_sixth(const std::string &text) {
  return regex_str::extract_template(complex, text, sixth, {1, 2}, {4, 5}, 3, 6,
                                     "S", "W");
}
std::pair<double, double>
regex_str::extract_six_with_directions_start(const std::string &text) {
  return regex_str::extract_template(complex, text, sixth_with_directions_start,
                                     {2, 3}, {5, 6}, 1, 4, "S", "W");
}
std::pair<double, double> regex_str::extract_sixth_1(const std::string &text) {
  return regex_str::extract_template(complex, text, sixth_1, {1, 2}, {4, 5}, 3,
                                     6, "S", "W");
}
std::pair<double, double> regex_str::extract_sixth_2(const std::string &text) {
  return regex_str::extract_template(complex, text, sixth_2, {1, 2}, {4, 5}, 3,
                                     6, "\xD0\xAE", "\xD0\x97");
}
std::pair<double, double> regex_str::extract_sixth_3(const std::string &text) {
  return regex_str::extract_template(complex, text, sixth_3, {1}, {3}, 2, 4,
                                     "S", "W");
}
std::pair<double, double> regex_str::extract_seventh(const std::string &text) {
  return regex_str::extract_template(complex, text, seventh, {1, 2, 3},
                                     {5, 6, 7}, 4, 8, "S", "W");
}
std::pair<double, double>
regex_str::extract_seventh_with_quotes(const std::string &text) {
  return regex_str::extract_template(complex, text, seventh_with_quotes,
                                     {1, 2, 3}, {5, 6, 7}, 4, 8, "S", "W");
}
std::pair<double, double>
regex_str::extract_seventh_1(const std::string &text) {
  return regex_str::extract_template(complex, text, seventh_1, {1, 2, 3},
                                     {5, 6, 7}, 4, 8, "S", "W");
}
std::pair<double, double>
regex_str::extract_seventh_with_dig_quotes(const std::string &text) {
  return regex_str::extract_template(complex, text, seventh_with_dig_quotes,
                                     {1, 2, 3}, {5, 6, 7}, 4, 8, "S", "W");
}
std::pair<double, double> regex_str::extract_eighth(const std::string &text) {
  return regex_str::extract_template(complex, text, eighth, {1, 2}, {4, 5}, 3,
                                     6, "\xD1\x8E", "\xD0\xB7");
}
std::pair<double, double> regex_str::extract_eighth_1(const std::string &text) {
  return regex_str::extract_template(complex, text, eighth_1, {1, 2}, {4, 5}, 3,
                                     6, "\xD0\xAE", "\xD0\x97");
}
std::pair<double, double> regex_str::extract_nineth(const std::string &text) {
  return regex_str::extract_template(complex, text, nineth, {1, 2, 3},
                                     {5, 6, 7}, 4, 8, "\xD1\x8E", "\xD0\xB7");
}
std::pair<double, double> regex_str::extract_nineth_1(const std::string &text) {
  return regex_str::extract_template(complex, text, nineth_1, {1, 2, 3},
                                     {5, 6, 7}, 4, 8, "\xD0\xAE", "\xD0\x97");
}
std::pair<double, double> regex_str::extract_tenth(const std::string &text) {
  return regex_str::extract_template(complex, text, tenth, {1, 2, 3}, {5, 6, 7},
                                     4, 8, "S", "W");
}
std::pair<double, double> regex_str::extract_eleventh(const std::string &text) {
  return regex_str::extract_template(complex, text, eleventh, {1, 2}, {4, 5}, 3,
                                     6, "S", "W");
}
std::pair<double, double> regex_str::extract_twelve(const std::string &text) {
  return regex_str::extract_template(simple, text, twelve, {1}, {2}, 0, 0, "S",
                                     "W", true);
}
std::pair<double, double> regex_str::extract_twelve_1(const std::string &text) {
  return regex_str::extract_template(simple, text, twelve_1);
}
std::pair<double, double> regex_str::extract_thirteen(const std::string &text) {
  return regex_str::extract_template(complex, text, thirteenth, {2}, {4}, 1, 3,
                                     "S", "W");
}

std::vector<regex_str::MatchInfo>
regex_str::extract_substrings(const std::string &s) {
  std::vector<regex_str::MatchInfo> out;
  size_t pos = 0;

  while (pos < s.size()) {
    bool matched = false;

    for (size_t i = 0; i < regexs.size(); ++i) {
      const boost::regex re(regexs[i]);
      boost::smatch m;

      std::string sub = s.substr(pos);
      if (boost::regex_search(sub, m, re, boost::match_continuous)) {
        size_t start = pos + static_cast<size_t>(m[0].first - sub.begin());
        size_t end = pos + static_cast<size_t>(m[0].second - sub.begin());

        std::pair<double, double> coords = functions[i](m.str());

        if (coords.first != wrong || coords.second != wrong) {
          out.push_back({start, end, coords.first, coords.second});
        }

        pos = end;
        matched = true;
        break;
      }
    }

    if (!matched) {
      ++pos;
    }
  }

  return out;
}