#include "scene.hh"

namespace raytracer
{
    Scene::Scene(const Camera &camera)
        : Scene{ camera, {}, {} }
    {}

    Scene::Scene(const Camera &camera, std::vector<Object> objects,
                 const std::vector<lights::Light> lights)
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

    std::vector<lights::Light> &Scene::lights()
    {
        return lights_;
    }

    const std::vector<lights::Light> &Scene::lights() const
    {
        return lights_;
    }

    std::vector<Object> &Scene::objects()
    {
        return objects_;
    }

    const std::vector<Object> &Scene::objects() const
    {
        return objects_;
    }
} // namespace raytracer
