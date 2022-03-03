#include "sun_light.hh"

#include "intersection/intersection.hh"
#include "points/point3.hh"
#include "ray/ray.hh"
#include "scene/scene.hh"
#include "vectors/vector3.hh"

namespace raytracer::lights
{
    SunLight::SunLight(const vectors::Vector3 &direction,
                       const vectors::Vector3 &color)
        : direction{ direction }
        , color{ color }
    {}

    vectors::Vector3
    SunLight::get_illumination(const Intersection &intersection) const
    {
        const auto normal = intersection.normal();
        const auto point = intersection.intersection_point();
        const Ray ray(point + -direction * 0.000001, -direction);
        const auto illumination = intersection.scene->cast_ray(ray);

        if (illumination)
        {
            return vectors::Vector3::zero();
        }

        return -normal.dot(direction) * color;
    }

    std::ostream &SunLight::print(std::ostream &out) const
    {
        return out << "Sunlight{ direction: " << direction
                   << ", color: " << color << " }";
    }
} // namespace raytracer::lights
