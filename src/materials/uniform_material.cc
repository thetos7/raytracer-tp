#include "uniform_material.hh"

namespace raytracer::materials
{
    Uniform_Texture::Uniform_Texture(vectors::Vector3 &diffuse,
                                     vectors::Vector3 &specular)
        : properties_{ diffuse, specular }
    {}

    const MaterialProperties
    Uniform_Texture::get_point_properties(Intersection intersection)
    {
        return properties_;
    }
} // namespace raytracer::materials
