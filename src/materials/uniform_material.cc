#include "uniform_material.hh"

#include "intersection/intersection.hh"
#include "vectors/vector3.hh"

namespace raytracer::materials
{
    UniformMaterial::UniformMaterial(const vectors::Vector3 &diffuse,
                                     double specular, double specular_spread,
                                     double reflectivity)
        : properties_{ diffuse, specular, specular_spread, reflectivity }
    {}

    const MaterialProperties
    UniformMaterial::get_point_properties(Intersection intersection) const
    {
        return properties_;
    }
} // namespace raytracer::materials
