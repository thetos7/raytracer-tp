#pragma once

#include <map>

#include "json.hpp"
#include "materials/material.hh"
#include "scene/scene.hh"

using json = nlohmann::json;

namespace raytracer
{
    class JsonImport
    {
    public:
        JsonImport(const std::string &jsonPath);
        Scene importScene();

    private:
        Scene scene;
        nlohmann::json jsonObject;
        std::map<std::string, std::shared_ptr<materials::Material>> materials;
        void loadJsonObject(const std::string &jsonPath);
        void loadCamera();
        void loadMaterials();
        void loadLights();
        void loadObjects();
    };
} // namespace raytracer