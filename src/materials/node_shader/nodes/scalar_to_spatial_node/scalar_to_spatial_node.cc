#include "scalar_to_spatial_node.hh"

namespace raytracer::materials::node_shader::nodes
{
    ScalarToSpatialNode::ScalarToSpatialNode(PinAdressMap inputs)
        : super_type(inputs)
    {
        out_pin_ = std::make_shared<ValueProvider>(Vector3::zero(), this);
        outputs_ = {
            { "out", out_pin_ },
        };
    }

    void ScalarToSpatialNode::compute(ComputationIdType cid) const
    {
        auto input = std::get<double>(inputs_.at("in")->get(cid));
        out_pin_->set(Vector3::all(input), cid);
    }

    std::string ScalarToSpatialNode::node_type_() const
    {
        return "ScalarToSpatialNode";
    }
} // namespace raytracer::materials::node_shader::nodes
