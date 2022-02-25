#pragma once

#include "object.hh"
#include "points/point3.hh"
#include "materials/texture_material.hh"

namespace raytracer
{
    class Sphere : Object
    {
    public:
        Sphere(const points::Point3 &center, double radius, MaterialPtr material);
        virtual double intersects_ray(const Ray &ray) override;
        virtual vectors::Vector3 get_normal(double u, double v) override;
    private:
        points::Point3 center_;
        double radius_;
    };
} // namespace raytracer