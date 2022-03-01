#pragma once

#include <sstream>
#include <string>

namespace utils
{
    template <class T>
    std::string join(const std::vector<std::shared_ptr<T>> &vec,
                     const std::string &delimiter);

    template <typename T>
    inline int signum(const T &v);
} // namespace utils

#include "utils.hxx"
