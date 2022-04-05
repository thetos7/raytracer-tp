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
            double u = intersection.u;
            double v = intersection.v;
            int ucoord = _width * u;
            int vcoord = _height * v;
            auto diffuseColor = _diffuseMap.pixel_get(ucoord, vcoord);
            auto specularColor = _specularMap.pixel_get(ucoord, vcoord);
            auto specularSpreadColor = _specularSpreadMap.pixel_get(ucoord, vcoord);
            auto reflectivityColor = _reflectivityMap.pixel_get(ucoord, vcoord);
            auto diffuseVector = vectors::Vector3(diffuseColor.r / 255., diffuseColor.g / 255., diffuseColor.b / 255.);
            auto specularVector = vectors::Vector3::all(specularColor.r / _specularFactor);
            auto specularSpread = specularSpreadColor.r / _specularSpreadFactor;
            auto reflectivityVector = vectors::Vector3::all(reflectivityColor.r / _reflectivityFactor);
            return MaterialProperties(diffuseVector, specularVector, specularSpread, reflectivityVector);
        }
    } // namespace materials
} // namespace raytracer