#pragma once

#include "vectors/vector3.hh"

namespace raytracer::materials
{
    class MaterialProperties
    {
    public:
        MaterialProperties(vectors::Vector3 &diffuse, vectors::Vector3 &specular);
        const vectors::Vector3 diffuse;
        const vectors::Vector3 specular;

    private:
    };
} // namespace raytracer::materials
