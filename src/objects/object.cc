#include "object.hh"

#include "materials/material_properties.hh"
#include "materials/texture_material.hh"

namespace raytracer::objects
{
    Object::Object(Object::MaterialPtr material)
        : material{ material }
    {}

    const materials::MaterialProperties &
    Object::get_texture(Intersection intersection) const
    {
        return material->get_point_properties(intersection);
    }

    std::ostream &operator<<(std::ostream &out, const Object &obj)
    {
        return obj.print(out);
    }
} // namespace raytracer::objects
