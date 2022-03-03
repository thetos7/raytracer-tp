#include "object.hh"

#include "intersection/intersection.hh"
#include "materials/material.hh"
#include "materials/material_properties.hh"

namespace raytracer::objects
{
    Object::Object(Object::MaterialPtr material)
        : material{ material }
    {}

    const materials::MaterialProperties &
    Object::get_texture(const Intersection &intersection) const
    {
        return material->get_point_properties(intersection);
    }

    std::ostream &operator<<(std::ostream &out, const Object &obj)
    {
        return obj.print(out);
    }
} // namespace raytracer::objects
