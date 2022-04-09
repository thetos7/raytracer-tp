#include "value_node.hh"

namespace raytracer::materials::node_shader::nodes
{
    ValueNode::ValueNode(NodeData value)
        : super_type({})
        , value_(value)
    {}

    void ValueNode::compute(ComputationIdType cid) const
    {
        out_pin_->set(value_, cid);
    }

    std::string ValueNode::node_type_() const
    {
        return "ValueNode";
    }
} // namespace raytracer::materials::node_shader::nodes
