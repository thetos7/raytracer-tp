#pragma once
#include "image/rgb_image.hh"
#include "materials/material.hh"

namespace raytracer
{
    namespace materials
    {
        class TexturedMaterial : public Material
        {
        public:
            TexturedMaterial(image::RgbImage diffuseMap,
                             image::RgbImage specularMap,
                             double specularSpread,
                             double reflectivity)
                : _height(diffuseMap.get_heigth())
                , _width(diffuseMap.get_width())
                , _diffuseMap(diffuseMap)
                , _specularMap(specularMap)
                , _specularSpread(specularSpread)
                , _reflectivity(reflectivity){};

            const MaterialProperties
            get_point_properties(Intersection intersection) const;

        private:
            unsigned _height;
            unsigned _width;
            image::RgbImage _diffuseMap;
            image::RgbImage _specularMap;
            double _specularSpread;
            double _reflectivity;
        };
    } // namespace materials
} // namespace raytracer