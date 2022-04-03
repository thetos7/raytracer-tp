#pragma once
#include "materials/material.hh"
#include "image/rgb_image.hh"

namespace raytracer
{
    namespace materials
    {
        class TexturedMaterial : Material
        {
        public:
            const MaterialProperties &
            get_point_properties(Intersection intersection) const;
        private:
            image::RgbImage texture;
        };
    } // namespace materials
} // namespace raytracer