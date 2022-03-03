#pragma once

#include "intersection/fwd.hh"
#include "material_properties.hh"

namespace raytracer
{
    class Intersection;

    namespace materials
    {
        class Material
        {
        public:
            virtual const MaterialProperties &
            get_point_properties(Intersection intersection) const = 0;
        };
    } // namespace materials
} // namespace raytracer
