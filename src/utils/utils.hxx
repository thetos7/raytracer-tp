#pragma once

#include "utils.hh"

namespace utils
{
    template <class T>
    std::string join(const std::vector<std::shared_ptr<T>> &vec,
                     const std::string &delimiter)
    {
        std::ostringstream oss;
        for (auto it = vec.begin(); it != vec.end(); ++it)
        {
            oss << **it;
            if (it != vec.end() - 1)
            {
                oss << delimiter;
            }
        }
        return oss.str();
    }

    template <typename T>
    inline int signum(const T &value)
    {
        return (T(0) < value) - (value < T(0));
    }
} // namespace utils
