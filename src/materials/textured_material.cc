#include "textured_material.hh"

#include "colors/rgb.hh"
#include "intersection/intersection.hh"
#include "materials/material_properties.hh"

namespace raytracer
{
    namespace materials
    {
        const MaterialProperties
        TexturedMaterial::get_point_properties(Intersection intersection) const
        {
            double u = intersection.uv.x;
            double v = intersection.uv.y;
            int ucoord = _width * u;
            int vcoord = _height * v;
            auto diffuseColor = _diffuseMap.pixel_get(ucoord, vcoord);
            auto specularColor = _specularMap.pixel_get(ucoord, vcoord);
            auto diffuseVector = vectors::Vector3(diffuseColor.r / 255., diffuseColor.g / 255., diffuseColor.b / 255.);
            return MaterialProperties(diffuseVector, specularColor.r / 255, _specularSpread, _reflectivity);
        }
    } // namespace materials
} // namespace raytracer