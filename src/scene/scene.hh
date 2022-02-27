#pragma once

#include <vector>

#include "camera/camera.hh"
#include "lights/light.hh"
#include "objects/object.hh"

namespace raytracer
{
    class Scene
    {
    public:
        Scene(const Camera &camera);
        Scene(const Camera &camera, std::vector<Object> objects,
              const std::vector<lights::Light> lights);

        Camera &camera();
        const Camera &camera() const;

        std::vector<lights::Light> &lights();
        const std::vector<lights::Light> &lights() const;

        std::vector<Object> &objects();
        const std::vector<Object> &objects() const;

    private:
        std::vector<lights::Light> lights_;
        std::vector<Object> objects_;
        Camera camera_;
    };
} // namespace raytracer
