#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>

#include "colors/rgb.hh"
#include "engine/engine.hh"
#include "image/linear_image.hh"
#include "image/rgb_image.hh"
#include "intersection/intersection.hh"
#include "json/json-import.hh"
#include "lights/ambient_light.hh"
#include "lights/point_light.hh"
#include "lights/sun_light.hh"
#include "materials/shader_material.hh"
#include "materials/textured_material.hh"
#include "materials/uniform_material.hh"
#include "objects/blob.hh"
#include "objects/blob_sources/blob_point.hh"
#include "objects/mesh.hh"
#include "objects/plane.hh"
#include "objects/sphere.hh"
#include "objects/triangle.hh"
#include "points/point3.hh"
#include "scene/scene.hh"
#include "utils/utils.hh"
#include "vectors/vector2.hh"
#include "vectors/vector3.hh"
#include "vectors/rot_matrix3.hh"

using namespace points;
using namespace vectors;
using raytracer::materials::MaterialProperties;
using raytracer::materials::ShaderMaterial;
using raytracer::materials::UniformMaterial;
using raytracer::materials::TexturedMaterial;
using raytracer::lights::PointLight;
using raytracer::lights::SunLight;
using raytracer::lights::AmbientLight;
using raytracer::objects::Sphere;
using raytracer::objects::Plane;
using raytracer::objects::Triangle;
using raytracer::objects::Mesh;
using raytracer::objects::Blob;
using raytracer::objects::blob_sources::BlobPoint;
using raytracer::Intersection;
using raytracer::Scene;
using raytracer::Camera;
using colors::RGB;

constexpr auto VORO_SIZE = 5;
constexpr auto VORO_CELL_SIZE = 1. / VORO_SIZE;
size_t voro_idx(int x, int y)
{
    return (y + 1) * (VORO_SIZE + 2) + (x + 1);
}

double randfloat()
{
    return static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX);
}

