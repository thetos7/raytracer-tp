#include "destruct_spatial_node.hh"

namespace raytracer::materials::node_shader::nodes
{
    DestructSpatialNode::DestructSpatialNode(PinAdressMap inputs)
        : super_type(inputs)
    {
        x_pin_ = std::make_shared<ValueProvider>(0., this);
        y_pin_ = std::make_shared<ValueProvider>(0., this);
        z_pin_ = std::make_shared<ValueProvider>(0., this);

        outputs_ = {
            { "x", x_pin_ },
            { "y", y_pin_ },
            { "z", z_pin_ },
        };
    }

    void DestructSpatialNode::compute(ComputationIdType cid) const
    {
        const auto input = std::get<Vector3>(inputs_.at("in")->get(cid));

        const auto x = input.x;
        const auto y = input.y;
        const auto z = input.z;

        x_pin_->set(x, cid);
        y_pin_->set(y, cid);
        z_pin_->set(z, cid);
    }

    std::string DestructSpatialNode::node_type_() const
    {
        return "DestructSpatialNode";
    }
} // namespace raytracer::materials::node_shader::nodes
