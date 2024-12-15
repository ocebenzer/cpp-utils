#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem>
#include <regex>

#include <bigint/bigint.hpp>

namespace ocb {
    // returns file content as a list of lines
    constexpr auto read_lines = [](const auto &file_path) {
        std::vector<std::string> lines;

        std::ifstream file{file_path};
        if (!file.is_open()) {
            std::cerr << "File " << file_path << " could not be opened!" << std::endl;
            std::cerr << "Hint: pwd is " << absolute(std::filesystem::current_path()) << std::endl;
            exit(1);
        }

        for (std::string line; std::getline(file, line);) {
            lines.emplace_back(line);
        }

        return lines;
    };

    // returns all substrings that match with regex, similar to global flag
    constexpr auto find_all = [](const auto &string, const std::regex &regex) {
        std::vector<std::string> matches;
        std::smatch results;

        for (auto line_iter = string.begin();
             std::regex_search(line_iter, string.end(), results, regex);
             line_iter = results[0].second) {
            matches.push_back(results[0]);
        }

        return matches;
    };

    constexpr auto find_pow_of_2 = [](const auto &pow) {
        const auto find_pow_of_2_impl = [](const auto &pow, const auto &find_pow_of_2_ref) {
            if (pow < 64) {
                int64_t ll;
                std::stringstream ss{pow.to_string()};
                ss >> ll;
                return BigInt{ll};
            }

            const BigInt half_pow{find_pow_of_2_ref(pow / 2, find_pow_of_2_ref)};

            if (pow % 2 == 0) {
                return half_pow * half_pow;
            }

            return half_pow * half_pow * 2;
        };

        return find_pow_of_2_impl(pow, find_pow_of_2_impl);
    };

    constexpr auto print_list = [](const auto &list, const std::string &end = "\n") {
        for (const auto &e: list) {
            std::cout << e << " ";
        }
        std::cout << end;
    };
} // namespace ocb::utils
