#pragma once

#include <memory>
#include <vector>

#include "object.hh"
#include "triangle.hh"

namespace raytracer::objects
{
    class Mesh : public Object
    {
    public:
        using TriangleCollection = std::vector<std::shared_ptr<Triangle>>;
        Mesh(const TriangleCollection &triangles);

        virtual std::optional<Intersection>
        intersects_ray(const Ray &ray) const override;
        virtual vectors::Vector3
        get_normal(const Intersection &intersection) const override;
        virtual const materials::MaterialProperties &
        get_texture(const Intersection &intersection) const override;

    private:
        virtual std::ostream &print(std::ostream &out) const override;

        TriangleCollection triangles_;
    };

} // namespace raytracer::objects
