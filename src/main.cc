#include <cmath>
#include <iostream>
#include <memory>

#include "colors/rgb.hh"
#include "engine/engine.hh"
#include "image/image.hh"
#include "lights/ambient_light.hh"
#include "lights/point_light.hh"
#include "lights/sun_light.hh"
#include "materials/uniform_material.hh"
#include "objects/plane.hh"
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
    using raytracer::lights::SunLight;
    using raytracer::lights::AmbientLight;
    using raytracer::objects::Sphere;
    using raytracer::objects::Plane;
    using raytracer::Scene;
    using raytracer::Camera;
    using colors::RGB;

    constexpr int height = 480;
    constexpr double aspectRatio = 16. / 9.;
    constexpr int width = height * aspectRatio;
    constexpr double fieldOfView = (90. / 180.) * M_PI;

    auto lightGreyUniform = std::make_shared<UniformTexture>(UniformTexture{
        Vector3::all(0.8),
        Vector3::all(0.),
    });
    auto redUniform = std::make_shared<UniformTexture>(UniformTexture{
        Vector3(0.9, 0.2, 0.2),
        Vector3::all(0.),
    });
    auto orangeUniform = std::make_shared<UniformTexture>(UniformTexture{
        Vector3(0.9, 0.7, 0.2),
        Vector3::all(0.),
    });
    auto greenUniform = std::make_shared<UniformTexture>(UniformTexture{
        Vector3(0.1, 0.7, 0.1),
        Vector3::all(0.),
    });

    const auto camPos = Point3::origin();
    const auto camPoint = Point3(4, 0, 0);
    const auto redSphere = std::make_shared<Sphere>(camPoint, 1., redUniform);
    const auto orangeSphere =
        std::make_shared<Sphere>(Point3(4, -1, 1), 1., orangeUniform);
    const auto greenSphere =
        std::make_shared<Sphere>(Point3(3, 0, 1), .5, greenUniform);

    auto lightGreyPlane = std::make_shared<Plane>(
        Point3(0, 0, -1), Vector3::up(), lightGreyUniform);

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
            redSphere,
            orangeSphere,
            greenSphere,
            lightGreyPlane,
        },
        Scene::LightCollection{
            std::make_shared<AmbientLight>(Vector3::all(.15)),
            std::make_shared<PointLight>(Point3::origin() + Vector3::up() * 3,
                                         Vector3::all(1.5)),
            std::make_shared<SunLight>(Vector3(0.5, -1, -1),
                                       Vector3(1., 1., 0.8)),
        },
    };

    std::cout << "Scene built:" << std::endl;
    std::cout << scene << std::endl;
    const auto output =
        raytracer::raytrace(scene, height, RGB::from_hex(0x222233));
    output->save_ppm("result.ppm");
    return 0;
}
