#pragma once

#include <optional>

#include "object.hh"
#include "points/point3.hh"

namespace raytracer::objects
{
    class Plane : public Object
    {
    public:
        Plane(const points::Point3 &reference, const vectors::Vector3 &normal,
              MaterialPtr material);

        virtual std::optional<Intersection>
        intersects_ray(const Ray &ray) const override;

        virtual vectors::Vector3
        get_normal(const Intersection &intersection) const override;

    private:
        virtual std::ostream &print(std::ostream &out) const override;

        points::Point3 origin_;
        vectors::Vector3 normal_;
    };
} // namespace raytracer::objects
