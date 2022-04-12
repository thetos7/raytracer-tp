#include "json-import.hh"

#include <fstream>
#include <iostream>

#include "colors/rgb.hh"
#include "lights/ambient_light.hh"
#include "lights/point_light.hh"
#include "lights/sun_light.hh"
#include "materials/node_shader/node_shader.hh"
#include "materials/node_shader/nodes/all_nodes.hh"
#include "materials/node_shader_material.hh"
#include "materials/textured_material.hh"
#include "materials/uniform_material.hh"
#include "objects/blob.hh"
#include "objects/blob_sources/blob_point.hh"
#include "objects/plane.hh"
#include "objects/sphere.hh"
#include "objects/triangle.hh"
#include "points/point3.hh"
#include "vectors/vector3.hh"

using namespace points;
using namespace vectors;
using namespace raytracer::lights;
using namespace raytracer::materials;
using json = nlohmann::json;
using namespace raytracer::objects;
using PointsType = std::array<points::Point3, 3>;
using namespace node_shader;
using namespace nodes;

namespace raytracer
{
    static void missingFieldErrorMessage(const std::string &fieldMissing,
                                         const std::string &objectName)
    {
        std::cerr << "Missing or invalid field \"" << fieldMissing
                  << "\" in object \"" << objectName << "\".\n";
    }

    std::optional<Node::PinAdressMap> loadInputs(const json &obj)
    {
        Node::PinAdressMap inputs;
        if (!obj.is_object())
        {
            std::cerr << "input map is not an object\n";
            return {};
        }
        for (auto &[k, v] : obj.items())
        {
            if (!v.is_string())
            {
                missingFieldErrorMessage(k, "inputs");
                continue;
            }
            auto str_value = v.get<std::string>();
            inputs.insert({ k, PinAddress::from_str(str_value) });
        }
        return inputs;
    }

    std::optional<NodeData> loadAnyNodeData(const json &data)
    {
        if (data.is_number_float())
        {
            return data.get<double>();
        }
        if (data.is_array())
        {
            const auto v = data.get<std::vector<double>>();
            if (v.size() == 2)
            {
                return Vector2::from_vector(v);
            }
            if (v.size() == 3)
            {
                return Vector3::from_vector(v);
            }
        }
        return std::nullopt;
    }

    std::shared_ptr<Node> loadNode(const json &obj)
    {
        const auto type = obj["type"].get<std::string>();
        if (type == "intersection_info")
        {
            return std::make_shared<IntersectionInfoNode>();
        } // intersection_info
        if (type == "voronoi_texture")
        {
            const auto inputs = *loadInputs(obj["inputs"]);
            int size = 5;
            if (obj.contains("size"))
            {
                size = obj["size"].get<int>();
            }
            return std::make_shared<VoronoiTextureNode>(inputs, size);
        } // voronoi_texture
        if (type == "scalar_to_spatial")
        {
            const auto inputs = *loadInputs(obj["inputs"]);
            return std::make_shared<ScalarToSpatialNode>(inputs);
        } // scalar_to_spatial
        if (type == "color_ramp")
        {
            const auto inputs = *loadInputs(obj["inputs"]);
            if (!(obj.contains("stops") && obj["stops"].is_array()))
            {
                missingFieldErrorMessage("stops", "color_ramp");
                return nullptr;
            }
            ColorRampNode::StopCollection stops;
            for (const auto &stop : obj["stops"])
            {
                if (!(stop.contains("value")
                      && stop["value"].is_number_float()))
                {
                    missingFieldErrorMessage("value", "ColorStop");
                    return nullptr;
                }
                if (!(stop.contains("color") && stop["color"].is_array()))
                {
                    missingFieldErrorMessage("color", "ColorStop");
                    return nullptr;
                }
                const auto value = stop["value"].get<double>();
                const auto color = Vector3::from_vector(
                    stop["color"].get<std::vector<double>>());
                stops.emplace_back(value, color);
            }
            return std::make_shared<ColorRampNode>(inputs, stops);
        } // color_ramp
        if (type == "value")
        {
            if (!(obj.contains("value")))
            {
                missingFieldErrorMessage("value", "ValueNode");
                return nullptr;
            }
            const auto value = loadAnyNodeData(obj["value"]);
            if (!value)
            {
                std::cerr << "field `value` of ValueNode does not match any "
                             "NodeData type\n";
                return nullptr;
            }
            return std::make_shared<ValueNode>(*value);
        } // value
        return nullptr;
    }

