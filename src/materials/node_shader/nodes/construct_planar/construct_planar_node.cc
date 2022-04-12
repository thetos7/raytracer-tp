#include "construct_planar_node.hh"

namespace raytracer::materials::node_shader::nodes
{
    ConstructPlanarNode::ConstructPlanarNode(PinAdressMap inputs)
        : super_type(inputs)
    {
        result_pin_ = std::make_shared<ValueProvider>(Vector2::zero(), this);

        outputs_ = {
            { "result", result_pin_ },
        };
    }

    void ConstructPlanarNode::compute(ComputationIdType cid) const
    {
        const auto x = std::get<double>(inputs_.at("x")->get(cid));
        const auto y = std::get<double>(inputs_.at("y")->get(cid));

        const auto result = Vector2(x, y);

        result_pin_->set(result, cid);
    }

    std::string ConstructPlanarNode::node_type_() const
    {
        return "ConstructPlanarNode";
    }
} // namespace raytracer::materials::node_shader::nodes
