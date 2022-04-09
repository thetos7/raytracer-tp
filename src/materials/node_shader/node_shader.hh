#pragma once

#include <optional>
#include <string>
#include <unordered_map>

#include "intersection/intersection.hh"
#include "materials/material_properties.hh"
#include "nodes/node.hh"
#include "nodes/pin_address.hh"
#include "nodes/value_provider.hh"

namespace raytracer::materials::node_shader
{
    class NodeShader
    {
        using Node = nodes::Node;
        using PinAddress = nodes::PinAddress;
        using ValueProvider = nodes::ValueProvider;
        using string = std::string;
        using OutputPinAddressType = std::optional<PinAddress>;
        using OutputPinType = std::shared_ptr<ValueProvider>;
        // TODO if multithreading: make atomic, nodes need to cache multiple
        // results
        using ComputationIdType = size_t;

    public:
        using NodeCollection =
            std::unordered_map<string, std::shared_ptr<Node>>;
        NodeShader(NodeCollection nodes, OutputPinAddressType diffuse_output_,
                   OutputPinAddressType specular_output_,
                   OutputPinAddressType specular_spread_output_,
                   OutputPinAddressType reflectivity_output_);

        MaterialProperties
        compute_material_properties(Intersection intersection);
        ComputationIdType get_era() const;
        std::shared_ptr<nodes::ValueProvider> fetch_pin(PinAddress pin);
        Intersection get_intersection();

    private:
        OutputPinType diffuse_output_;
        OutputPinType specular_output_;
        OutputPinType specular_spread_output_;
        OutputPinType reflectivity_output_;

        NodeCollection nodes_;
        ComputationIdType cid_;
        Intersection current_intersection_;
    };

} // namespace raytracer::materials::node_shader
