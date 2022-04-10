#pragma once

#include "materials/node_shader/nodes/node.hh"

namespace raytracer::materials::node_shader::nodes
{
    class MixNode : public Node
    {
    public:
        // Inputs:
        // left: Any - left value of mix
        // right: Any - right value of mix
        // factor: double - mixing factor

        // this node returns the result of the linear interpolation between
        // left and right by the factor
        using super_type = Node;

        MixNode(PinAdressMap inputs);
        virtual void compute(ComputationIdType cid) const override;

    private:
        virtual std::string node_type_() const override;
        PinType result_pin_;
    };

} // namespace raytracer::materials::node_shader::nodes
