#pragma once

#include <ostream>

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

        Point3(double x, double y, double z);

        Point3 &operator+=(const vectors::Vector3 &vect);
        Point3 &operator-=(const vectors::Vector3 &vect);

        Point3 operator+(const vectors::Vector3 &vect) const;
        Point3 operator-(const vectors::Vector3 &vect) const;
        vectors::Vector3 operator-(const Point3 &other) const;
    };

    std::ostream &operator<<(std::ostream &out, const Point3 &point);
} // namespace points
