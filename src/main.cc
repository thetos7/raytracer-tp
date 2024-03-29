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
#include "materials/node_shader/node_shader.hh"
#include "materials/node_shader/nodes/all_nodes.hh"
#include "materials/node_shader_material.hh"
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
using namespace raytracer::materials::node_shader;
using namespace nodes;
using raytracer::materials::MaterialProperties;
using raytracer::materials::ShaderMaterial;
using raytracer::materials::UniformMaterial;
using raytracer::materials::TexturedMaterial;
using raytracer::materials::NodeShaderMaterial;
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

int main(int argc, char *argv[])
{
    std::srand(std::time(0));
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

    auto nodeShaderUvMaterial = std::make_shared<
        NodeShaderMaterial>(NodeShaderMaterial{ std::make_shared<NodeShader>(
        NodeShader::NodeCollection{
            { "intersectionInfo", std::make_shared<IntersectionInfoNode>() },
            { "uvConverter",
              std::make_shared<PlanarToSpatialNode>(Node::PinAdressMap{
                  { "in", PinAddress::from_str("intersectionInfo.uv") } }) },
        },
        PinAddress::from_str("uvConverter.out"), std::nullopt, std::nullopt,
        std::nullopt) });

    auto nodeShaderFractalNoiseMaterial =
        std::make_shared<NodeShaderMaterial>(NodeShaderMaterial{
            std::make_shared<NodeShader>(
                NodeShader::NodeCollection{
                    { "intersectionInfo",
                      std::make_shared<IntersectionInfoNode>() },
                    { "fractalNoise",
                      std::make_shared<FractalNoiseTextureNode>(
                          Node::PinAdressMap{
                              { "uv",
                                PinAddress::from_str("intersectionInfo.uv") } },
                          3.0, 6) },
                    { "factorConverter",
                      std::make_shared<ScalarToSpatialNode>(Node::PinAdressMap{
                          { "in",
                            PinAddress::from_str("fractalNoise.factor") } }) },
                    { "specularSpreadConstant",
                      std::make_shared<ValueNode>(1.0) } },
                PinAddress::from_str("factorConverter.out"),
                PinAddress::from_str("fractalNoise.factor"),
                PinAddress::from_str("specularSpreadConstant.value"),
                std::nullopt),
        });
    auto nodeShaderVoronoiMaterial = std::make_shared<NodeShaderMaterial>(
        NodeShaderMaterial{ std::make_shared<NodeShader>(
            NodeShader::NodeCollection{
                { "intersectionInfo",
                  std::make_shared<IntersectionInfoNode>() },
                { "voronoi",
                  std::make_shared<VoronoiTextureNode>(
                      Node::PinAdressMap{
                          { "uv", PinAddress::from_str("intersectionInfo.uv") },
                      },
                      5 // voronoi size
                      ) },
                { "colorRamp",
                  std::make_shared<ColorRampNode>(
                      Node::PinAdressMap{
                          { "value", PinAddress::from_str("voronoi.factor") },
                      },
                      ColorRampNode::StopCollection{
                          { 0, { 0, 0, 1 } },
                          { .35, { 0, 1, 1 } },
                          { .5, { 0, 1, 0 } },
                          { 65, { 1, 1, 0 } },
                          { 1, { 1, 0, 0 } },
                      }) } },
            PinAddress::from_str("colorRamp.color"), std::nullopt, std::nullopt,
            std::nullopt) });

    auto uvDebugMaterial = std::make_shared<ShaderMaterial>(
        [](const Intersection &intersection, MaterialProperties &props) {
            props.diffuse.x = intersection.uv.x;
            props.diffuse.y = intersection.uv.y;
        });

    const auto camPos = Point3(0, 0, 0);
    const auto camPoint = Point3(4, 0, 0);
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

    const auto &texMaterial = nodeShaderFractalNoiseMaterial;
    const auto texTriangle1 = std::make_shared<Triangle>(
        Triangle::PointsType{
            Point3{ 2, 0, 1 },
            Point3{ 2, 1, 1 },
            Point3{ 2, 0, 0 },
        },
        Triangle::UvsType{
            Vector2{ 0, 0 },
            Vector2{ 1, 0 },
            Vector2{ 0, 1 },
        },
        texMaterial);
    const auto texTriangle2 = std::make_shared<Triangle>(
        Triangle::PointsType{
            Point3{ 2, 1, 1 },
            Point3{ 2, 1, 0 },
            Point3{ 2, 0, 0 },
        },
        Triangle::UvsType{
            Vector2{ 1, 0 },
            Vector2{ 1, 1 },
            Vector2{ 0, 1 },
        },
        texMaterial);

    const auto cubeMesh = std::make_shared<Mesh>(Mesh::loadFromObj("../Testing/obj_files/weird_tris.obj", orangeUniform, Vector3(3, 2, 0), 0.3, RotMatrix3(M_PI_2, 0, 0)));

    // The blob adds a lot of rendering time, it can take around 10mins with it
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
            texTriangle1,
            texTriangle2,
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
