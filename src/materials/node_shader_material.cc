#include "node_shader_material.hh"

#include "intersection/intersection.hh"
#include "node_shader/node_shader.hh"

namespace raytracer::materials
{
    NodeShaderMaterial::NodeShaderMaterial(ShaderPtr shader)
        : shader_{ shader }
    {}

    const MaterialProperties
    NodeShaderMaterial::get_point_properties(Intersection intersection) const
    {
        return shader_->compute_material_properties(intersection);
    }
} // namespace raytracer::materials
