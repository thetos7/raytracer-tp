#include "material_properties.hh"

#include "vectors/vector3.hh"

namespace raytracer::materials
{
    MaterialProperties::MaterialProperties(const vectors::Vector3 &diffuse,
                                           const vectors::Vector3 &specular,
                                           double specular_spread)
        : diffuse{ diffuse }
        , specular{ specular }
        , specular_spread{ specular_spread }
    {}
} // namespace raytracer::materials
