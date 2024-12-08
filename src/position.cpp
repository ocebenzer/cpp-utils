#include "utils/position.hpp"

namespace ocb {

auto Position::operator<(const Position& rhs) const -> bool {
    return row < rhs.row || (row == rhs.row && col < rhs.col);
}

auto Position::operator+=(const Position& rhs) -> Position& {
    row += rhs.row;
    col += rhs.col;
    return *this;
}

} // namespace ocb