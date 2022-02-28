#include "ray.hh"

#include "points/point3.hh"
#include "vectors/vector3.hh"

namespace raytracer
{
    Ray::Ray(const points::Point3 &origin, const vectors::Vector3 &direction)
        : origin_{ origin }
        , direction_{ direction.normalized() }
    {}

    Ray Ray::AtoB(const points::Point3 &origin, const points::Point3 &target)
    {
        return Ray{ origin, target - origin };
    }

    const points::Point3 &Ray::origin_get() const
    {
        return origin_;
    }

    const vectors::Vector3 &Ray::direction_get() const
    {
        return direction_;
    }

    std::ostream &operator<<(std::ostream &out, const Ray &ray)
    {
        return out << "Ray{ origin: " << ray.origin_
                   << ", direction: " << ray.direction_ << " }";
    }
} // namespace raytracer
