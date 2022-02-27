#include "scene.hh"

#include <sstream>

namespace raytracer
{

    namespace
    {
        template <class T>
        std::string join(std::vector<std::shared_ptr<T>> vec, std::string delimiter)
        {
            std::ostringstream oss;
            for (auto it = vec.begin(); it != vec.end(); ++it)
            {
                oss << **it;
                if (it != vec.end() - 1)
                {
                    oss << delimiter;
                }
            }
            return oss.str();
        }
    } // namespace

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
