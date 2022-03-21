#include "ambient_light.hh"

#include <ostream>

#include "illumination.hh"
#include "utils/utils.hh"

namespace raytracer::lights
{
    AmbientLight::AmbientLight(const vectors::Vector3 &color)
        : color{ color }
    {}

    Light::IlluminationResult
    AmbientLight::get_illumination(const Intersection &intersection) const
    {
        return IlluminationResult{ {}, color };
    }

    std::ostream &AmbientLight::print(std::ostream &out) const
    {
        if (utils::compact_enabled(out))
        {
            return out << "AmbientLight{ " << color << " }";
        }
        return out << "AmbientLight{ color: " << color << " }";
    }
} // namespace raytracer::lights
