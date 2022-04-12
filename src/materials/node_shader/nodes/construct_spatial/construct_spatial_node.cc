#include "construct_spatial_node.hh"

namespace raytracer::materials::node_shader::nodes
{
    ConstructSpatialNode::ConstructSpatialNode(PinAdressMap inputs)
        : super_type(inputs)
    {
        result_pin_ = std::make_shared<ValueProvider>(Vector3::zero(), this);

        outputs_ = {
            { "result", result_pin_ },
        };
    }

    void ConstructSpatialNode::compute(ComputationIdType cid) const
    {
        const auto x = std::get<double>(inputs_.at("x")->get(cid));
        const auto y = std::get<double>(inputs_.at("y")->get(cid));
        const auto z = std::get<double>(inputs_.at("z")->get(cid));

        const auto result = Vector3(x, y, z);

        result_pin_->set(result, cid);
    }

    std::string ConstructSpatialNode::node_type_() const
    {
        return "ConstructSpatialNode";
    }
} // namespace raytracer::materials::node_shader::nodes
