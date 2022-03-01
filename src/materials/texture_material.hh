#pragma once

#include "intersection/intersection.hh"
#include "material_properties.hh"

namespace raytracer
{
    class Intersection;

    namespace materials
    {
        class TextureMaterial
        {
        public:
            virtual const MaterialProperties &
            get_point_properties(Intersection intersection) const = 0;
        };
    } // namespace materials
} // namespace raytracer
