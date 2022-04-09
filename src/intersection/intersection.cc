#include "intersection.hh"

#include <ostream>

#include "objects/object.hh"
#include "points/point3.hh"
#include "ray/ray.hh"
#include "utils/utils.hh"
#include "vectors/vector2.hh"
#include "vectors/vector3.hh"

namespace raytracer
{
    using vectors::Vector2;
    using ObjectPtr = Intersection::ObjectPtr;

    Intersection::Intersection()
        : Intersection(Ray(points::Point3::origin(), Vector3::all(0)), 0,
                       Vector2::all(0), nullptr)
    {}

    Intersection::Intersection(const Ray ray, const double t, const Vector2 &uv,
                               ObjectPtr object, StoragePtr storage)
        : ray{ ray }
        , uv{ uv }
        , object{ object }
        , t{ t }
        , storage{ storage }
    {}

    Intersection::Intersection(const Intersection &other)
        : Intersection{ other.ray, other.t, other.uv, other.object,
                        other.storage }
    {
        scene = other.scene;
    }

    points::Point3 Intersection::intersection_point() const
    {
        return ray.origin + ray.direction * t;
    }

    vectors::Vector3 Intersection::object_normal() const
    {
        return object->get_normal(*this);
    }

    vectors::Vector3 Intersection::normal() const
    {
        return object_normal();
    }

    std::ostream &operator<<(std::ostream &out,
                             const Intersection &intersection)
    {
        return out << "Intersection{ ray: " << intersection.ray
                   << ", uv: " << intersection.uv
                   << ", object: " << *intersection.object
                   << ", t: " << intersection.t << " }";
    }
} // namespace raytracer
