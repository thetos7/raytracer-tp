#include "ambient_light.hh"

#include <ostream>

namespace raytracer::lights
{
    AmbientLight::AmbientLight(const vectors::Vector3 &color)
        : color{ color }
    {}

    vectors::Vector3
    AmbientLight::get_illumination(const Intersection &intersection) const
    {
        return color;
    }

    std::ostream &AmbientLight::print(std::ostream &out) const
    {
        return out << "AmbientLight{ color: " << color << " }";
    }
} // namespace raytracer::lights
