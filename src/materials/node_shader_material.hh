#pragma once

#include <memory>

#include "material.hh"
#include "node_shader/fwd.hh"

namespace raytracer::materials
{
    class NodeShaderMaterial : public Material
    {
    public:
        using NodeShader = node_shader::NodeShader;
        using ShaderPtr = std::shared_ptr<NodeShader>;
        NodeShaderMaterial(ShaderPtr shader);

        virtual const MaterialProperties
        get_point_properties(Intersection intersection) const override;

    private:
        ShaderPtr shader_;
    };

} // namespace raytracer::materials
