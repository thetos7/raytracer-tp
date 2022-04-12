#pragma once

namespace raytracer::materials::node_shader::nodes
{
    class Node;
    class ValueProvider;
    class PinAddress;
    class IntersectionInfoNode;
    class PlanarToSpatialNode;
    class ValueNode;
    class VoronoiTextureNode;
    class ScalarToSpatialNode;
    class ColorRampNode;
    class UnaryMathNode;
    class BinaryMathNode;
    enum class BinaryMathOp;
    enum class UnaryMathOp;
    class MixNode;
    class FractalNoiseTextureNode;
    class WaveTextureNode;
    class ConstructPlanarNode;
    class ConstructSpatialNode;
    class DestructSpatialNode;
    class DestructPlanarNode;
} // namespace raytracer::materials::node_shader::nodes
