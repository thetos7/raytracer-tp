#pragma once

#include "materials/node_shader/nodes/node.hh"

namespace raytracer::materials::node_shader::nodes
{
    class ValueNode : public Node
    {
    public:
        // Inputs:
        // in: Vector2 - vector to convert
        using super_type = Node;

        ValueNode(NodeData value);
        virtual void compute(ComputationIdType cid) const override;

    private:
        virtual std::string node_type_() const override;
        NodeData value_;
        PinType value_pin_;
    };

} // namespace raytracer::materials::node_shader::nodes