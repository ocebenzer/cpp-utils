#pragma once

#include <algorithm>
#include <array>
#include <functional>
#include <ranges>
#include <ostream>
#include <boost/functional/hash.hpp>

namespace ocb {
    template<typename T, std::size_t N>
    struct vector : std::array<T, N> {
        /* Scalar Operations */

        vector operator+() const { return *this; }
        vector operator-() const { return copy_transform_unary_op(std::negate()); }

        vector &operator+=(const T &rhs) { return transform_unary_op([&rhs](auto &lhs) { lhs += rhs; }); }
        vector &operator-=(const T &rhs) { return transform_unary_op([&rhs](auto &lhs) { lhs -= rhs; }); }
        vector &operator*=(const T &rhs) { return transform_unary_op([&rhs](auto &lhs) { lhs *= rhs; }); }
        vector &operator/=(const T &rhs) { return transform_unary_op([&rhs](auto &lhs) { lhs /= rhs; }); }
        vector &operator%=(const T &rhs) { return transform_unary_op([&rhs](auto &lhs) { lhs %= rhs; }); }

        vector operator+(const T &rhs) const { return copy_transform_unary_op([&rhs](auto &lhs) { lhs += rhs; }); }
        vector operator-(const T &rhs) const { return copy_transform_unary_op([&rhs](auto &lhs) { lhs -= rhs; }); }
        vector operator*(const T &rhs) const { return copy_transform_unary_op([&rhs](auto &lhs) { lhs *= rhs; }); }
        vector operator/(const T &rhs) const { return copy_transform_unary_op([&rhs](auto &lhs) { lhs /= rhs; }); }
        vector operator%(const T &rhs) const { return copy_transform_unary_op([&rhs](auto &lhs) { lhs %= rhs; }); }

        /* Vector Operations */

        vector &operator+=(const vector &rhs) { return transform_binary_op(rhs, std::plus()); }
        vector &operator-=(const vector &rhs) { return transform_binary_op(rhs, std::minus()); }
        vector &operator*=(const vector &rhs) { return transform_binary_op(rhs, std::multiplies()); }
        vector &operator/=(const vector &rhs) { return transform_binary_op(rhs, std::divides()); }
        vector &operator%=(const vector &rhs) { return transform_binary_op(rhs, std::modulus()); }

        vector operator+(const vector &rhs) const { return copy_transform_binary_op(rhs, std::plus()); }
        vector operator-(const vector &rhs) const { return copy_transform_binary_op(rhs, std::minus()); }
        vector operator*(const vector &rhs) const { return copy_transform_binary_op(rhs, std::multiplies()); }
        vector operator/(const vector &rhs) const { return copy_transform_binary_op(rhs, std::divides()); }
        vector operator%(const vector &rhs) const { return copy_transform_binary_op(rhs, std::modulus()); }

        /* Comparisons */

        bool operator<(const vector &rhs) const {
            for (const auto &[left, right]
                 : std::views::zip(*this, rhs)
                   | std::views::drop_while([](const auto &p) { return std::apply(std::equal_to(), p); })) {
                return left < right;
            }
            return false;
        }

        bool operator>(const vector &rhs) const { return rhs < *this; }
        bool operator<=(const vector &rhs) const { return !(*this > rhs); }
        bool operator>=(const vector &rhs) const { return !(*this < rhs); }

        bool operator==(const vector &rhs) const {
            return std::ranges::all_of(std::views::zip(*this, rhs),
                                       [](const auto &p) { return std::apply(std::equal_to(), p); });
        }

        bool operator!=(const vector &rhs) const { return !(*this == rhs); }

        /* Stream Operators */

        friend std::ostream &operator<<(std::ostream &o, const vector &v) {
            o << "[";
            if (!v.empty()) {
                o << v.front();
                for (const auto &e: std::ranges::subrange(v.begin() + 1, v.end())) {
                    o << ", " << e;
                }
            }
            return o << "]";
        }

    private:
        vector &transform_unary_op(const auto &op) {
            std::ranges::transform(*this, this->begin(), op);
            return *this;
        }

        vector copy_transform_unary_op(const auto &op) const {
            vector copy{};
            std::ranges::transform(*this, copy.begin(), op);
            return copy;
        }

        vector &transform_binary_op(const vector &rhs, const auto &op) {
            std::ranges::transform(*this, rhs, this->begin(), op);
            return *this;
        }

        vector copy_transform_binary_op(const vector &rhs, const auto &op) const {
            vector copy{};
            std::ranges::transform(*this, rhs, copy.begin(), op);
            return copy;
        }
    };

    template<typename T, typename... Ts>
    vector(T, Ts...) -> vector<T, 1 + sizeof...(Ts)>;

    template<typename T, std::size_t N = 2>
    using vector2 = vector<T, N>;

    template<typename T, std::size_t N = 3>
    using vector3 = vector<T, N>;
} // namespace ocb

template<typename T, std::size_t N>
struct std::hash<ocb::vector<T, N> > {
    std::size_t operator()(const ocb::vector<T, N> data) const {
        return boost::hash_range(data.begin(), data.end());
    }
};
