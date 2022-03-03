#pragma once

#include <memory>
#include <optional>

#include "intersection/fwd.hh"
#include "materials/fwd.hh"
#include "ray/fwd.hh"
#include "vectors/fwd.hh"

namespace raytracer::objects
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

        friend std::ostream &operator<<(std::ostream &out, const Object &obj);
    };

    std::ostream &operator<<(std::ostream &out, const Object &obj);
} // namespace raytracer::objects
