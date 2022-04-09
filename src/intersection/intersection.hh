#pragma once

#include <iosfwd>
#include <memory>

#include "objects/fwd.hh"
#include "points/fwd.hh"
#include "ray/ray.hh"
#include "scene/fwd.hh"
#include "vectors/fwd.hh"
#include "vectors/vector2.hh"

namespace raytracer
{

    class Intersection
    {
        using Vector2 = vectors::Vector2;
        using Vector3 = vectors::Vector3;

    public:
        using ObjectPtr = const objects::Object *;
        using StoragePtr = std::shared_ptr<void>;

        Intersection();
        Intersection(const Intersection &other);
        Intersection(const Ray ray, const double t, const Vector2 &uv,
                     ObjectPtr object, StoragePtr storage = nullptr);

        /** Original ray */
        Ray ray;
        /** Object UV coordinates (for texture mapping) */
        Vector2 uv;
        /** Ray parameter ('distance') */
        double t;
        /** Intersected object */
        ObjectPtr object;

        /** Custom object-specific storage space owned and managed by the
         * intersection */
        StoragePtr storage;

        /** Scene in which the intersection occured */
        const Scene *scene;

        points::Point3 intersection_point() const;
        Vector3 object_normal() const;
        Vector3 normal() const;
    };

    std::ostream &operator<<(std::ostream &out,
                             const Intersection &intersection);

} // namespace raytracer
