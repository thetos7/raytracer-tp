#include "sun_light.hh"

#include <ostream>

#include "illumination.hh"
#include "intersection/intersection.hh"
#include "points/point3.hh"
#include "ray/ray.hh"
#include "scene/scene.hh"
#include "utils/utils.hh"
#include "vectors/vector3.hh"

namespace raytracer::lights
{
    SunLight::SunLight(const vectors::Vector3 &direction,
                       const vectors::Vector3 &color)
        : direction{ direction.normalized() }
        , color{ color }
    {}

    Light::IlluminationResult
    SunLight::get_illumination(const Intersection &intersection) const
    {
        const auto normal = intersection.normal();
        const auto point = intersection.intersection_point();
        const Ray ray(point + -direction * 0.000001, -direction);
        const auto obstruction = intersection.scene->cast_ray(ray);

        if (obstruction)
        {
            return IlluminationResult{ {}, vectors::Vector3::zero() };
        }

        return IlluminationResult{ -direction, -normal.dot(direction) * color };
    }

    std::ostream &SunLight::print(std::ostream &out) const
    {
        if (utils::compact_enabled(out))
        {
            return out << "SunLight{ " << direction << ", " << color << " }";
        }
        return out << "SunLight{ direction: " << direction
                   << ", color: " << color << " }";
    }
} // namespace raytracer::lights
