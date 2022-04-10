#pragma once

#include "materials/node_shader/nodes/node.hh"
#include "math_operations.hh"

namespace raytracer::materials::node_shader::nodes
{
    class BinaryMathNode : public Node
    {
    public:
        // Inputs:
        // lhs: Any - left-hand side operand
        // rhs: Any - right-hand side operand
        using super_type = Node;

        BinaryMathNode(PinAdressMap inputs, BinaryMathOp op);
        virtual void compute(ComputationIdType cid) const override;

    private:
        virtual std::string node_type_() const override;
        PinType result_pin_;
        BinaryMathOp op_;
    };

} // namespace raytracer::materials::node_shader::nodes
