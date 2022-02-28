#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>

#include "colors/rgb.hh"
#include "image/image.hh"
#include "intersection/intersection.hh"
#include "lights/light.hh"
#include "lights/point_light.hh"
#include "materials/uniform_material.hh"
#include "objects/object.hh"
#include "objects/sphere.hh"
#include "points/point3.hh"
#include "scene/scene.hh"
#include "vectors/vector3.hh"

using Image = image::Image;
using namespace raytracer;

std::shared_ptr<Image> raytrace(const Scene &scene, const int &height)
{
    using namespace colors;
    const auto &camera = scene.camera();
    const auto width =
        static_cast<int>(std::round(camera.aspectRatio * height));
    auto output = std::make_shared<Image>(width, height);
    const auto imagePlaneWidthHalf = std::tan(camera.fov / 2.) * camera.zMin;
    const auto imagePlaneWidth = imagePlaneWidthHalf * 2;
    const auto pixelSize = imagePlaneWidth / width;
    const auto imagePlaneCenter =
        camera.position + camera.forward * camera.zMin;
    const auto floatImageWidthHalf = static_cast<double>(width) / 2;
    const auto floatImageHeightHalf = static_cast<double>(height) / 2;

    for (auto y = 0; y < height; ++y)
    {
        for (auto x = 0; x < width; ++x)
        {
            const auto rayOrigin = imagePlaneCenter
                + (x - floatImageWidthHalf) * camera.right * pixelSize
                + (y - floatImageHeightHalf) * camera.up * pixelSize;
            // std::cout << "ray origin: " << rayOrigin << "\n";
            const auto rayDirection = rayOrigin - camera.position;

            const Ray ray{ rayOrigin, rayDirection };
            auto intersection = scene.cast_ray(ray);
            if (intersection)
            {
                output->pixel_set(x, y, RGB::white());
            }
        }
    }

    return output;
}

int main(int argc, char *argv[])
{
    using namespace points;
    using namespace vectors;
    using namespace materials;
    using namespace lights;

    constexpr int height = 480;
    constexpr double aspectRatio = 16. / 9.;
    constexpr int width = height * aspectRatio;
    constexpr double fieldOfView = (90. / 180.) * M_PI;

    auto greyUniform = std::make_shared<UniformTexture>(UniformTexture{
        Vector3::all(0.7),
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
    const auto output = raytrace(scene, height);
    output->save_ppm("result.ppm");
    return 0;
}
