#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>

#include "colors/rgb.hh"
#include "image/image.hh"
#include "lights/light.hh"
#include "lights/point_light.hh"
#include "materials/uniform_material.hh"
#include "objects/object.hh"
#include "objects/sphere.hh"
#include "points/point3.hh"
#include "scene/scene.hh"
#include "vectors/vector3.hh"

int main(int argc, char *argv[])
{
    using Image = image::Image;
    using namespace raytracer;
    using namespace points;
    using namespace vectors;
    using namespace raytracer::materials;
    using namespace raytracer::lights;

    constexpr int height = 480;
    constexpr double aspectRatio = 16. / 9.;
    constexpr int width = height * aspectRatio;
    constexpr double fieldOfView = (90. / 180.) * M_PI;

    auto greyUniform = std::make_shared<UniformTexture>(UniformTexture{
        Vector3::all(0.7),
        Vector3::all(0.),
    });

    Scene scene{
        Camera{
            Point3{ -2, 0, 2 },
            Point3::origin(),
            Vector3{ 1, 0, 1 }.normalized(),
            fieldOfView,
            aspectRatio,
            0.5,
        },
        Scene::ObjectCollection{
            std::make_shared<Sphere>(Point3::origin(), 1., greyUniform),
        },
        Scene::LightCollection{
            std::make_shared<PointLight>(Point3::origin() + Vector3::up() * 3,
                                         Vector3::all(10.)),
        },
    };

    std::cout << scene << std::endl;
    return 0;
}
