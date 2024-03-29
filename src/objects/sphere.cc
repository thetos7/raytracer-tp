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
            // https://en.wikipedia.org/wiki/UV_mapping
            vectors::Vector3 d =
                (ray.origin + ray.direction * tI1 - this->center_)
                    .normalized(); // vector from point to center
            double u = 0.5 + std::atan2(d.x, d.y) / (2 * M_PI);
            double v = 0.5 + std::asin(d.z) / M_PI;

            return Intersection{ ray, tI1, { u, v }, this };
        }

        auto tI2 = proj + f;
        if (tI2 > 0)
        {
            // https://en.wikipedia.org/wiki/UV_mapping
            vectors::Vector3 d =
                (ray.origin + ray.direction * tI2 - this->center_)
                    .normalized(); // vector from point to center
            double u = 0.5 + std::atan2(d.x, d.y) / (2 * M_PI);
            double v = 0.5 + std::asin(d.z) / M_PI;

            return Intersection{ ray, tI2, { u, v }, this };
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
