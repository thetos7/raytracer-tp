#pragma once

#include "materials/node_shader/nodes/node.hh"

namespace raytracer::materials::node_shader::nodes
{
    class VoronoiTextureNode : public Node
    {
    public:
        // Inputs:
        // uv: Vector2 - UV coordinates to sample
        using super_type = Node;

        VoronoiTextureNode(PinAdressMap inputs, size_t size);
        virtual void init() override;
        virtual void compute(ComputationIdType cid) const override;

    private:
        using VoronoiPointCollection = std::vector<Vector2>;
        virtual std::string node_type_() const override;
        PinType factor_pin_;

        VoronoiPointCollection points_;
        double voro_cell_size_;
        ssize_t voro_size_;
        bool initialized_;

        size_t voro_idx(int x, int y) const;
    };

} // namespace raytracer::materials::node_shader::nodes
