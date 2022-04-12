#pragma once

#include "materials/node_shader/nodes/node.hh"

namespace raytracer::materials::node_shader::nodes
{
    class WaveTextureNode : public Node
    {
    public:
        // Inputs:
        // uv: Vector2 - Uv coordinate of sample
        using super_type = Node;

        WaveTextureNode(PinAdressMap inputs, double angle = 0.0,
                        double scale = 1.0, double offset = 0.0);
        virtual void compute(ComputationIdType cid) const override;

    private:
        virtual std::string node_type_() const override;

        PinType factor_pin_;
        double scale_;
        double angle_;
        double offset_;
        Vector2 direction_;
    };
} // namespace raytracer::materials::node_shader::nodes
