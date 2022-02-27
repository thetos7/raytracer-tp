#pragma once

#include <memory>
#include <optional>

#include "intersection/intersection.hh"
#include "materials/material_properties.hh"
#include "materials/texture_material.hh"
#include "ray/ray.hh"
#include "vectors/vector3.hh"

namespace raytracer
{
    class Intersection;
    namespace materials
    {
        class TextureMaterial;
    } // namespace materials

    class Object
    {
    public:
        using MaterialPtr = std::shared_ptr<materials::TextureMaterial>;
        Object(MaterialPtr material_);

        virtual std::optional<Intersection> intersects_ray(const Ray &ray) = 0;
        virtual vectors::Vector3 get_normal(Intersection intersection) = 0;
        virtual const materials::MaterialProperties
        get_texture(Intersection intersection);

    private:
        virtual std::ostream &print(std::ostream &out) const = 0;

        MaterialPtr material_;

        friend std::ostream &operator<<(std::ostream&out, const Object &obj);
    };

    std::ostream &operator<<(std::ostream&out, const Object &obj);
} // namespace raytracer
