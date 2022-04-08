#include "node_shader.hh"

#include <stdexcept>

namespace raytracer::materials::node_shader
{
    NodeShader::NodeShader(NodeCollection nodes, OutputPinType diffuse_output,
                           OutputPinType specular_output,
                           OutputPinType specular_spread_output,
                           OutputPinType reflectivity_output)
        : nodes_(nodes)
        , diffuse_output_(diffuse_output)
        , specular_output_(specular_output)
        , specular_spread_output_(specular_spread_output)
        , reflectivity_output_(reflectivity_output)
        , era_(0)
    {}

    MaterialProperties
    NodeShader::compute_material_properties(const Intersection &Intersection)
    {
        era_++;
        throw std::logic_error("Not Implemented Yet"); // FIXME
    }

    NodeShader::EraType NodeShader::get_era() const
    {
        return era_;
    }
} // namespace raytracer::materials::node_shader
