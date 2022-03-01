#pragma once

#include <memory>
#include <ostream>

#include "objects/object.hh"
#include "points/point3.hh"
#include "ray/ray.hh"

namespace raytracer
{
    namespace objects
    {
        class Object;
    } // namespace objects

    class Intersection
    {
    public:
        using ObjectPtr = const objects::Object *;

        Intersection(const Ray ray, const double t, const double u,
                     const double v, ObjectPtr object);

        /** Original ray */
        Ray ray;
        /** Object UV coordinates (for texture mapping) */
        double u;
        double v;
        /** Ray parameter ('distance') */
        double t;
        /** Intersected object */
        ObjectPtr object;
    };

    std::ostream &operator<<(std::ostream &out,
                             const Intersection &intersection);

} // namespace raytracer
