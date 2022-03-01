#include "point_light.hh"

#include "intersection/intersection.hh"
#include "scene/scene.hh"

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
        static constexpr auto EPSILON = 0.0001;
        const auto target = intersection.intersection_point();
        const auto normal = intersection.normal();
        const auto ray = Ray::AtoB(position, target);
        const auto light_cast = intersection.scene->cast_ray(ray);
        const bool illuminated = !light_cast
            || light_cast->t <= (target - position).norm() + EPSILON;
        if (illuminated)
        {
            return -ray.direction.dot(normal) * intensity;
        }
        return vectors::Vector3::zero();
    }
} // namespace raytracer::lights
