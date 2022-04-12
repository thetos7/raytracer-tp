#include "wave_texture_node.hh"

#include <cmath>

namespace raytracer::materials::node_shader::nodes
{
    WaveTextureNode::WaveTextureNode(PinAdressMap inputs, double angle,
                                     double scale, double offset)
        : super_type(inputs)
        , angle_(angle)
        , scale_(scale)
        , offset_(offset)
        , direction_(std::cos(angle), std::sin(angle))
    {
        factor_pin_ = std::make_shared<ValueProvider>(0., this);

        outputs_ = {
            { "factor", factor_pin_ },
        };
    }

    void WaveTextureNode::compute(ComputationIdType cid) const
    {
        const auto uv = std::get<Vector2>(inputs_.at("uv")->get(cid)).fract();

        const auto result = std::sin(direction_.dot(uv) * scale_ + offset_);

        factor_pin_->set(result, cid);
    }

    std::string WaveTextureNode::node_type_() const
    {
        return "WaveTextureNode";
    }
} // namespace raytracer::materials::node_shader::nodes
