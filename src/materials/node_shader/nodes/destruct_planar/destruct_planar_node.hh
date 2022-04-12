#pragma once

#include "materials/node_shader/nodes/node.hh"

namespace raytracer::materials::node_shader::nodes
{
    class DestructPlanarNode : public Node
    {
    public:
        // Inputs:
        // uv: Vector2 - Uv coordinate of sample
        using super_type = Node;

        DestructPlanarNode(PinAdressMap inputs);
        virtual void compute(ComputationIdType cid) const override;

    private:
        virtual std::string node_type_() const override;

        PinType x_pin_;
        PinType y_pin_;
    };
} // namespace raytracer::materials::node_shader::nodes
