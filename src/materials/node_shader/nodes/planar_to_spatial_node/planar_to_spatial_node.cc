#include "planar_to_spatial_node.hh"

namespace raytracer::materials::node_shader::nodes
{
    PlanarToSpatialNode::PlanarToSpatialNode(PinAdressMap inputs)
        : super_type(inputs)
    {
        out_pin_ = std::make_shared<ValueProvider>(Vector3::zero(), this);
        outputs_ = {
            { "out", out_pin_ },
        };
    }

    void PlanarToSpatialNode::compute(ComputationIdType cid) const
    {
        auto input = std::get<Vector2>(inputs_.at("in")->get(cid));
        out_pin_->set(Vector3(input.x, input.y, 0.), cid);
    }

    std::string PlanarToSpatialNode::node_type_() const
    {
        return "PlanarToSpatialNode";
    }
} // namespace raytracer::materials::node_shader::nodes
