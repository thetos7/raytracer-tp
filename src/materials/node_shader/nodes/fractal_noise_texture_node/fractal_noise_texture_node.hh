#pragma once

#include "materials/node_shader/nodes/node.hh"

namespace raytracer::materials::node_shader::nodes
{
    class FractalNoiseTextureNode : public Node
    {
    public:
        // Inputs:
        // uv: Vector2 - Uv coordinate of sample
        using super_type = Node;

        FractalNoiseTextureNode(PinAdressMap inputs, double scale, size_t octaves);
        virtual void compute(ComputationIdType cid) const override;

    private:
        virtual std::string node_type_() const override;
        double fbm(Vector2 pos) const;

        PinType factor_pin_;
        double scale_;
        size_t octaves_;
    };
} // namespace raytracer::materials::node_shader::nodes
