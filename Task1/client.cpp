
#include <future>
#include <iostream>
#include <sstream>
#include <thread>
#include <zmq.hpp>

void SendBack(zmq::socket_t &send_back_sock) {
    send_back_sock.send(zmq::buffer("finished"), zmq::send_flags::none);
}

void Receive(std::promise<std::string> prom) {
    zmq::context_t context(1);
    zmq::socket_t subscriber(context, ZMQ_SUB);

    subscriber.connect("tcp://localhost:5556");
    subscriber.set(zmq::sockopt::subscribe, "");

    zmq::socket_t sender(context, zmq::socket_type::push);
    sender.bind("tcp://*:5555");

    std::string answer;

    while (true) {
        zmq::message_t message;
        auto res = subscriber.recv(message, zmq::recv_flags::none);
        answer = std::string(static_cast<char *>(message.data()), message.size());
        if (res) {
            prom.set_value(answer);
            SendBack(sender);
            break;
        }
    }
}

bool Comparator(const std::vector<std::string> &a, const std::vector<std::string> &b) {
    return std::tie(a[1], a[0]) < std::tie(b[1], b[0]);
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

// Это закомментированный код проверки корректности полученных клиентом данных
// Согласно условию самой задачи, это не требуется
// Более того, проверка на сервере уже гарантирует корректность данных
// Однако, если это нужно (так как написано в начале перед заданиями), то можно
// и расскоментировать
/*
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
    if (student_data.size() != 3) {
        std::cerr << "неверное число слов в строке: " << line << "\n";
        return false;
    }

    if (!IsValidDate(student_data[2], line)) {
        return false;
    }

    // имя и отчество (фамилия) не проверяются, могут быть любыми

    return true;
}
*/

std::vector<std::vector<std::string>> SortStudentList(const std::string &inp_list) {
    std::istringstream iss(inp_list);
    std::string line;

    std::vector<std::vector<std::string>> data;
    while (std::getline(iss, line)) {
        std::vector<std::string> tokens = Split(line, " ");

        /**
        if (!isValid(tokens, line)) {
          continue;
        }
        */

        data.push_back(tokens);
    }

    std::sort(data.begin(), data.end(), Comparator);

    return data;
}

void ShowOutput(const std::vector<std::vector<std::string>> &a) {
    for (const auto &vec : a) {
        std::cout << vec[0] << " " << vec[1] << " " << vec[2] << "\n";
    }
}

void ClientWork() {
    std::promise<std::string> prom;
    std::future<std::string> fut = prom.get_future();
    std::thread receive_thread(Receive, std::move(prom));
    auto res = fut.get();
    auto ans = SortStudentList(res);
    ShowOutput(ans);
    receive_thread.join();
}

int main() {
    ClientWork();
}