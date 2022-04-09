#include "constant_value_provider.hh"

namespace raytracer::materials::node_shader::nodes
{
    ConstantValueProvider::ConstantValueProvider(NodeData value)
        : super_type(value)
    {}

    NodeData ConstantValueProvider::get(ComputationIdType) const
    {
        return cache_;
    }
} // namespace raytracer::materials::node_shader::nodes