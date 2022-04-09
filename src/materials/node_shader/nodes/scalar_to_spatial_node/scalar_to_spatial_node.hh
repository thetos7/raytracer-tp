#pragma once

#include "materials/node_shader/nodes/node.hh"

namespace raytracer::materials::node_shader::nodes
{
    class ScalarToSpatialNode : public Node
    {
    public:
        // Inputs:
        // in: double - scalar to convert
        using super_type = Node;

        ScalarToSpatialNode(PinAdressMap inputs);
        virtual void compute(ComputationIdType cid) const override;

    private:
        virtual std::string node_type_() const override;
        PinType out_pin_;
    };

} // namespace raytracer::materials::node_shader::nodes