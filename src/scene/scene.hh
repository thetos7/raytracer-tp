#pragma once

#include <iosfwd>
#include <memory>
#include <optional>
#include <vector>

#include "camera/camera.hh"
#include "intersection/fwd.hh"
#include "json/fwd.hh"
#include "lights/fwd.hh"
#include "objects/fwd.hh"
#include "ray/fwd.hh"

namespace raytracer
{
    class Intersection;

    class Scene
    {
        friend JsonImport;

    public:
        using LightCollection = std::vector<std::shared_ptr<lights::Light>>;
        using ObjectCollection = std::vector<std::shared_ptr<objects::Object>>;
        using SampleResult = std::optional<const vectors::Vector3>;
        Scene();
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

        SampleResult sample_color(const Ray &ray, const int depth) const;

    private:
        LightCollection lights_;
        ObjectCollection objects_;
        Camera camera_;
    };

    std::ostream &operator<<(std::ostream &out, const Scene &scene);
} // namespace raytracer
