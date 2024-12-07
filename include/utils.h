#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>
#include <regex>

namespace ocb {

// returns file content as a list of lines
const auto read_lines = [] (const auto& file_path) {
    std::vector<std::string> lines;

    std::ifstream file{file_path};
    if (!file.is_open()) {
        std::cerr << "File " << file_path << " could not be opened!" << std::endl;
        std::cerr << "Hint: pwd is " << absolute(std::filesystem::current_path()) << std::endl;
        exit(1);
    }

    for (std::string line; std::getline(file, line); ) {
        lines.push_back(std::string(line));
    }

    return lines;
};

// returns all substrings that match with regex, similar to global flag
const auto find_all = [] (const auto& string, const std::regex& regex) {
    std::vector<std::string> matches;
    std::smatch results;

    for (auto line_iter = string.begin();
        std::regex_search(line_iter, string.end(), results, regex);
        line_iter = results[0].second) {
            matches.push_back(results[0]);
        }

    return matches;
};

} // namespace ocb::utils