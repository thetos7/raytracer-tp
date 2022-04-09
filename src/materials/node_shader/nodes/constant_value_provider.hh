#pragma once

#include "fwd.hh"
#include "node.hh"
#include "node_data.hh"
#include "value_provider.hh"

namespace raytracer::materials::node_shader::nodes
{

    class ConstantValueProvider : public ValueProvider
    {
    public:
    using super_type = ValueProvider;
        ConstantValueProvider(NodeData value);
        virtual NodeData get(ComputationIdType) const override;
    };

} // namespace raytracer::materials::node_shader::nodes
