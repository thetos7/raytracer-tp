#pragma once

#include <optional>
#include <string>
#include <unordered_map>

#include "intersection/fwd.hh"
#include "materials/material_properties.hh"
#include "nodes/node.hh"
#include "nodes/pin_address.hh"

namespace raytracer::materials::node_shader
{
    class NodeShader
    {
        using Node = nodes::Node;
        using PinAddress = nodes::PinAddress;
        using string = std::string;
        using OutputPinType = std::optional<PinAddress>;
        // TODO if multithreading: make atomic, nodes need to cache multiple results
        using EraType = size_t;

    public:
        using NodeCollection = std::unordered_map<string, Node>;
        NodeShader(NodeCollection nodes, OutputPinType diffuse_output_,
                   OutputPinType specular_output_,
                   OutputPinType specular_spread_output_,
                   OutputPinType reflectivity_output_);

        MaterialProperties
        compute_material_properties(const Intersection &Intersection);
        EraType get_era() const;

    private:
        OutputPinType diffuse_output_;
        OutputPinType specular_output_;
        OutputPinType specular_spread_output_;
        OutputPinType reflectivity_output_;
        NodeCollection nodes_;
        EraType era_;
    };

} // namespace raytracer::materials::node_shader
