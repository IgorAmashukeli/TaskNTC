
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <thread>
#include <unordered_set>
#include <zmq.hpp>

bool IsReceived(zmq::socket_t &is_received_sock) {
    zmq::message_t message;
    auto result = is_received_sock.recv(message, zmq::recv_flags::dontwait);

    return result.has_value();
}

void Send(std::string str) {
    zmq::context_t context(1);

    zmq::socket_t publisher(context, zmq::socket_type::pub);
    zmq::socket_t is_received_sock(context, zmq::socket_type::pull);
    is_received_sock.connect("tcp://localhost:5555");

    publisher.bind("tcp://*:5556");

    while (true) {

        publisher.send(zmq::buffer(str), zmq::send_flags::none);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (IsReceived(is_received_sock)) {
            break;
        }
    }
}

bool IsAllDigits(const std::string &s) {
    if (s.empty()) {
        return false;
    }
    for (unsigned char c : s) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

template <typename T>
std::vector<std::string> Split(T &&str, const std::string &delimiter) {
    std::string s = std::forward<T>(str);
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
}

int StringToInt(const std::string &str) {
    try {
        size_t pos = 0;
        int val = std::stoi(str, &pos);
        if (pos != str.size()) {
            return -1;
        }
        return val;
    } catch (const std::invalid_argument &) {
        return -1;
    } catch (const std::out_of_range &) {
        return -1;
    }
}

bool IsLeapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

bool IsValidDay(int day, int month, int year, std::string_view line) {
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 ||
        month == 12) {
        if (!((day > 0) && (day <= 31))) {
            std::cerr << "неверный день: " << line << "\n";
        }

        return (day > 0) && (day <= 31);
    } else if ((month == 4) || (month == 6) || (month == 9) || (month == 11)) {
        if (!((day > 0) && (day <= 30))) {
            std::cerr << "неверный день: " << line << "\n";
        }

        return (day > 0) && (day <= 30);
    } else if ((month == 2) && IsLeapYear(year)) {
        if (!((day > 0) && (day <= 29))) {
            std::cerr << "неверный день: " << line << "\n";
        }

        return (day > 0) && (day <= 29);
    } else if (month == 2) {
        if (!((day > 0) && (day <= 28))) {
            std::cerr << "неверный день: " << line << "\n";
        }

        return (day > 0) && (day <= 28);
    } else {
        std::cerr << "неверный день: " << line << "\n";
        return false;
    }
}

bool HasLeadingOrTrailingSpace(const std::string &s) {
    return !s.empty() && (std::isspace(static_cast<unsigned char>(s.front())) ||
                          std::isspace(static_cast<unsigned char>(s.back())));
}

bool IsValidMonth(int month, std::string_view line) {
    if (!(month > 0 && month <= 12)) {
        std::cerr << "неверный месяц: " << line << "\n";
    }
    return month > 0 && month <= 12;
}

bool IsValidYear(int year, std::string_view line) {
    if (!(year > 0)) {
        std::cerr << "неверный год: " << line << "\n";
    }

    return (year > 0);
}

bool IsValidDate(const std::string &date, std::string_view line) {
    std::vector<std::string> date_vec = Split(date, ".");
    if (date_vec.size() != 3) {
        std::cerr << "неверное число чисел в дате: " << line << "\n";
        return false;
    }

    if (HasLeadingOrTrailingSpace(date_vec[0]) || HasLeadingOrTrailingSpace(date_vec[1]) ||
        HasLeadingOrTrailingSpace(date_vec[2])) {
        std::cerr << "лишние пробелы в дате: " << line << "\n";
        return false;
    }

    if ((date_vec[0].size() != 2) || (date_vec[1].size() != 2) || (date_vec[2].size() != 4)) {
        std::cerr << "неверный формат даты (не dd.mm.yyyy): " << line << "\n";
        return false;
    }

    if (!IsAllDigits(date_vec[0]) || !IsAllDigits(date_vec[1]) || !IsAllDigits(date_vec[2])) {
        std::cerr << "найдены не цифры в дате: " << line << "\n";
        return false;
    }

    int year = StringToInt(date_vec[2]);
    int month = StringToInt(date_vec[1]);
    int day = StringToInt(date_vec[0]);

    return IsValidYear(year, line) && IsValidMonth(month, line) &&
           IsValidDay(day, month, year, line);
}

bool IsValid(const std::vector<std::string> &student_data, std::string_view line) {
    if (student_data.size() != 4) {
        std::cerr << "неверное число слов в строке: " << line << "\n";
        return false;
    }

    if (!IsValidDate(student_data[3], line)) {
        return false;
    }

    // имя и отчество (фамилия) не проверяются, могут быть любыми

    return true;
}

std::unordered_set<std::string> GetListFromFile(const std::string &file_name) {
    std::unordered_set<std::string> answer;
    std::ifstream input_file(file_name);

    if (!input_file.is_open()) {
        return {};
    }

    std::string line;
    while (std::getline(input_file, line)) {
        std::vector<std::string> student_data = Split(line, " ");
        if (!IsValid(student_data, line)) {
            continue;
        } else {

            answer.insert(student_data[1] + " " + student_data[2] + " " + student_data[3]);
        }
    }

    input_file.close();

    return answer;
}

std::unordered_set<std::string> UnionSets(std::unordered_set<std::string> a,
                                          std::unordered_set<std::string> b) {
    auto &big = (a.size() >= b.size()) ? a : b;
    auto &small = (a.size() >= b.size()) ? b : a;

    big.reserve(big.size() + small.size());
    big.insert(small.begin(), small.end());

    return big;
}

std::string GetMergedList() {
    std::unordered_set<std::string> list1 = GetListFromFile("student_file_1.txt");
    std::unordered_set<std::string> list2 = GetListFromFile("student_file_2.txt");
    std::unordered_set<std::string> list = UnionSets(std::move(list1), std::move(list2));

    std::string result;

    size_t i = 1;

    for (const auto &str : list) {
        result += str;
        result += "\n";
        ++i;
    }

    return result;
}

void ServerWork() {
    std::string result = GetMergedList();
    std::thread send_thread(Send, std::move(result));
    send_thread.join();
}

int main() {
    ServerWork();
}
