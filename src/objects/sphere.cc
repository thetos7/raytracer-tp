#include "sphere.hh"

#include <cmath>
#include <iostream>
#include <optional>

#include "intersection/intersection.hh"
#include "materials/material.hh"
#include "object.hh"
#include "points/point3.hh"
#include "ray/ray.hh"
#include "utils/utils.hh"
#include "vectors/vector3.hh"

namespace raytracer::objects
{
    Sphere::Sphere(const points::Point3 &center, double radius,
                   Object::MaterialPtr material)
        : Object{ material }
        , center_{ center }
        , radius_{ radius }
    {}

    std::optional<Intersection> Sphere::intersects_ray(const Ray &ray) const
    {
        auto originToCenter = center_ - ray.origin;

        auto proj = originToCenter.dot(ray.direction);

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

    vectors::Vector3 Sphere::get_normal(const Intersection &intersection) const
    {
        return (intersection.intersection_point() - center_).normalized();
    }

    std::ostream &Sphere::print(std::ostream &out) const
    {
        if (utils::compact_enabled(out))
        {
            return out << "Sphere{ " << center_ << ", " << radius_ << " }";
        }
        return out << "Sphere{ center: " << center_ << ", radius: " << radius_
                   << " }";
    }
} // namespace raytracer::objects
