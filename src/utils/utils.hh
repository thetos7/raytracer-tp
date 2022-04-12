#pragma once

#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

namespace utils
{
    constexpr double EPSILON = 0.0000000001;
    template <class T>
    std::ostream &stream_join(std::ostream &out,
                              const std::vector<std::shared_ptr<T>> &vec,
                              const std::string &delimiter);

    template <class T>
    std::string join(const std::vector<std::shared_ptr<T>> &vec,
                     const std::string &delimiter);

    template <typename T>
    inline int signum(const T &v);

    template <typename T>
    inline auto lerp(const T &a, const T &b, double factor);

    double fract(double x);

    std::ostream &compact_on(std::ostream &out);
    std::ostream &compact_off(std::ostream &out);
    bool compact_enabled(std::ostream &out);
} // namespace utils

#include "utils.hxx"
