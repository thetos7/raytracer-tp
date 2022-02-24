#pragma once
#include <ostream>

#include "vectors/vector3.hh"

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

        Point3 operator+(const vectors::Vector3 &vect);
        Point3 operator-(const vectors::Vector3 &vect);
    };

    std::ostream &operator<<(const std::ostream &out, Point3 &point);
} // namespace points