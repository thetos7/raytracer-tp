#pragma once

#include "material.hh"
#include "material_properties.hh"
#include "vectors/fwd.hh"

namespace raytracer::materials
{
    class UniformTexture : public Material
    {
    public:
        UniformTexture(const vectors::Vector3 &diffuse,
                       const vectors::Vector3 &specular, double specular_spread);
        const MaterialProperties &
        get_point_properties(Intersection intersection) const override;

    private:
        const MaterialProperties properties_;
    };
} // namespace raytracer::materials
