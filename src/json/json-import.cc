#include "json-import.hh"

#include <fstream>
#include <iostream>

#include "lights/ambient_light.hh"
#include "lights/point_light.hh"
#include "lights/sun_light.hh"
#include "materials/textured_material.hh"
#include "materials/uniform_material.hh"
#include "objects/blob.hh"
#include "objects/blob_sources/blob_point.hh"
#include "objects/plane.hh"
#include "objects/sphere.hh"
#include "objects/triangle.hh"
#include "points/point3.hh"
#include "vectors/vector3.hh"
#include "colors/rgb.hh"

using namespace points;
using namespace vectors;
using namespace raytracer::lights;
using namespace raytracer::materials;
using json = nlohmann::json;
using namespace raytracer::objects;
using PointsType = std::array<points::Point3, 3>;

namespace raytracer
{
    JsonImport::JsonImport(const std::string &jsonPath)
    {
        this->scene = Scene();
        this->loadJsonObject(jsonPath);
    }

    Scene JsonImport::importScene()
    {
        loadCamera();
        loadMaterials();
        loadLights();
        loadObjects();
        return scene;
    }

    void JsonImport::loadJsonObject(const std::string &jsonPath)
    {
        std::ifstream(jsonPath) >> this->jsonObject;
    }

    void JsonImport::loadCamera()
    {
        std::cout << "Loading camera.\n";
        json cameraJsonObject = jsonObject["camera"];
        scene.camera_ =
            Camera(Point3::from_vector(
                       cameraJsonObject["position"].get<std::vector<double>>()),
                   Point3::from_vector(
                       cameraJsonObject["focus"].get<std::vector<double>>()),
                   Vector3::from_vector(
                       cameraJsonObject["up"].get<std::vector<double>>()),
                   cameraJsonObject["fov"].get<double>(),
                   cameraJsonObject["aspectRatio"].get<double>(),
                   cameraJsonObject["zmin"].get<double>());
        std::cout << "Loaded camera from json." << '\n';
        std::cout << scene.camera_ << '\n';
    }

    void JsonImport::loadMaterials()
    {
        std::cout << "Loading materials.\n";
        json materialsJsonObject = jsonObject["materials"];
        for (auto materialJsonObject : materialsJsonObject)
        {
            std::string type = materialJsonObject["type"];
            if (type == "uniform")
            {
                auto m = std::make_shared<UniformMaterial>(
                    Vector3::from_vector(materialJsonObject["diffuse"]
                                             .get<std::vector<double>>()),
                    materialJsonObject["specular"].get<double>(),
                    materialJsonObject["specularSpread"].get<double>(),
                    materialJsonObject["reflectivity"].get<double>());
                std::string name =
                    materialJsonObject["name"].get<std::string>();
                materials[name] = m;
                std::cout << "Loaded uniform material \"" << name
                          << "\" from json.\n";
            }
            if (type == "textured")
            {
                auto m = std::make_shared<TexturedMaterial>(
                    image::RgbImage::load_from_png(
                        materialJsonObject["diffuseMap"].get<std::string>()),
                    image::RgbImage::load_from_png(
                        materialJsonObject["specularMap"].get<std::string>()),
                    materialJsonObject["specularSpread"].get<double>(),
                    materialJsonObject["reflectivity"].get<double>());
            }
        }
    }

    void JsonImport::loadLights()
    {
        std::cout << "Loading lights.\n";
        json lightsJsonObject = jsonObject["lights"];
        for (auto lightJsonObject : lightsJsonObject)
        {
            std::string type = lightJsonObject["type"];
            if (type == "ambientLight")
            {
                auto l = std::make_shared<AmbientLight>(Vector3::from_vector(
                    lightJsonObject["color"].get<std::vector<double>>()));
                scene.lights_.push_back(l);
                std::cout << "Loaded an ambient light from json.\n";
                std::cout << *l << '\n';
            }
            else if (type == "pointLight")
            {
                auto l = std::make_shared<PointLight>(
                    Point3::from_vector(
                        lightJsonObject["position"].get<std::vector<double>>()),
                    Vector3::from_vector(lightJsonObject["intensity"]
                                             .get<std::vector<double>>()));
                scene.lights_.push_back(l);
                std::cout << "Loaded a point light from json.\n";
                std::cout << *l << '\n';
            }
            else if (type == "sunLight")
            {
                auto l = std::make_shared<SunLight>(
                    Vector3::from_vector(lightJsonObject["direction"]
                                             .get<std::vector<double>>()),
                    Vector3::from_vector(
                        lightJsonObject["color"].get<std::vector<double>>()));
                scene.lights_.push_back(l);
                std::cout << "Loaded a sun light from json.\n";
                std::cout << *l << '\n';
            }
        }
    }

