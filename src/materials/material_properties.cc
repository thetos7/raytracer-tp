#include "material_properties.hh"

#include "vectors/vector3.hh"

namespace raytracer::materials
{
    MaterialProperties::MaterialProperties(const vectors::Vector3 &diffuse,
                                           double specular,
                                           double specular_spread,
                                           double reflectivity)
        : diffuse{ diffuse }
        , specular{ specular }
        , specular_spread{ specular_spread }
        , reflectivity{ reflectivity }
    {}
} // namespace raytracer::materials
