#pragma once

#include "material.hh"
#include "material_properties.hh"
#include "vectors/fwd.hh"

namespace raytracer::materials
{
    class UniformMaterial : public Material
    {
    public:
        UniformMaterial(const vectors::Vector3 &diffuse,
                       double specular, double specular_spread, double reflectivity);
        const MaterialProperties
        get_point_properties(Intersection intersection) const override;

    private:
        const MaterialProperties properties_;
    };
} // namespace raytracer::materials
