#pragma once

#include <array>

#include "vectors/vector3.hh"
#include "points/point3.hh"

namespace vectors
{
    class RotMatrix3
    {
    public:
        std::array<std::array<double, 3>, 3> matrix;
        RotMatrix3(double xangle, double yangle, double zangle);
        static RotMatrix3 Identity();
        Vector3 operator*(const Vector3 &) const;
        points::Point3 operator*(const points::Point3 &) const;
    };
} // namespace vectors