#include "uniform_material.hh"

#include "intersection/intersection.hh"

namespace raytracer::materials
{
    UniformTexture::UniformTexture(vectors::Vector3 &diffuse,
                                     vectors::Vector3 &specular)
        : properties_{ diffuse, specular }
    {}

    const MaterialProperties
    UniformTexture::get_point_properties(Intersection intersection)
    {
        return properties_;
    }
} // namespace raytracer::materials
