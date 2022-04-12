#include "unary_math_node.hh"

#include <sstream>

#include "utils/overload.hh"

namespace raytracer::materials::node_shader::nodes
{
    namespace
    {
        using utils::overload;
        NodeData neg_(NodeData value)
        {
            return std::visit(overload{
                                  [](double v) -> NodeData { return -v; },
                                  [](Vector2 v) -> NodeData { return -v; },
                                  [](Vector3 v) -> NodeData { return -v; },
                                  [](auto v) -> NodeData {
                                      std::ostringstream oss;
                                      oss << __FILE__ << " line " << __LINE__
                                          << ": unsupported operand";
                                      throw std::logic_error(oss.str());
                                  },
                              },
                              value);
        }

        NodeData norm_(NodeData value)
        {
            return std::visit(
                overload{
                    [](double v) -> NodeData { return std::abs(v); },
                    [](Vector2 v) -> NodeData { return v.norm(); },
                    [](Vector3 v) -> NodeData { return v.norm(); },
                    [](auto v) -> NodeData {
                        std::ostringstream oss;
                        oss << __FILE__ << " line " << __LINE__
                            << ": unsupported operand";
                        throw std::logic_error(oss.str());
                    },
                },
                value);
        }

        NodeData sq_norm_(NodeData value)
        {
            return std::visit(
                overload{
                    [](double v) -> NodeData { return v * v; },
                    [](Vector2 v) -> NodeData { return v.square_norm(); },
                    [](Vector3 v) -> NodeData { return v.square_norm(); },
                    [](auto v) -> NodeData {
                        std::ostringstream oss;
                        oss << __FILE__ << " line " << __LINE__
                            << ": unsupported operand";
                        throw std::logic_error(oss.str());
                    },
                },
                value);
        }

        NodeData execute_operation(UnaryMathOp op, NodeData value)
        {
            switch (op)
            {
            case UnaryMathOp::NEGATION:
                return neg_(value);

            case UnaryMathOp::NORM:
                return norm_(value);

            case UnaryMathOp::SQ_NORM:
                return sq_norm_(value);
            }
            std::ostringstream oss;
            oss << __FILE__ << " line " << __LINE__
                << ": Unknown operation encountered";
            throw std::logic_error(oss.str());
        }
    } // namespace

    UnaryMathNode::UnaryMathNode(PinAdressMap inputs, UnaryMathOp op)
        : super_type(inputs)
        , op_(op)
    {
        result_pin_ = std::make_shared<ValueProvider>(0., this);

        outputs_ = {
            { "result", result_pin_ },
        };
    }

    void UnaryMathNode::compute(ComputationIdType cid) const
    {
        const auto value = inputs_.at("in")->get(cid);

        const auto result = execute_operation(op_, value);

        result_pin_->set(result, cid);
    }

    std::string UnaryMathNode::node_type_() const
    {
        return "UnaryMathNode";
    }

} // namespace raytracer::materials::node_shader::nodes
