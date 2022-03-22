#pragma once

#include <iosfwd>
#include <vector>

#include "vectors/fwd.hh"

namespace points
{
    class Point3
    {
    public:
        double x;
        double y;
        double z;

        static Point3 origin();
        static Point3 from_vector(const std::vector<double> &);

        constexpr Point3()
            : Point3{ 0, 0, 0 }
        {}

        constexpr Point3(double x, double y, double z)
            : x{ x }
            , y{ y }
            , z{ z }
        {}

        Point3 &operator+=(const vectors::Vector3 &vect);
        Point3 &operator-=(const vectors::Vector3 &vect);

        Point3 operator+(const vectors::Vector3 &vect) const;
        Point3 operator-(const vectors::Vector3 &vect) const;
        vectors::Vector3 operator-(const Point3 &other) const;
    };

    std::ostream &operator<<(std::ostream &out, const Point3 &point);
} // namespace points
