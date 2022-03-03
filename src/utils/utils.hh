#pragma once

#include <sstream>
#include <string>

namespace utils
{
    constexpr double EPSILON = 0.0000000001;

    template <class T>
    std::string join(const std::vector<std::shared_ptr<T>> &vec,
                     const std::string &delimiter);

    template <typename T>
    inline int signum(const T &v);
} // namespace utils

#include "utils.hxx"
