#pragma once

#include "fwd.hh"
#include "node.hh"
#include "node_data.hh"

namespace raytracer::materials::node_shader::nodes
{

    class ValueProvider
    {
    public:
        ValueProvider(NodeData default_value, Node* parent);
        ValueProvider(NodeData default_value);
        virtual NodeData get(ComputationIdType current_cid) const;
        void set(NodeData data, ComputationIdType current_cid);
        void set_parent(Node *parent);

    protected:
        NodeData cache_;
        ComputationIdType cid_;
        Node *parent_;
    };

} // namespace raytracer::materials::node_shader::nodes
