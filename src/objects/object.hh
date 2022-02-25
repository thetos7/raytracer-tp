#pragma once

#include <memory>

#include "materials/material_properties.hh"
#include "materials/texture_material.hh"
#include "ray/ray.hh"
#include "vectors/vector3.hh"

namespace raytracer
{
    class Object
    {
    public:
        using MaterialPtr = std::shared_ptr<materials::Texture_Material>;
        Object(MaterialPtr  material_);

        virtual double intersects_ray(const Ray &ray) = 0;
        virtual vectors::Vector3 get_normal(double u, double v) = 0;
        virtual const materials::MaterialProperties get_texture(double u,
                                                                double v);

    private:
        MaterialPtr material_;
    };
} // namespace raytracer