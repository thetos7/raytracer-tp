#include "object.hh"

#include "materials/material_properties.hh"
#include "materials/texture_material.hh"

namespace raytracer
{
    Object::Object(Object::MaterialPtr material)
        : material_{ material }
    {}

    const materials::MaterialProperties Object::get_texture(double u, double v)
    {
        return material_->get_point_properties(u, v);
    }
} // namespace raytracer