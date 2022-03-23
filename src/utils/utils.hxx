#pragma once

#include "utils.hh"

namespace utils
{

    template <class T>
    std::ostream &stream_join(std::ostream &out,
                              const std::vector<std::shared_ptr<T>> &vec,
                              const std::string &delimiter)
    {
        if (vec.size() == 0)
        {
            return out;
        }

        auto it = vec.begin();
        while (true)
        {
            out << **it;
            if (++it != vec.end())
            {
                out << delimiter;
            }
            else
            {
                break;
            }
        }
        return out;
    }

    template <class T>
    std::string join(const std::vector<std::shared_ptr<T>> &vec,
                     const std::string &delimiter)
    {
        if (vec.size() == 0)
        {
            return "";
        }
        std::ostringstream oss;
        auto it = vec.begin();
        while (true)
        {
            oss << **it;
            if (++it != vec.end())
            {
                oss << delimiter;
            }
            else
            {
                break;
            }
        }
        return oss.str();
    }

    template <typename T>
    inline int signum(const T &value)
    {
        return (T(0) < value) - (value < T(0));
    }

    template <typename T>
    inline auto lerp(const T &a, const T &b, double factor)
    {
        return a * factor + b * (1 - factor);
    }
} // namespace utils
