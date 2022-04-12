#include "mix_node.hh"

#include <sstream>

#include "utils/overload.hh"
#include "utils/utils.hh"

namespace raytracer::materials::node_shader::nodes
{
    MixNode::MixNode(PinAdressMap inputs)
        : super_type(inputs)
    {
        result_pin_ = std::make_shared<ValueProvider>(0., this);

        outputs_ = {
            { "result", result_pin_ },
        };
    }

    void MixNode::compute(ComputationIdType cid) const
    {
        using utils::overload;
        const auto l = inputs_.at("left")->get(cid);
        const auto r = inputs_.at("right")->get(cid);
        const auto f = std::get<double>(inputs_.at("factor")->get(cid));

        const auto result = std::visit(
            // visitor
            overload{
                [&f](double l, double r) -> NodeData {
                    return utils::lerp(l, r, f);
                },
                [&f](Vector2 l, Vector2 r) -> NodeData {
                    return l.lerp_to(r, f);
                },
                [&f](Vector3 l, Vector3 r) -> NodeData {
                    return l.lerp_to(r, f);
                },
                [](auto l, auto r) -> NodeData {
                    std::ostringstream oss;
                    oss << __FILE__ << " line " << __LINE__
                        << ": unsupported operands.";
                    throw std::logic_error(oss.str());
                },
            },
            l, r);

        result_pin_->set(result, cid);
    }

    std::string MixNode::node_type_() const
    {
        return "MixNode";
    }

} // namespace raytracer::materials::node_shader::nodes
