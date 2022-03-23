#pragma once

#include <iosfwd>
#include <vector>

#include "vectors/fwd.hh"

namespace points
{
    class Point3i
    {
    public:
        int x;
        int y;
        int z;

        static Point3i origin();
        static Point3i from_vector(const std::vector<int> &);

        constexpr Point3i()
            : Point3i{ 0, 0, 0 }
        {}

        constexpr Point3i(int x, int y, int z)
            : x{ x }
            , y{ y }
            , z{ z }
        {}

        Point3i &operator+=(const vectors::Vector3i &vect);
        Point3i &operator-=(const vectors::Vector3i &vect);

        Point3i operator+(const vectors::Vector3i &vect) const;
        Point3i operator-(const vectors::Vector3i &vect) const;
        vectors::Vector3i operator-(const Point3i &other) const;
    };

    std::ostream &operator<<(std::ostream &out, const Point3i &point);
} // namespace points
