#include "scene.hh"

#include <sstream>

#include "utils/utils.hh"

namespace raytracer
{
    using utils::join;
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
