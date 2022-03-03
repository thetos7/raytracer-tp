#pragma once

#include "vectors/vector3.hh"

namespace raytracer::materials
{
    class MaterialProperties
    {
    public:
        MaterialProperties(const vectors::Vector3 &diffuse,
                           const vectors::Vector3 &specular,
                           double specular_spread);
        vectors::Vector3 diffuse;
        vectors::Vector3 specular;
        double specular_spread;

    private:
    };
} // namespace raytracer::materials
