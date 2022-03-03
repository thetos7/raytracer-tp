#include "point_light.hh"

#include <ostream>

#include "intersection/intersection.hh"
#include "points/point3.hh"
#include "ray/ray.hh"
#include "scene/scene.hh"
#include "vectors/vector3.hh"

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

    vectors::Vector3
    PointLight::get_illumination(const Intersection &intersection) const
    {
        static constexpr auto EPSILON = 0.000000001;
        const auto target = intersection.intersection_point();
        const auto ray = Ray::AtoB(position, target);

        const auto light_intersection = *intersection.scene->cast_ray(ray);
        const auto reference_distance = (target - position).norm() - EPSILON;

        const bool illuminated = light_intersection.t >= reference_distance;
        if (illuminated)
        {
            const auto normal = intersection.normal();
            return -ray.direction.dot(normal) * intensity;
        }
        return vectors::Vector3::zero();
    }
} // namespace raytracer::lights
