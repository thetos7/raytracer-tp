#pragma once

#include "materials/node_shader/nodes/node.hh"

namespace raytracer::materials::node_shader::nodes
{
    class PlanarToSpatialNode : public Node
    {
    public:
        // Inputs:
        // in: Vector2 - vector to convert
        using super_type = Node;

        PlanarToSpatialNode(PinAdressMap inputs);
        virtual void compute(ComputationIdType cid) const override;

    private:
        virtual std::string node_type_() const override;
        PinType out_pin_;
    };

} // namespace raytracer::materials::node_shader::nodes