    void JsonImport::loadObjects()
    {
        std::cout << "Loading objects.\n";
        json objectsJsonObject = jsonObject["objects"];
        for (auto objectJsonObject : objectsJsonObject)
        {
            std::string type = objectJsonObject["type"];
            auto mat =
                materials[objectJsonObject["material"].get<std::string>()];
            if (type == "sphere")
            {
                auto o = std::make_shared<Sphere>(
                    Point3::from_vector(
                        objectJsonObject["center"].get<std::vector<double>>()),
                    objectJsonObject["radius"].get<double>(), mat);
                scene.objects_.push_back(o);
                std::cout << "Loaded a sphere from json.\n";
                std::cout << *o << '\n';
            }
            else if (type == "plane")
            {
                auto o = std::make_shared<Plane>(
                    Point3::from_vector(objectJsonObject["reference"]
                                            .get<std::vector<double>>()),
                    Vector3::from_vector(
                        objectJsonObject["normal"].get<std::vector<double>>()),
                    mat);
                scene.objects_.push_back(o);
                std::cout << "Loaded a plane from json.\n";
                std::cout << *o << '\n';
            }
            else if (type == "triangle")
            {
                using VectorList = std::vector<std::vector<double>>;
                constexpr auto POINTS_KEY = "points";
                constexpr auto NORMALS_KEY = "normals";
                constexpr auto UV_MAP_KEY = "uvMap";
                PointsType ptsType;
                Triangle::NormalsType normals;
                Triangle::UvsType uv_map;
                bool hasNormals = objectJsonObject.contains(NORMALS_KEY);
                int i = 0;
                for (auto point :
                     objectJsonObject[POINTS_KEY].get<VectorList>())
                {
                    ptsType[i] = Point3::from_vector(point);
                    i++;
                    if (i > 2)
                        break;
                }

                if (hasNormals)
                {
                    int i = 0;
                    for (auto normal :
                         objectJsonObject[NORMALS_KEY].get<VectorList>())
                    {
                        normals[i] = Vector3::from_vector(normal);
                        ++i;
                        if (i > 2)
                            break;
                    }
                }

                if (objectJsonObject.contains(UV_MAP_KEY))
                {
                    int i = 0;
                    for (auto uv :
                         objectJsonObject[UV_MAP_KEY].get<VectorList>())
                    {
                        uv_map[i] = Vector2::from_vector(uv);
                        ++i;
                        if (i > 2)
                            break;
                    }
                }
                else
                {
                    uv_map = Triangle::DEFAULT_UVS;
                }

                auto o = std::make_shared<Triangle>(ptsType, normals, uv_map,
                                                    !hasNormals, mat);
                scene.objects_.push_back(o);
                std::cout << "Loaded a triangle from json.\n";
                std::cout << *o << '\n';
            }
            else if (type == "blob")
            {
                auto center = Point3::from_vector(
                    objectJsonObject["center"].get<std::vector<double>>());
                auto size = objectJsonObject["size"].get<double>();
                auto divisions = objectJsonObject["divisions"].get<size_t>();
                auto threshold = objectJsonObject["threshold"].get<double>();
                auto sources =
                    std::vector<std::shared_ptr<blob_sources::BlobSource>>();
                for (json sourceJsonObject : objectJsonObject["sources"])
                {
                    std::string sourceType = sourceJsonObject["type"];
                    if (sourceType == "point")
                    {
                        auto radius = sourceJsonObject["radius"].get<double>();
                        auto center = Point3::from_vector(
                            sourceJsonObject["center"]
                                .get<std::vector<double>>());
                        auto blobPoint =
                            std::make_shared<blob_sources::BlobPoint>(radius,
                                                                      center);
                        sources.push_back(blobPoint);
                    }
                }
                auto o = std::make_shared<Blob>(center, size, divisions,
                                                threshold, sources, mat);
                scene.objects_.push_back(o);
                std::cout << "Loaded a blob from json.\n";
                std::cout << *o << '\n';
            }
        }
    }
} // namespace raytracer
