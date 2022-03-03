#pragma once

#include <optional>

#include "object.hh"
#include "points/point3.hh"

namespace raytracer::objects
{
    class Sphere : public Object
    {
    public:
        Sphere(const points::Point3 &center, double radius,
               MaterialPtr material);
        virtual std::optional<Intersection>
        intersects_ray(const Ray &ray) const override;
        virtual vectors::Vector3
        get_normal(const Intersection &intersection) const override;

    private:
        virtual std::ostream &print(std::ostream &out) const override;
        points::Point3 center_;
        double radius_;
    };
} // namespace raytracer::objects
