#include "node.hh"

#include <sstream>

namespace raytracer::materials::node_shader::nodes
{

    Node::Node(PinAdressMap inputs)
        : inputs_adresses_(inputs)
    {}

    std::string Node::node_type_() const
    {
        return "Node";
    }

    std::shared_ptr<ValueProvider> Node::get_output(std::string name) const
    {
        if (!outputs_.contains(name))
        {
            std::ostringstream oss;
            oss << __FILE__ << " line " << __LINE__ << ": Node `"
                << node_type_() << "` has no output `" << name << "`.";
            throw std::logic_error(oss.str());
        }
        return outputs_.at(name);
    }

    void Node::set_context(NodeShader *context)
    {
        context_ = context;
    }

    void Node::init()
    {
        for (auto &[k, v] : inputs_adresses_)
        {
            inputs_.insert_or_assign(k, context_->fetch_pin(v));
        }
    }

} // namespace raytracer::materials::node_shader::nodes
