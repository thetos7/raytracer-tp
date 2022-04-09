#pragma once

#include <variant>

#include "vectors/vector2.hh"
#include "vectors/vector3.hh"

namespace raytracer::materials::node_shader::nodes
{
    using Vector2 = vectors::Vector2;
    using Vector3 = vectors::Vector3;
    using NodeData = std::variant<double, Vector2, Vector3>;
    using ComputationIdType = size_t;
} // namespace raytracer::materials::node_shader::nodes
