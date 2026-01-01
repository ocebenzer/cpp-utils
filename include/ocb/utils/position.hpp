#pragma once

#include <cstdint>
#include <ostream>
#include <boost/container_hash/hash.hpp>

namespace ocb {
    template<typename T = int64_t>
    struct point {
        T y;
        T x;

        point operator+() const { return *this; }
        point operator-() const { return {y, x}; }

        point &operator+=(const point &rhs) {
            y += rhs.y;
            x += rhs.x;
            return *this;
        }

        point &operator-=(const point &rhs) {
            y -= rhs.y;
            x -= rhs.x;
            return *this;
        }

        point &operator*=(const point &rhs) {
            y *= rhs.y;
            x *= rhs.x;
            return *this;
        }

        point &operator/=(const point &rhs) {
            y /= rhs.y;
            x /= rhs.x;
            return *this;
        }

        point &operator%=(const point &rhs) {
            y %= rhs.y;
            x %= rhs.x;
            return *this;
        }

        point operator+(const point &rhs) const { return {y + rhs.y, x + rhs.x}; }
        point operator-(const point &rhs) const { return {y - rhs.y, x - rhs.x}; }
        point operator*(const point &rhs) const { return {y * rhs.y, x * rhs.x}; }
        point operator/(const point &rhs) const { return {y / rhs.y, x / rhs.x}; }
        point operator%(const point &rhs) const { return {y % rhs.y, x % rhs.x}; }

        /* Comparisons */

        bool operator<(const point &rhs) const {
            return y < rhs.y || (y == rhs.y && x < rhs.x);
        }

        bool operator>(const point &rhs) const {
            return rhs < *this;
        }

        bool operator<=(const point &rhs) const {
            return !(*this > rhs);
        }

        bool operator>=(const point &rhs) const {
            return !(*this < rhs);
        }

        bool operator==(const point &rhs) const = default;

        bool operator!=(const point &rhs) const { return !(*this == rhs); }

        /* Stream Operators */

        friend std::ostream &operator<<(std::ostream &o, const point &p) {
            return o << std::format("({}, {})", p.y, p.x);
        }
    };

    template<typename T>
    point(T...) -> point<T>;
} // namespace ocb

template<typename T>
struct std::hash<ocb::point<T> > {
    std::size_t operator()(const ocb::point<T> &pos) const noexcept {
        std::size_t seed = 0;
        boost::hash_combine(seed, pos.y);
        boost::hash_combine(seed, pos.x);
        return seed;
    }
};
