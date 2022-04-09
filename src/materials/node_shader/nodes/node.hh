#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <variant>

#include "materials/node_shader/fwd.hh"
#include "materials/node_shader/node_shader.hh"
#include "node_data.hh"
#include "pin_address.hh"
#include "value_provider.hh"

namespace raytracer::materials::node_shader::nodes
{
    class Node
    {
    public:
        using PinMapIndexType = std::string;
        using PinType = std::shared_ptr<ValueProvider>;
        using PinMap = std::unordered_map<PinMapIndexType, PinType>;
        using PinAdressMap = std::unordered_map<PinMapIndexType, PinAddress>;

        Node(PinAdressMap inputs);
        void set_context(NodeShader *context);
        virtual void init();
        virtual void compute(ComputationIdType cid) const = 0;

        std::shared_ptr<ValueProvider> get_output(std::string name) const;

    protected:
        virtual std::string node_type_() const;

        PinAdressMap inputs_adresses_;
        PinMap inputs_;
        PinMap outputs_;
        NodeShader *context_;
    };

} // namespace raytracer::materials::node_shader::nodes
