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
    private:
        std::vector<lights::Light> lights_;
        std::vector<Object> objects_;
        Camera camera_;
    };
} // namespace raytracer
