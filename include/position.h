#pragma once

#include <string>

namespace ocb {

struct Position {
    int64_t row;
    int64_t col;

    bool operator==(const Position&) const = default;

    auto operator<(const Position& rhs) const -> bool;
    auto operator+=(const Position& rhs) -> Position&;
};

} // namespace ocb

template <>
struct std::hash<ocb::Position> {
    std::size_t operator()(const ocb::Position& pos) const noexcept {
        const auto str = std::to_string(pos.row) + std::to_string(pos.col);
        return std::hash<std::string>()(str);
    }
};
