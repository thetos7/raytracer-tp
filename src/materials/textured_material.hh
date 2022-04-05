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
                             image::RgbImage specularSpreadMap,
                             image::RgbImage reflectivityMap)
                : _height(diffuseMap.get_heigth())
                , _width(diffuseMap.get_width())
                , _diffuseMap(diffuseMap)
                , _specularMap(specularMap)
                , _specularSpreadMap(specularSpreadMap)
                , _reflectivityMap(reflectivityMap){};

            const MaterialProperties
            get_point_properties(Intersection intersection) const;

        private:
            unsigned _height;
            unsigned _width;
            image::RgbImage _diffuseMap;
            image::RgbImage _specularMap;
            double _specularFactor = 255;
            image::RgbImage _specularSpreadMap;
            double _specularSpreadFactor = 255;
            image::RgbImage _reflectivityMap;
            double _reflectivityFactor = 255;
        };
    } // namespace materials
} // namespace raytracer