#include <cmath>
#include <iostream>
#include <memory>

#include "engine/engine.hh"
#include "image/image.hh"
#include "lights/point_light.hh"
#include "materials/uniform_material.hh"
#include "objects/sphere.hh"
#include "points/point3.hh"
#include "scene/scene.hh"
#include "vectors/vector3.hh"

int main(int argc, char *argv[])
{
    using namespace points;
    using namespace vectors;
    using raytracer::materials::UniformTexture;
    using raytracer::lights::PointLight;
    using raytracer::objects::Sphere;
    using raytracer::Scene;
    using raytracer::Camera;

    constexpr int height = 480;
    constexpr double aspectRatio = 16. / 9.;
    constexpr int width = height * aspectRatio;
    constexpr double fieldOfView = (90. / 180.) * M_PI;

    auto greyUniform = std::make_shared<UniformTexture>(UniformTexture{
        Vector3(0.9, 0.2, 0.2),
        Vector3::all(0.),
    });
    const auto camPos = Point3::origin();
    const auto camPoint = Point3(4, 0, 0);
    const auto sphere = std::make_shared<Sphere>(camPoint, 1., greyUniform);

    Scene scene{
        Camera{
            camPos,
            camPoint,
            Vector3::up(),
            fieldOfView,
            aspectRatio,
            0.5,
        },
        Scene::ObjectCollection{
            sphere,
        },
        Scene::LightCollection{
            std::make_shared<PointLight>(Point3::origin() + Vector3::up() * 3,
                                         Vector3::all(10.)),
        },
    };

    std::cout << "Scene built:" << std::endl;
    std::cout << scene << std::endl;
    const auto output = raytracer::raytrace(scene, height);
    output->save_ppm("result.ppm");
    return 0;
}
