#pragma once

#include "points/point3.hh"
#include "vectors/vector3.hh"

namespace raytracer
{
    class Ray
    {
    public:
        Ray(const points::Point3 &origin, const vectors::Vector3 &direction);

        static Ray AtoB(const points::Point3 &origin, const points::Point3 &target);

        const points::Point3 &origin_get() const;
        const vectors::Vector3 &direction_get() const;

    private:
        points::Point3 origin_;
        vectors::Vector3 direction_;
    };
} // namespace raytracer
