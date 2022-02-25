#include "ray.hh"

#include "points/point3.hh"
#include "vectors/vector3.hh"

namespace raytracer
{
    Ray::Ray(points::Point3 &origin, vectors::Vector3 &direction)
        : origin_{ origin }
        , direction_{ direction }
    {}

    const points::Point3 &Ray::origin_get()
    {
        return origin_;
    }

    const vectors::Vector3 &Ray::direction_get()
    {
        return direction_;
    }
} // namespace raytracer