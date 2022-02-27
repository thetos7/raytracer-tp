#pragma once

#include <memory>

#include "objects/object.hh"
#include "points/point3.hh"
#include "ray/ray.hh"

namespace raytracer
{
    class Intersection
    {
    public:
        using ObjectPtr = const Object *;

        Intersection(const Ray ray, const double t, const double u,
                     const double v, ObjectPtr object);

        /** Original ray */
        const Ray ray;
        /** Object UV coordinates (for texture mapping) */
        const double u;
        const double v;
        /** Ray parameter ('distance') */
        const double t;
        /** Intersected object */
        ObjectPtr object;
    };
} // namespace raytracer
