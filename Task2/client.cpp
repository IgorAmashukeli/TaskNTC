#include <cpr/cpr.h>
#include <fstream>
#include <iostream>
#include <sstream>

std::string ReadText() {
    std::ifstream input_file("text.txt");

    std::stringstream buffer;
    buffer << input_file.rdbuf();
    return buffer.str();
}

std::string Escape(std::string_view text) {
    std::string out;
    for (char ch : text) {
        switch (ch) {
            case '\"':
                out += "\\\"";
                break;
            case '\\':
                out += "\\\\";
                break;
            case '\b':
                out += "\\b";
                break;
            case '\f':
                out += "\\f";
                break;
            case '\n':
                out += "\\n";
                break;
            case '\r':
                out += "\\r";
                break;
            case '\t':
                out += "\\t";
                break;
            default:
                out += ch;
                break;
        }
    }
    return out;
}

std::string CreateBody(std::string_view text) {
    std::string body;
    body.reserve(9 + text.size() + 2);
    body.append("{\"text\":\"");
    body.append(Escape(text));
    body.append("\"}");
    return body;
}

void ClientWork() {
    std::string text = ReadText();

    auto r = cpr::Post(cpr::Url{"http://localhost:8080/process_coordinates"},
                       cpr::Body{CreateBody(text)});
    std::cout << r.text << "\n";
}

int main() {
    ClientWork();
}