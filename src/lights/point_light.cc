#include "point_light.hh"

namespace raytracer::lights
{
    PointLight::PointLight(points::Point3 position, vectors::Vector3 intensity)
        : position{ position }
        , intensity{ intensity }
    {}

    std::ostream &PointLight::print(std::ostream &out) const
    {
        return out << "PointLight{ position: " << position
                   << ", intensity: " << intensity << " }";
    }
} // namespace raytracer::lights
