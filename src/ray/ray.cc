#include "ray.hh"

#include <ostream>

#include "points/point3.hh"
#include "vectors/vector3.hh"

namespace raytracer
{
    Ray::Ray(const points::Point3 &origin, const vectors::Vector3 &direction)
        : origin{ origin }
        , direction{ direction.normalized() }
    {}

    Ray Ray::AtoB(const points::Point3 &origin, const points::Point3 &target)
    {
        return Ray{ origin, target - origin };
    }

    std::ostream &operator<<(std::ostream &out, const Ray &ray)
    {
        return out << "Ray{ origin: " << ray.origin
                   << ", direction: " << ray.direction << " }";
    }
} // namespace raytracer
