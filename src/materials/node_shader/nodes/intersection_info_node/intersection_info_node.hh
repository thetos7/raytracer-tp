#pragma once

#include "materials/node_shader/nodes/node.hh"

namespace raytracer::materials::node_shader::nodes
{
    class IntersectionInfoNode : public Node
    {
    public:
        using super_type = Node;
        IntersectionInfoNode();
        virtual void compute(ComputationIdType cid) const override;

    private:
        virtual std::string node_type_() const override;
        PinType uv_pin_;
        PinType t_pin_;
        PinType ray_origin_pin_;
        PinType ray_direction_pin_;
    };

} // namespace raytracer::materials::node_shader::nodes
