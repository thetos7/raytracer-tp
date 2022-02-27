#pragma once

#include "material_properties.hh"
#include "texture_material.hh"
#include "vectors/vector3.hh"

namespace raytracer::materials
{
    class Uniform_Texture : Texture_Material
    {
    public:
        Uniform_Texture(vectors::Vector3 &diffuse, vectors::Vector3 &specular);
        const MaterialProperties get_point_properties(Intersection intersection) override;
    private:
        const MaterialProperties properties_;
    };
} // namespace raytracer::materials
