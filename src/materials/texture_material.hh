#pragma once

#include "intersection/intersection.hh"
#include "material_properties.hh"

namespace raytracer::materials
{
    class Texture_Material
    {
    public:
        virtual const MaterialProperties
        get_point_properties(Intersection intersection) = 0;
    };
} // namespace raytracer::materials
