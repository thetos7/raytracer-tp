#include "sphere.hh"

#include <cmath>
#include <iostream>
#include <optional>

#include "object.hh"
#include "points/point3.hh"
#include "vectors/vector3.hh"

namespace raytracer
{
    Sphere::Sphere(const points::Point3 &center, double radius,
                   Object::MaterialPtr material)
        : Object{ material }
        , center_{ center }
        , radius_{ radius }
    {}

    std::optional<Intersection> Sphere::intersects_ray(const Ray &ray)
    {
        auto originToCenter = center_ - ray.origin_get();

        auto proj = originToCenter.dot(ray.direction_get());

        auto distCenter = std::sqrt(originToCenter.square_norm() - proj * proj);

        if (distCenter > radius_)
        {
            return {};
        }

        auto f = std::sqrt(radius_ * radius_ - distCenter * distCenter);

        auto tI1 = proj - f;
        if (tI1 > 0)
        {
            return Intersection{ ray, tI1, 0, 0, this };
        }

        auto tI2 = proj + f;
        if (tI2 > 0)
        {
            return Intersection{ ray, tI2, 0, 0, this };
        }
        // all intersection points are behind the origin of the ray
        return {};
    }

    vectors::Vector3 Sphere::get_normal(Intersection intersection)
    {
        auto intersectionPoint = intersection.ray.origin_get()
            + intersection.t * intersection.ray.direction_get();
        return (intersectionPoint - center_).normalized();
    }

    std::ostream &Sphere::print(std::ostream &out) const
    {
        return out << "Sphere{ center: " << center_ << ", radius: " << radius_
                   << " }";
    }
} // namespace raytracer
