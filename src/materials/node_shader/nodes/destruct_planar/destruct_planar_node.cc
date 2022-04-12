#include "destruct_planar_node.hh"

namespace raytracer::materials::node_shader::nodes
{
    DestructPlanarNode::DestructPlanarNode(PinAdressMap inputs)
        : super_type(inputs)
    {
        x_pin_ = std::make_shared<ValueProvider>(0., this);
        y_pin_ = std::make_shared<ValueProvider>(0., this);

        outputs_ = {
            { "x", x_pin_ },
            { "y", y_pin_ },
        };
    }

    void DestructPlanarNode::compute(ComputationIdType cid) const
    {
        const auto input = std::get<Vector2>(inputs_.at("in")->get(cid));

        const auto x = input.x;
        const auto y = input.y;

        x_pin_->set(x, cid);
        y_pin_->set(y, cid);
    }

    std::string DestructPlanarNode::node_type_() const
    {
        return "DestructPlanarNode";
    }
} // namespace raytracer::materials::node_shader::nodes
