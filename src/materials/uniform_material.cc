#include "uniform_material.hh"

#include "intersection/intersection.hh"
#include "vectors/vector3.hh"

namespace raytracer::materials
{
    UniformTexture::UniformTexture(const vectors::Vector3 &diffuse,
                                   const vectors::Vector3 &specular)
        : properties_{ diffuse, specular }
    {}

    const MaterialProperties &
    UniformTexture::get_point_properties(Intersection intersection) const
    {
        return properties_;
    }
} // namespace raytracer::materials
