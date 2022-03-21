#include <cmath>
#include <iostream>
#include <memory>

#include "colors/rgb.hh"
#include "engine/engine.hh"
#include "image/linear_image.hh"
#include "json/json-import.hh"
#include "lights/ambient_light.hh"
#include "lights/point_light.hh"
#include "lights/sun_light.hh"
#include "materials/uniform_material.hh"
#include "objects/plane.hh"
#include "objects/sphere.hh"
#include "objects/triangle.hh"
#include "points/point3.hh"
#include "scene/scene.hh"
#include "vectors/vector3.hh"

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        raytracer::JsonImport jsonImport = raytracer::JsonImport(argv[1]);
        auto scene = jsonImport.importScene();
        std::cout << "Scene built:" << std::endl;
        std::cout << scene << std::endl;

        constexpr int height = 480;
        const auto output = raytracer::raytrace(scene, height, 3);
        output->save_ppm("result.ppm");
    }
    return 0;

    using namespace points;
    using namespace vectors;
    using raytracer::materials::UniformMaterial;
    using raytracer::lights::PointLight;
    using raytracer::lights::SunLight;
    using raytracer::lights::AmbientLight;
    using raytracer::objects::Sphere;
    using raytracer::objects::Plane;
    using raytracer::objects::Triangle;
    using raytracer::Scene;
    using raytracer::Camera;
    using colors::RGB;

    constexpr int height = 480;
    constexpr double aspectRatio = 16. / 9.;
    constexpr int width = height * aspectRatio;
    constexpr double fieldOfView = (90. / 180.) * M_PI;

    auto lightGreyUniform = std::make_shared<UniformMaterial>(UniformMaterial{
        Vector3::all(0.8),
        Vector3::all(0.),
        1.,
        Vector3::all(1.),
    });
    auto redUniform = std::make_shared<UniformMaterial>(UniformMaterial{
        Vector3(0.9, 0.2, 0.2),
        Vector3::all(0.1),
        .8,
        Vector3::all(0.05),
    });
    auto orangeUniform = std::make_shared<UniformMaterial>(UniformMaterial{
        Vector3(1.0, 0.5, 0.1),
        Vector3::all(0.),
        1.,
        Vector3::zero(),
    });
    auto greenUniform = std::make_shared<UniformMaterial>(UniformMaterial{
        Vector3(0.1, 0.6, 0.1),
        Vector3::all(0.5),
        16.,
        Vector3::all(0.5),
    });
    auto lightBlueUniform = std::make_shared<UniformMaterial>(UniformMaterial{
        Vector3(0.5, 0.5, 0.7),
        Vector3::zero(),
        1.,
        Vector3::zero(),
    });

    const auto camPos = Point3::origin();
    const auto camPoint = Point3(4, 0, 0);
    const auto redSphere = std::make_shared<Sphere>(camPoint, 1., redUniform);
    const auto orangeSphere =
        std::make_shared<Sphere>(Point3(4, -1, 1), 1., orangeUniform);
    const auto greenSphere =
        std::make_shared<Sphere>(Point3(3, 0, 1), .5, greenUniform);
    const auto backgroundPlane = std::make_shared<Plane>(
        Point3(20, 0, 0), Vector3(-1, 0, 0), lightBlueUniform);

    const auto lightGreyPlane = std::make_shared<Plane>(
        Point3(0, 0, -1), Vector3::up(), lightGreyUniform);

    const auto redTriangle = std::make_shared<Triangle>(
        Triangle::PointsType{
            Point3{ 2, 1, 1 },
            Point3{ 2, 0, 1 },
            Point3{ 2, 1, 0 },
        },
        redUniform);

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
            backgroundPlane,
            redTriangle,
        },
        Scene::LightCollection{
            std::make_shared<AmbientLight>(Vector3::all(.15)),
            std::make_shared<PointLight>(Point3::origin() + Vector3::up() * 3,
                                         Vector3::all(0.8)),
            std::make_shared<SunLight>(Vector3(0.5, -1, -1),
                                       Vector3(0.8, 0.8, 0.6)),
        },
    };

    std::cout << "Scene built:" << std::endl;
    std::cout << scene << std::endl;

    const auto output = raytracer::raytrace(scene, height, 3);
    output->save_ppm("result.ppm");
    return 0;
}