double voronoi(Vector2 uv)
{
    static std::vector<Vector2> points((VORO_SIZE + 2) * (VORO_SIZE + 2));
    static bool initialized = false;
    if (!initialized)
    {
        for (int y = 0; y < VORO_SIZE; ++y)
            for (int x = 0; x < VORO_SIZE; ++x)
            {
                auto px = randfloat() * VORO_CELL_SIZE;
                auto py = randfloat() * VORO_CELL_SIZE;
                points[voro_idx(y, x)] = { px, py };
            }
        for (int x = 0; x < VORO_SIZE; ++x)
        {
            points[voro_idx(x, -1)] = points[voro_idx(x, VORO_SIZE - 1)];
            points[voro_idx(x, VORO_SIZE)] = points[voro_idx(x, 0)];
        }
        for (int y = -1; y < VORO_SIZE + 1; ++y)
        {
            points[voro_idx(-1, y)] = points[voro_idx(VORO_SIZE - 1, y)];
            points[voro_idx(VORO_SIZE, y)] = points[voro_idx(0, y)];
        }
        for (int y = -1; y < VORO_SIZE + 1; ++y)
            for (int x = -1; x < VORO_SIZE + 1; ++x)
            {
                auto &p = points[voro_idx(x, y)];
                p.x += x * VORO_CELL_SIZE;
                p.y += y * VORO_CELL_SIZE;
            }
        initialized = true;
    }
    double nearest_dist = 4;
    const auto u = uv.x;
    const auto v = uv.y;
    const int cx = static_cast<int>(std::floor(u / VORO_CELL_SIZE));
    const int cy = static_cast<int>(std::floor(v / VORO_CELL_SIZE));

    for (int ox = -1; ox <= 1; ++ox)
        for (int oy = -1; oy <= 1; ++oy)
        {
            nearest_dist = std::min(
                nearest_dist, (uv - points[voro_idx(cx + ox, cy + oy)]).norm());
        }
    const auto dist = nearest_dist / (VORO_CELL_SIZE);
    return std::clamp(dist, 0., 1.);
}

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        raytracer::JsonImport jsonImport = raytracer::JsonImport(argv[1]);
        auto scene = jsonImport.importScene();
        std::cout << "Scene built:" << std::endl;
        std::cout << scene << std::endl;

        constexpr int height = 480;
        const auto output = raytracer::raytrace(scene, height, 3, true, 5);
        output->save_ppm("result.ppm");
        return 0;
    }

    std::srand(std::time(0));
    constexpr int height = 480;
    constexpr double aspectRatio = 16. / 9.;
    constexpr int width = height * aspectRatio;
    constexpr double fieldOfView = (90. / 180.) * M_PI;

    auto minecraftTexture = std::make_shared<TexturedMaterial>(TexturedMaterial{
        image::RgbImage::load_from_png("../Testing/textures/grass/diffuse.png"),
        image::RgbImage::load_from_png(
            "../Testing/textures/grass/specular.png"),
        0., 0. });

    auto lightGreyUniform = std::make_shared<UniformMaterial>(UniformMaterial{
        Vector3::all(0.8),
        0.,
        1.,
        1.,
    });
    auto redUniform = std::make_shared<UniformMaterial>(UniformMaterial{
        Vector3(0.9, 0.2, 0.2),
        0.1,
        .8,
        0.05,
    });
    auto orangeUniform = std::make_shared<UniformMaterial>(UniformMaterial{
        Vector3(1.0, 0.5, 0.1),
        0.,
        1.,
        0.,
    });
    auto greenUniform = std::make_shared<UniformMaterial>(UniformMaterial{
        Vector3(0.1, 0.6, 0.1),
        0.5,
        16.,
        0.5,
    });
    auto lightBlueUniform = std::make_shared<UniformMaterial>(UniformMaterial{
        Vector3(0.5, 0.5, 0.7),
        0.,
        1.,
        0.,
    });
    auto purpleUniform = std::make_shared<UniformMaterial>(UniformMaterial{
        Vector3(0.7, 0., 1.0),
        0.,
        1.,
        0.,
    });

    auto voronoiMaterial = std::make_shared<ShaderMaterial>(
        [&](const Intersection &intersection, MaterialProperties &props) {
            auto fact = voronoi(Vector2(intersection.u, intersection.v));
            props.diffuse =
                Vector3(0.9, 0.9, 0.2).lerp_to(Vector3(0.9, 0.5, 0.1), fact);
        });

    auto uvDebugMaterial = std::make_shared<ShaderMaterial>(
        [](const Intersection &intersection, MaterialProperties &props) {
            props.diffuse.x = intersection.u;
            props.diffuse.y = intersection.v;
        });

    const auto camPos = Point3(0, -1, 1);
    const auto camPoint = Point3(2, 0, 0);
    const auto camUp = Vector3::up();
    const auto redSphere =
        std::make_shared<Sphere>(Point3(4, 0, 0), 1., minecraftTexture);
    const auto debugSphere =
        std::make_shared<Sphere>(Point3(4, 0, 0), 1., uvDebugMaterial);
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
        voronoiMaterial);

    const auto cubeMesh = std::make_shared<Mesh>(Mesh::loadFromObj("../Testing/obj_files/weird_tris.obj", orangeUniform, Vector3(3, 2, 0), 0.3, RotMatrix3(M_PI_2, 0, 0)));

    // const auto purpleBlob = std::make_shared<Blob>(
    //     Point3(2, 0, 0), 2.2, 33, 0.4,
    //     Blob::SourceCollection{
    //         std::make_shared<BlobPoint>(0.75, Point3(2, -0.35, 0)),
    //         std::make_shared<BlobPoint>(0.75, Point3(2, 0.35, 0)),
    //     },
    //     purpleUniform);

    Scene scene{
        Camera{
            camPos,
            camPoint,
            camUp,
            fieldOfView,
            aspectRatio,
            0.5,
        },
        Scene::ObjectCollection{
            // purpleBlob,
            redSphere,
            orangeSphere,
            greenSphere,
            lightGreyPlane,
            backgroundPlane,
            // redTriangle,
            cubeMesh,
        },
        Scene::LightCollection{
            std::make_shared<AmbientLight>(Vector3::all(.05)),
            std::make_shared<PointLight>(Point3::origin() + Vector3::up() * 3,
                                         Vector3::all(0.5)),
            std::make_shared<SunLight>(Vector3(0.5, -1, -1),
                                       Vector3(0.7, 0.7, 0.55)),
        },
    };

    std::cout << "Scene built:" << std::endl;
    std::cout << scene << std::endl;

    const auto output = raytracer::raytrace(scene, height, 3, true, 5);
    output->save_ppm("result.ppm");
    return 0;
}
