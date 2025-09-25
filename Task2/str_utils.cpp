#include "str_utils.h"
#include <string>

std::pair<double, double> regex_str::ExtractTemplate(
    TYPE type, const std::string &text, const char *const regex, std::vector<size_t> lat_coord,
    std::vector<size_t> lon_coord, size_t latm1_coord, size_t lonm1_coord, const char *const south,
    const char *const west, bool replace_comma) {

    boost::regex r(regex);
    boost::smatch m;
    if (boost::regex_search(text, m, r)) {

        std::array<double, 3> divisors = {1, 60.0, 3600.0};
        double lat = 0;
        double lon = 0;
        if (lat_coord.size() != lon_coord.size()) {
            return {coordinate::kWrong, coordinate::kWrong};
        }
        for (size_t i = 0; i < lat_coord.size(); ++i) {
            std::string lat_str = m[lat_coord[i]].str();
            std::string lon_str = m[lon_coord[i]].str();
            if (replace_comma) {
                std::replace(lat_str.begin(), lat_str.end(), ',', '.');
                std::replace(lon_str.begin(), lon_str.end(), ',', '.');
            }
            if (i >= 1 && (std::stod(lat_str) > 60 || std::stod(lon_str) > 60)) {
                return {coordinate::kWrong, coordinate::kWrong};
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
            return {coordinate::kWrong, coordinate::kWrong};
        }

        return {lat, lon};
    }
    return {coordinate::kWrong, coordinate::kWrong};
}

std::string coordinate::CoordinatesToString(double lat, double lon) {
    return "latitude: " + std::to_string(lat) + " longitude: " + std::to_string(lon);
}

std::string tokenizer::Concat(const std::vector<std::string> &vec) {
    std::string res;
    for (size_t i = 0; i < vec.size(); ++i) {
        res += vec[i];
        if (i + 1 != vec.size()) {
            res += " ";
        }
    }
    return res;
}

std::pair<double, double> regex_str::ExtractFirst(const std::string &text) {
    return regex_str::ExtractTemplate(simple, text, kFirst);
}
std::pair<double, double> regex_str::ExtractSecond(const std::string &text) {
    return regex_str::ExtractTemplate(complex, text, kSecond, {2}, {4}, 1, 3, "S", "W");
}
std::pair<double, double> regex_str::ExtractThird(const std::string &text) {
    return regex_str::ExtractTemplate(complex, text, kThird, {1, 2}, {4, 5}, 3, 6, "S", "W");
}
std::pair<double, double> regex_str::ExtractFourth(const std::string &text) {
    return regex_str::ExtractTemplate(complex, text, kFourth, {1, 2}, {4, 5}, 3, 6, "S", "W");
}
std::pair<double, double> regex_str::ExtractFourth1(const std::string &text) {
    return regex_str::ExtractTemplate(complex, text, kFourth1, {1}, {3}, 2, 4, "S", "W");
}
std::pair<double, double> regex_str::ExtractFifth(const std::string &text) {
    return regex_str::ExtractTemplate(complex, text, kFifth, {2, 3, 4}, {6, 7, 8}, 1, 5, "S", "W");
}
std::pair<double, double> regex_str::ExtractFifth1(const std::string &text) {
    return regex_str::ExtractTemplate(complex, text, kFifth1, {2, 3}, {5, 6}, 1, 4, "S", "W");
}
std::pair<double, double> regex_str::ExtractFifth2(const std::string &text) {
    return regex_str::ExtractTemplate(complex, text, kFifth2, {2}, {4}, 1, 3, "S", "W");
}
std::pair<double, double> regex_str::ExtractSixth(const std::string &text) {
    return regex_str::ExtractTemplate(complex, text, kSixth, {1, 2}, {4, 5}, 3, 6, "S", "W");
}
std::pair<double, double> regex_str::ExtractSixWithDirectionsStart(const std::string &text) {
    return regex_str::ExtractTemplate(complex, text, kSixthWithDirectionsStart, {2, 3}, {5, 6}, 1,
                                      4, "S", "W");
}
std::pair<double, double> regex_str::ExtractSixth1(const std::string &text) {
    return regex_str::ExtractTemplate(complex, text, kSixth1, {1, 2}, {4, 5}, 3, 6, "S", "W");
}
std::pair<double, double> regex_str::ExtractSixth2(const std::string &text) {
    return regex_str::ExtractTemplate(complex, text, kSixth2, {1, 2}, {4, 5}, 3, 6, "\xD0\xAE",
                                      "\xD0\x97");
}
std::pair<double, double> regex_str::ExtractSixth3(const std::string &text) {
    return regex_str::ExtractTemplate(complex, text, kSixth3, {1}, {3}, 2, 4, "S", "W");
}
std::pair<double, double> regex_str::ExtractSeventh(const std::string &text) {
    return regex_str::ExtractTemplate(complex, text, kSeventh, {1, 2, 3}, {5, 6, 7}, 4, 8, "S",
                                      "W");
}
std::pair<double, double> regex_str::ExtractSeventhWithQuotes(const std::string &text) {
    return regex_str::ExtractTemplate(complex, text, kSeventhWithQuotes, {1, 2, 3}, {5, 6, 7}, 4, 8,
                                      "S", "W");
}
std::pair<double, double> regex_str::ExtractSeventh1(const std::string &text) {
    return regex_str::ExtractTemplate(complex, text, kSeventh1, {1, 2, 3}, {5, 6, 7}, 4, 8, "S",
                                      "W");
}
std::pair<double, double> regex_str::ExtractSeventhWithDigQuotes(const std::string &text) {
    return regex_str::ExtractTemplate(complex, text, kSeventhWithDigQuotes, {1, 2, 3}, {5, 6, 7}, 4,
                                      8, "S", "W");
}
std::pair<double, double> regex_str::ExtractEighth(const std::string &text) {
    return regex_str::ExtractTemplate(complex, text, kEighth, {1, 2}, {4, 5}, 3, 6, "\xD1\x8E",
                                      "\xD0\xB7");
}
std::pair<double, double> regex_str::ExtractEighth1(const std::string &text) {
    return regex_str::ExtractTemplate(complex, text, kEighth1, {1, 2}, {4, 5}, 3, 6, "\xD0\xAE",
                                      "\xD0\x97");
}
std::pair<double, double> regex_str::ExtractNineth(const std::string &text) {
    return regex_str::ExtractTemplate(complex, text, kNineth, {1, 2, 3}, {5, 6, 7}, 4, 8,
                                      "\xD1\x8E", "\xD0\xB7");
}
std::pair<double, double> regex_str::ExtractNineth1(const std::string &text) {
    return regex_str::ExtractTemplate(complex, text, kNineth1, {1, 2, 3}, {5, 6, 7}, 4, 8,
                                      "\xD0\xAE", "\xD0\x97");
}
std::pair<double, double> regex_str::ExtractTenth(const std::string &text) {
    return regex_str::ExtractTemplate(complex, text, kTenth, {1, 2, 3}, {5, 6, 7}, 4, 8, "S", "W");
}
std::pair<double, double> regex_str::ExtractEleventh(const std::string &text) {
    return regex_str::ExtractTemplate(complex, text, kEleventh, {1, 2}, {4, 5}, 3, 6, "S", "W");
}
std::pair<double, double> regex_str::ExtractTwelve(const std::string &text) {
    return regex_str::ExtractTemplate(simple, text, kTwelve, {1}, {2}, 0, 0, "S", "W", true);
}
std::pair<double, double> regex_str::ExtractTwelve1(const std::string &text) {
    return regex_str::ExtractTemplate(simple, text, kTwelve1);
}
std::pair<double, double> regex_str::ExtractThirteen(const std::string &text) {
    return regex_str::ExtractTemplate(complex, text, kThirteenth, {2}, {4}, 1, 3, "S", "W");
}

std::vector<regex_str::MatchInfo> regex_str::ExtractCoordinates(const std::string &s) {
    std::vector<regex_str::MatchInfo> out;
    size_t pos = 0;

    while (pos < s.size()) {
        bool matched = false;

        for (size_t i = 0; i < kRegexs.size(); ++i) {
            const boost::regex re(kRegexs[i]);
            boost::smatch m;

            std::string sub = s.substr(pos);
            if (boost::regex_search(sub, m, re, boost::match_continuous)) {
                size_t start = pos + static_cast<size_t>(m[0].first - sub.begin());
                size_t end = pos + static_cast<size_t>(m[0].second - sub.begin());

                std::pair<double, double> coords = kFunctions[i](m.str());

                if (coords.first != coordinate::kWrong || coords.second != coordinate::kWrong) {
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

bool names::IsCoordNumber(const std::string &word) {
    bool has_digit = false;
    for (char c : word) {
        if (isdigit(c)) {
            has_digit = true;
            break;
        }
    }
    if (!has_digit) {
        return false;
    }

    if (word.find_first_of(".,") != std::string::npos) {
        return true;
    }

    if (word.find_first_of("-'\"°′″") != std::string::npos) {
        return true;
    }

    return true;
}

namespace {
std::string ToLowerUtf8(const std::string &text) {
    icu::UnicodeString u = icu::UnicodeString::fromUTF8(text);
    u.toLower();
    std::string out;
    u.toUTF8String(out);
    return out;
}
}  // namespace

bool names::IsStopword(const std::string &word) {
    std::string lower = ToLowerUtf8(word);
    return (kStopWords.find(lower) != kStopWords.end()) || IsCoordNumber(lower);
}

bool names::IsPolygonWord(const std::string &word) {
    std::string lower = ToLowerUtf8(word);
    return (kPolygons.find(lower) != kPolygons.end());
}

bool coordinate::IsWordPolygon(const std::vector<tokenizer::WordInfo> &words,
                               const std::vector<regex_str::MatchInfo> &set, size_t k_before) {
    if (set.size() <= 1) {
        return false;
    }
    size_t start = set[0].start_byte;
    size_t end = set.back().end_byte;

    size_t idx_first = 0;
    while (idx_first < words.size() && words[idx_first].end_byte < start) {
        ++idx_first;
    }

    size_t start_idx = (idx_first > k_before) ? idx_first - k_before : 0;

    for (size_t i = start_idx; i < words.size() && words[i].start_byte <= end; ++i) {
        if (names::IsPolygonWord(words[i].word)) {
            return true;
        }
    }
    return false;
}

tokenizer::Tokenizer tokenizer::PrepareSentenceTokenizer(const icu::UnicodeString &txt) {
    auto status = U_ZERO_ERROR;
    auto tok = tokenizer::Tokenizer(
        icu::BreakIterator::createSentenceInstance(icu::Locale{"ru_RU"}, status));
    if (U_FAILURE(status)) {
        std::cerr << "Ошибка создания BreakIterator" << std::endl;
        return nullptr;
    }
    tok->setText(txt);
    return std::move(tok);
}

tokenizer::Tokenizer tokenizer::PrepareWordTokenizer(const icu::UnicodeString &txt) {
    UErrorCode status = U_ZERO_ERROR;
    auto tok =
        tokenizer::Tokenizer(icu::BreakIterator::createWordInstance(icu::Locale("ru_RU"), status));
    if (U_FAILURE(status)) {
        std::cerr << "Ошибка создания BreakIterator для слов" << std::endl;
        return nullptr;
    }
    tok->setText(txt);
    return tok;
}

std::vector<std::string> tokenizer::TokenizeToSentences(const std::string &text) {
    std::vector<std::string> result;
    auto txt = icu::UnicodeString::fromUTF8(text);
    auto tok = tokenizer::PrepareSentenceTokenizer(txt);
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

std::vector<tokenizer::WordInfo> tokenizer::TokenizeToWords(const std::string &text) {
    std::vector<WordInfo> words;
    auto utext = icu::UnicodeString::fromUTF8(text);
    auto tok = tokenizer::PrepareWordTokenizer(utext);
    if (!tok) {
        return words;
    }

    int32_t start = tok->first();
    int32_t end = tok->next();
    while (end != icu::BreakIterator::DONE) {
        icu::UnicodeString substr = utext.tempSubStringBetween(start, end);
        std::string word;
        substr.toUTF8String(word);

        if (!word.empty() && word.find_first_not_of(" \t\n\r") != std::string::npos) {
            std::string before;
            utext.tempSubStringBetween(0, start).toUTF8String(before);
            std::string curr;
            substr.toUTF8String(curr);

            words.push_back({curr, before.size(), before.size() + curr.size()});
        }

        start = end;
        end = tok->next();
    }
    return words;
}

std::vector<woords_with_coords::WordsForCoord> woords_with_coords::CollectWordsAroundCoords(
    const std::vector<tokenizer::WordInfo> &words, const std::vector<regex_str::MatchInfo> &coords,
    size_t n_before) {
    std::vector<woords_with_coords::WordsForCoord> results;
    size_t word_idx = 0;

    for (const auto &coord : coords) {
        while (word_idx < words.size() && words[word_idx].end_byte <= coord.start_byte) {
            ++word_idx;
        }
        std::vector<std::string> context;
        size_t count = 0;
        for (size_t i = word_idx; i > 0 && count < n_before;) {
            const auto &w = words[--i];
            if (!names::IsStopword(w.word)) {
                context.push_back(w.word);
                ++count;
            }
        }
        std::reverse(context.begin(), context.end());
        results.push_back({coord, std::move(context)});
    }

    return results;
}

double coordinate_sets::Distance(const regex_str::MatchInfo &m1, const regex_str::MatchInfo &m2) {
    return (m1.lat - m2.lat) * (m1.lat - m2.lat) + (m1.lon - m2.lon) * (m1.lon - m2.lon);
}

double coordinate_sets::FindEps(const std::vector<regex_str::MatchInfo> &vec) {
    std::vector<double> distances;
    for (size_t i = 1; i < vec.size(); ++i) {
        distances.push_back(Distance(vec[i], vec[i - 1]));
    }

    std::sort(distances.begin(), distances.end());
    return distances[distances.size() / 2] * 1.1;
}

std::vector<std::vector<regex_str::MatchInfo>> coordinate_sets::FindSets(
    const std::vector<regex_str::MatchInfo> &vec, double sm_dist, double byte_dist) {
    std::vector<std::vector<regex_str::MatchInfo>> out;
    std::vector<regex_str::MatchInfo> cur;
    for (size_t i = 0; i < vec.size(); ++i) {

        if (i == 0 || (coordinate_sets::Distance(vec[i], vec[i - 1]) <= sm_dist &&
                       (vec[i].start_byte - vec[i - 1].end_byte < byte_dist))) {
            cur.push_back(vec[i]);
            if (i + 1 == vec.size()) {
                out.push_back(cur);
            }
        } else {
            out.push_back(cur);
            cur = {vec[i]};
        }
    }
    return out;
}

bool coordinate_sets::ClosedSequence(const std::vector<regex_str::MatchInfo> &set) {
    double eps = coordinate_sets::FindEps(set);
    return coordinate_sets::Distance(set[0], set[set.size() - 1]) < eps / 10.0;
}

std::array<std::vector<std::vector<regex_str::MatchInfo>>, 3> coordinate_sets::CalcSetInfo(

    const std::vector<tokenizer::WordInfo> &words,
    const std::vector<std::vector<regex_str::MatchInfo>> &sets) {

    std::array<std::vector<std::vector<regex_str::MatchInfo>>, 3> answer;

    for (size_t i = 0; i < sets.size(); ++i) {
        if (sets[i].size() == 1) {
            answer[POINT].push_back(std::move(sets[i]));

        } else if (ClosedSequence(sets[i]) || coordinate::IsWordPolygon(words, sets[i])) {
            answer[POLYGON].push_back(std::move(sets[i]));

        } else {
            answer[LINE].push_back(sets[i]);
        }
    }
    return answer;
}

std::string coordinate_sets::CoordinateSetToString(const std::vector<regex_str::MatchInfo> &set) {
    std::string res = "{\n";
    for (size_t i = 0; i < set.size(); ++i) {
        res += coordinate::CoordinatesToString(set[i].lat, set[i].lon) + ";\n";
    }
    res += "}\n";
    return res;
}

std::string coordinate_sets::ArrOfCoordinateSetsToString(
    const std::vector<std::vector<regex_str::MatchInfo>> &arr) {
    std::string res = "{\n";
    for (size_t i = 0; i < arr.size(); ++i) {
        res += coordinate_sets::CoordinateSetToString(arr[i]);
    }
    res += "}\n";
    return res;
}
