#include "material_properties.hh"

namespace raytracer::materials
{
    class Texture_Material
    {
    public:
        virtual const MaterialProperties get_point_properties(double u, double v) = 0;
    };
} // namespace raytracer::materials