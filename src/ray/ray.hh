#pragma once

#include "points/point3.hh"
#include "vectors/vector3.hh"

namespace raytracer
{
    class Ray
    {
    public:
        Ray(points::Point3 &origin, vectors::Vector3 &direction);

        const points::Point3 &origin_get();
        const vectors::Vector3 &direction_get();
    private:
        points::Point3 &origin_;
        vectors::Vector3 &direction_;
    };
} // namespace raytracer