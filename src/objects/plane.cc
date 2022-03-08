#include "plane.hh"

#include <cmath>
#include <ostream>

#include "intersection/intersection.hh"
#include "materials/material.hh"
#include "points/point3.hh"
#include "ray/ray.hh"
#include "vectors/vector3.hh"

namespace raytracer::objects
{
    Plane::Plane(const points::Point3 &origin, const vectors::Vector3 &normal,
                 MaterialPtr material)
        : Object{ material }
        , origin_{ origin }
        , normal_{ normal }
    {}

    std::optional<Intersection> Plane::intersects_ray(const Ray &ray) const
    {
        static constexpr auto EPSILON = 0.000000001;
        const auto denom = normal_.dot(ray.direction);
        if (std::abs(denom) < EPSILON)
        {
            return {}; // parallel
        }
        const auto t = (normal_.dot(origin_ - ray.origin)) / denom;
        if (t < 0)
        {
            return {};
        }
        return Intersection{ ray, t, 0, 0, this };
    }

    vectors::Vector3 Plane::get_normal(const Intersection &intersection) const
    {
        return normal_;
    }

    std::ostream &Plane::print(std::ostream &out) const
    {
        return out << "Plane{ origin: " << origin_ << ", normal: " << normal_
                   << " }";
    }
} // namespace raytracer::objects