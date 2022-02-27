#pragma once

#include <optional>

#include "materials/texture_material.hh"
#include "object.hh"
#include "points/point3.hh"

namespace raytracer
{
    class Sphere : public Object
    {
    public:
        Sphere(const points::Point3 &center, double radius,
               MaterialPtr material);
        virtual std::optional<Intersection>
        intersects_ray(const Ray &ray) override;
        virtual vectors::Vector3 get_normal(Intersection intersection) override;

    private:
        points::Point3 center_;
        double radius_;
    };
} // namespace raytracer
