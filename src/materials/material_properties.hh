#pragma once

#include "vectors/vector3.hh"

namespace raytracer::materials
{
    class MaterialProperties
    {
    public:
        MaterialProperties(const vectors::Vector3 &diffuse,
                           double specular,
                           double specular_spread,
                           double reflectivity);
        vectors::Vector3 diffuse;
        double specular;
        double reflectivity;
        double specular_spread;

    private:
    };
} // namespace raytracer::materials
