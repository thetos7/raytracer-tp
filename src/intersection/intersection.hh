#pragma once

#include <iosfwd>
#include <memory>

#include "objects/fwd.hh"
#include "points/fwd.hh"
#include "ray/ray.hh"
#include "scene/fwd.hh"
#include "vectors/fwd.hh"

namespace raytracer
{

    class Intersection
    {
    public:
        using ObjectPtr = const objects::Object *;
        using StoragePtr = std::shared_ptr<void>;

        Intersection(const Intersection &other);
        Intersection(const Ray ray, const double t, const double u,
                     const double v, ObjectPtr object, StoragePtr storage = nullptr);

        /** Original ray */
        Ray ray;
        /** Object UV coordinates (for texture mapping) */
        double u;
        double v;
        /** Ray parameter ('distance') */
        double t;
        /** Intersected object */
        ObjectPtr object;

        /** Custom object-specific storage space owned and managed by the intersection */
        StoragePtr storage;

        /** Scene in which the intersection occured */
        const Scene *scene;

        points::Point3 intersection_point() const;
        vectors::Vector3 object_normal() const;
        vectors::Vector3 normal() const;
    };

    std::ostream &operator<<(std::ostream &out,
                             const Intersection &intersection);

} // namespace raytracer
