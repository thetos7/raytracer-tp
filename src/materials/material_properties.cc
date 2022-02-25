#include "material_properties.hh"

#include "vectors/vector3.hh"

namespace raytracer::materials
{
    MaterialProperties::MaterialProperties(vectors::Vector3 &diffuse,
                                           vectors::Vector3 &specular)
        : diffuse{ diffuse }
        , specular{ specular }
    {}
} // namespace raytracer::materials