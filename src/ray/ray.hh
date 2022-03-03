#pragma once

#include <iosfwd>

#include "points/point3.hh"
#include "vectors/vector3.hh"

namespace raytracer
{
    class Ray
    {
    public:
        Ray(const points::Point3 &origin, const vectors::Vector3 &direction);

        static Ray AtoB(const points::Point3 &origin,
                        const points::Point3 &target);

        points::Point3 origin;
        vectors::Vector3 direction;

    private:
        friend std::ostream &operator<<(std::ostream &out, const Ray &ray);
    };

    std::ostream &operator<<(std::ostream &out, const Ray &ray);
} // namespace raytracer
