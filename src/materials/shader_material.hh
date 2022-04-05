#pragma once

#include <functional>

#include "material.hh"

namespace raytracer::materials
{
    class ShaderMaterial : public Material
    {
    public:
        using ShaderProgram =
            std::function<void(const Intersection &, MaterialProperties &)>;

        ShaderMaterial(ShaderProgram shader);

        virtual const MaterialProperties
        get_point_properties(Intersection intersection) const override;

    private:
        ShaderProgram shader_;
    };

} // namespace raytracer::materials
