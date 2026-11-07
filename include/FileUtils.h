// Purpose: shared Milestone 1 input validation. Author: Codex (AI assistance).
#ifndef FILE_UTILS_H
#define FILE_UTILS_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
namespace Input {
// Remove outer whitespace, including Windows carriage returns.
inline std::string trim(const std::string& text) {
    const auto first = text.find_first_not_of(" \t\r\n\f\v");
    if (first == std::string::npos) return "";
    return text.substr(first, text.find_last_not_of(" \t\r\n\f\v") - first + 1);
}
// ASCII case folding preserves internal spaces.
inline std::string upper(std::string text) {
    for (char& c : text) if (c >= 'a' && c <= 'z') c -= 'a' - 'A';
    return text;
}
// Normalize comparison keys while keeping display spelling elsewhere.
inline std::string key(const std::string& text) { return upper(trim(text)); }
// Accept directories with or without a trailing slash.
inline std::string path(const std::string& directory, const std::string& file) {
    return directory + (directory.empty() || directory.back() == '/' ? "" : "/") + file;
}
// Split fields, retaining empty fields and trailing delimiters.
inline std::vector<std::string> fields(const std::string& line) {
    std::vector<std::string> result;
    std::size_t start = 0, end;
    while ((end = line.find('|', start)) != std::string::npos) {
        result.push_back(trim(line.substr(start, end - start)));
        start = end + 1;
    }
    result.push_back(trim(line.substr(start)));
    return result;
}
// Check the count and every required field.
inline bool validFields(const std::vector<std::string>& values, std::size_t count) {
    if (values.size() != count) return false;
    for (const auto& value : values) if (value.empty()) return false;
    return true;
}
// Visit records; loader returns an empty string or a rejection reason.
template<class Loader>
void load(const std::string& directory, const std::string& file, Loader loader,
          bool summary = true) {
    const std::string filename = path(directory, file);
    std::ifstream input(filename);
    std::size_t accepted = 0, rejected = 0, number = 0;
    if (!input) std::cout << "Error: cannot open " << filename << '\n';
    std::string line;
    while (std::getline(input, line)) {
        ++number;
        line = trim(line);
        if (line.empty() || line.front() == '#') continue;
        const std::string reason = loader(fields(line));
        if (reason.empty()) ++accepted;
        else {
            ++rejected;
            std::cout << "Warning: " << file << ':' << number << ": " << reason << '\n';
        }
    }
    std::cout << file << ": " << accepted << " accepted, " << rejected << " rejected";
    if (summary) std::cout << '\n';
}
}
#endif
