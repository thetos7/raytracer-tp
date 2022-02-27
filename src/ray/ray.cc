#include "ray.hh"

#include "points/point3.hh"
#include "vectors/vector3.hh"

namespace raytracer
{
    Ray::Ray(points::Point3 &origin, const vectors::Vector3 &direction)
        : origin_{ origin }
        , direction_{ direction.normalized() }
    {}

    const points::Point3 &Ray::origin_get() const
    {
        return origin_;
    }

    const vectors::Vector3 &Ray::direction_get() const
    {
        return direction_;
    }
} // namespace raytracer
