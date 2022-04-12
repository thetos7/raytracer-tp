#pragma once

#include "materials/node_shader/nodes/node.hh"
#include "math_operations.hh"

namespace raytracer::materials::node_shader::nodes
{
    class UnaryMathNode : public Node
    {
    public:
        // Inputs:
        // in: Any - operand
        using super_type = Node;

        UnaryMathNode(PinAdressMap inputs, UnaryMathOp op);
        virtual void compute(ComputationIdType cid) const override;

    private:
        virtual std::string node_type_() const override;
        PinType result_pin_;
        UnaryMathOp op_;
    };

} // namespace raytracer::materials::node_shader::nodes
