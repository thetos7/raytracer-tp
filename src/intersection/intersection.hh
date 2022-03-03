#pragma once

#include <memory>
#include <ostream>

#include "points/fwd.hh"
#include "ray/ray.hh"
#include "vectors/fwd.hh"

namespace raytracer
{
    class Scene;

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

        /** Scene in which the intersection occured */
        const Scene *scene;

        points::Point3 intersection_point() const;
        vectors::Vector3 object_normal() const;
        vectors::Vector3 normal() const;
    };

    std::ostream &operator<<(std::ostream &out,
                             const Intersection &intersection);

} // namespace raytracer
