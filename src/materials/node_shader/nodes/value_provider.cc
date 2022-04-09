#include "value_provider.hh"

#include <sstream>

namespace raytracer::materials::node_shader::nodes
{

    ValueProvider::ValueProvider(NodeData default_value)
        : ValueProvider(default_value, nullptr)
    {}

    ValueProvider::ValueProvider(NodeData default_value, Node *parent)
        : cache_(default_value)
        , cid_(0)
        , parent_(parent)
    {}

    NodeData ValueProvider::get(ComputationIdType current_cid) const
    {
        if (current_cid == cid_)
        {
            return cache_;
        }
        if (parent_ == nullptr)
        {
            std::ostringstream oss;
            oss << __FILE__ << " line " << __LINE__
                << ": No parent associated with value provider.";
            throw std::logic_error(oss.str());
        }
        parent_->compute(current_cid);

        if (cid_ != current_cid)
        {
            throw std::logic_error(
                "ValueProvider: `set` not called in parent node");
        }

        return cache_;
    }

    void ValueProvider::set(NodeData data, ComputationIdType current_cid)
    {
        cache_ = data;
        cid_ = current_cid;
    }

    void ValueProvider::set_parent(Node *parent)
    {
        parent_ = parent;
    }
} // namespace raytracer::materials::node_shader::nodes
