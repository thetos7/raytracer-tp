#pragma once

#include <memory>
#include <optional>

#include "intersection/intersection.hh"
#include "materials/material_properties.hh"
#include "ray/ray.hh"
#include "vectors/vector3.hh"

namespace raytracer
{
    class Intersection;
    namespace materials
    {
        class Material;
    } // namespace materials

    namespace objects
    {

        class Object
        {
        public:
            using MaterialPtr = std::shared_ptr<materials::Material>;
            Object(MaterialPtr material);

            virtual std::optional<Intersection>
            intersects_ray(const Ray &ray) const = 0;
            virtual vectors::Vector3
            get_normal(const Intersection &intersection) const = 0;
            virtual const materials::MaterialProperties &
            get_texture(const Intersection &intersection) const;

            MaterialPtr material;

        private:
            virtual std::ostream &print(std::ostream &out) const = 0;

            friend std::ostream &operator<<(std::ostream &out,
                                            const Object &obj);
        };

        std::ostream &operator<<(std::ostream &out, const Object &obj);
    } // namespace objects
} // namespace raytracer
