#pragma once

#include <memory>
#include <optional>
#include <ostream>
#include <vector>

#include "camera/camera.hh"
#include "intersection/intersection.hh"
#include "lights/light.hh"
#include "objects/object.hh"
#include "ray/ray.hh"

namespace raytracer
{
    class Intersection;

    class Scene
    {
    public:
        using LightCollection = std::vector<std::shared_ptr<lights::Light>>;
        using ObjectCollection = std::vector<std::shared_ptr<objects::Object>>;
        Scene(const Camera &camera);
        Scene(const Camera &camera, ObjectCollection objects,
              const LightCollection lights);

        Camera &camera();
        const Camera &camera() const;

        LightCollection &lights();
        const LightCollection &lights() const;

        ObjectCollection &objects();
        const ObjectCollection &objects() const;

        std::optional<Intersection> cast_ray(const Ray &ray) const;

    private:
        LightCollection lights_;
        ObjectCollection objects_;
        Camera camera_;
    };

    std::ostream &operator<<(std::ostream &out, const Scene &scene);
} // namespace raytracer
