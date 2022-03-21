#include "scene.hh"

#include <cmath>
#include <iostream>
#include <sstream>

#include "camera/camera.hh"
#include "intersection/intersection.hh"
#include "lights/illumination.hh"
#include "lights/light.hh"
#include "materials/material_properties.hh"
#include "objects/object.hh"
#include "ray/ray.hh"
#include "utils/utils.hh"

namespace raytracer
{
    using utils::join;
    Scene::Scene()
    {}

    Scene::Scene(const Camera &camera)
        : Scene{ camera, {}, {} }
    {}

    Scene::Scene(const Camera &camera, ObjectCollection objects,
                 const LightCollection lights)
        : camera_{ camera }
        , objects_{ objects }
        , lights_{ lights }
    {}

    Camera &Scene::camera()
    {
        return camera_;
    }

    const Camera &Scene::camera() const
    {
        return camera_;
    }

    Scene::LightCollection &Scene::lights()
    {
        return lights_;
    }

    const Scene::LightCollection &Scene::lights() const
    {
        return lights_;
    }

    Scene::ObjectCollection &Scene::objects()
    {
        return objects_;
    }

    const Scene::ObjectCollection &Scene::objects() const
    {
        return objects_;
    }

    std::optional<Intersection> Scene::cast_ray(const Ray &ray) const
    {
        std::optional<Intersection> minIntersection;
        for (const auto &obj : objects_)
        {
            const auto intersection = obj->intersects_ray(ray);
            if (intersection
                && (!minIntersection || minIntersection->t > intersection->t))
            {
                minIntersection = intersection;
            }
        }
        minIntersection->scene = this;
        return minIntersection;
    }

    Scene::SampleResult Scene::sample_color(const Ray &ray,
                                            const int depth) const
    {
        if (depth <= 0)
        {
            return {};
        }

        using utils::EPSILON;

        auto intersection = this->cast_ray(ray);
        if (!intersection)
        {
            return {};
        }
        // TODO: extract to shader function/object
        const auto normal = intersection->normal();
        const auto reflect_direction = ray.direction.reflect(normal);
        const auto intersection_point = intersection->intersection_point();
        const Ray reflected_ray(intersection_point
                                    + reflect_direction * EPSILON,
                                reflect_direction);
        const auto &props = intersection->object->get_texture(*intersection);
        auto color = vectors::Vector3::zero();
        for (const auto &light : lights_)
        {
            const auto illumination = light->get_illumination(*intersection);
            // diffuse
            color += props.diffuse * illumination.light_intensity;
            // specular
            if (illumination.light_direction)
            {
                color += props.specular * illumination.light_intensity
                    * std::pow(std::max(0.,
                                        reflect_direction.dot(
                                            *illumination.light_direction)),
                               props.specular_spread);
            }
        }
        // reflection
        const auto reflected = sample_color(reflected_ray, depth - 1);
        if (reflected)
        {
            color += props.reflectivity * (*reflected);
        }

        return color;
    }

    std::ostream &operator<<(std::ostream &out, const Scene &scene)
    {
        out << "Scene { camera: " << scene.camera() << ", objects: [ ";
        out << join(scene.objects(), ", ");
        out << " ], lights: [ ";
        out << join(scene.lights(), ", ");
        out << " ] }";
        return out;
    }
} // namespace raytracer