    std::shared_ptr<NodeShader> loadNodeShader(const json &obj)
    {
        std::optional<PinAddress> diffuse;
        std::optional<PinAddress> specular;
        std::optional<PinAddress> specular_spread;
        std::optional<PinAddress> reflectivity;
        if (obj.contains("diffuse_output") && obj["diffuse_output"].is_string())
        {
            diffuse =
                PinAddress::from_str(obj["diffuse_output"].get<std::string>());
        }
        if (obj.contains("specular_output")
            && obj["specular_output"].is_string())
        {
            specular =
                PinAddress::from_str(obj["specular_output"].get<std::string>());
        }
        if (obj.contains("specular_spread_output")
            && obj["specular_spread_output"].is_string())
        {
            specular_spread = PinAddress::from_str(
                obj["specular_spread_output"].get<std::string>());
        }
        if (obj.contains("reflectivity_output")
            && obj["reflectivity_output"].is_string())
        {
            reflectivity = PinAddress::from_str(
                obj["reflectivity_output"].get<std::string>());
        }
        if (!(diffuse || specular || specular_spread || reflectivity))
        {
            std::cerr << "Warning: Node shader has no output defined.\n";
        }
        if (!obj.contains("nodes"))
        {
            missingFieldErrorMessage("nodes", "node_shader");
            return nullptr; // should SEGV
        }

        NodeShader::NodeCollection nodes;
        for (auto &[node_name, node_obj] : obj["nodes"].items())
        {
            if (!node_obj.is_object())
            {
                std::cerr << "Node `" << node_name
                          << "` is not an object, skipping";
                continue;
            }
            nodes.insert({ node_name, loadNode(node_obj) });
        }

        return std::make_shared<NodeShader>(nodes, diffuse, specular,
                                            specular_spread, reflectivity);
    }

    JsonImport::JsonImport(const std::string &jsonPath)
    {
        this->jsonPath = jsonPath;
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
            if (!materialJsonObject.contains("type"))
            {
                missingFieldErrorMessage("type", "Material");
                std::cerr << "Missing mandatory material field, skipping...\n";
                continue;
            }
            std::string type = materialJsonObject["type"];
            if (!materialJsonObject.contains("name"))
            {
                missingFieldErrorMessage("name", "Material");
                std::cerr << "Missing mandatory material field, skipping...\n";
                continue;
            }
            std::string name = materialJsonObject["name"].get<std::string>();
            if (type == "uniform")
            {
                auto m = std::make_shared<UniformMaterial>(
                    Vector3::from_vector(materialJsonObject["diffuse"]
                                             .get<std::vector<double>>()),
                    materialJsonObject["specular"].get<double>(),
                    materialJsonObject["specularSpread"].get<double>(),
                    materialJsonObject["reflectivity"].get<double>());
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
                materials[name] = m;
            }
            if (type == "node")
            {
                auto shader = loadNodeShader(materialJsonObject["shader"]);
                auto m = std::make_shared<NodeShaderMaterial>(shader);
                materials[name] = m;
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
        if (!jsonObject.contains("objects")
            || !jsonObject["objects"].is_array())
        {
            missingFieldErrorMessage("objects", "JSON");
            return;
        }
        json objectsJsonObject = jsonObject["objects"];
        for (auto objectJsonObject : objectsJsonObject)
        {
            if (!objectJsonObject.contains("type")
                || !objectJsonObject["type"].is_string())
            {
                missingFieldErrorMessage("type", "Object");
                continue;
            }
            std::string type = objectJsonObject["type"];
            if (!objectJsonObject.contains("material")
                || !objectJsonObject["material"].is_string())
            {
                missingFieldErrorMessage("material", type);
                continue;
            }
            const auto mat_name =
                objectJsonObject["material"].get<std::string>();
            auto mat = materials[mat_name];
            if (mat == nullptr)
            {
                std::cerr << "Material `" << mat_name
                          << "` not found or null.\nPlease verify that your "
                             "objects reference existing listed materials.";
            }
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
            else if (type == "mesh_obj")
            {
                if (!objectJsonObject.contains("objPath")
                    || !objectJsonObject["objPath"].is_string())
                {
                    missingFieldErrorMessage("objPath", type);
                    continue;
                }
                auto path = objectJsonObject["objPath"].get<std::string>();
                if (!objectJsonObject.contains("center")
                    || !objectJsonObject["center"].is_array())
                {
                    missingFieldErrorMessage("center", type);
                    continue;
                }
                auto center = Vector3::from_vector(
                    objectJsonObject["center"].get<std::vector<double>>());
                double scale = 0.;
                if (objectJsonObject.contains("scale")
                    && objectJsonObject["scale"].is_number())
                    scale = objectJsonObject["scale"].get<double>();
                auto rotate = Vector3(0., 0., 0.);
                if (objectJsonObject.contains("rotate")
                    && objectJsonObject["rotate"].is_array())
                    rotate = Vector3::from_vector(
                        objectJsonObject["rotate"].get<std::vector<double>>());
                auto o = std::make_shared<Mesh>(Mesh::loadFromObj(
                    path, mat, center, scale,
                    RotMatrix3(rotate.x * M_PI / 180, rotate.y * M_PI / 180, rotate.z * M_PI / 180)));
                scene.objects_.push_back(o);
            }
        }
    }
} // namespace raytracer
