#ifndef HASH_UTILS_H
#define HASH_UTILS_H

#include <functional>
#include <utility>

namespace std {
    template <>
    struct hash<std::pair<int, int>> {
        size_t operator()(const std::pair<int, int>& p) const noexcept {
            return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
        }
    };
}

#endif