#include "binary_math_node.hh"

#include <cmath>
#include <sstream>

#include "utils/overload.hh"

namespace raytracer::materials::node_shader::nodes
{
    namespace
    {
        using utils::overload;
#pragma region operation implementations
        NodeData add_(NodeData lhs, NodeData rhs)
        {
            return std::visit(
                overload{
                    [](double l, double r) -> NodeData { return l + r; },
                    [](Vector2 &l, double r) -> NodeData {
                        return l + Vector2::all(r);
                    },
                    [](Vector3 &l, double r) -> NodeData {
                        return l + Vector3::all(r);
                    },
                    [](double l, Vector2 &r) -> NodeData {
                        return r + Vector2::all(l);
                    },
                    [](double l, Vector3 &r) -> NodeData {
                        return r + Vector3::all(l);
                    },
                    [](Vector2 &l, Vector2 &r) -> NodeData { return r + l; },
                    [](Vector3 &l, Vector3 &r) -> NodeData { return r + l; },
                    [](auto l, auto r) -> NodeData {
                        std::ostringstream oss;
                        oss << __FILE__ << " line " << __LINE__
                            << ": unsupported operands";
                        throw std::logic_error(oss.str());
                    },
                },
                lhs, rhs);
        }

        NodeData sub_(NodeData lhs, NodeData rhs)
        {
            return std::visit(
                overload{
                    [](double l, double r) -> NodeData { return l - r; },
                    [](Vector2 &l, double r) -> NodeData {
                        return l - Vector2::all(r);
                    },
                    [](Vector3 &l, double r) -> NodeData {
                        return l - Vector3::all(r);
                    },
                    [](double l, Vector2 &r) -> NodeData {
                        return -r + Vector2::all(l);
                    },
                    [](double l, Vector3 &r) -> NodeData {
                        return -r + Vector3::all(l);
                    },
                    [](Vector2 &l, Vector2 &r) -> NodeData { return r - l; },
                    [](Vector3 &l, Vector3 &r) -> NodeData { return r - l; },
                    [](auto l, auto r) -> NodeData {
                        std::ostringstream oss;
                        oss << __FILE__ << " line " << __LINE__
                            << ": unsupported operands";
                        throw std::logic_error(oss.str());
                    },
                },
                lhs, rhs);
        }

        NodeData mul_(NodeData lhs, NodeData rhs)
        {
            return std::visit(
                overload{
                    [](double l, double r) -> NodeData { return l * r; },
                    [](Vector2 &l, double r) -> NodeData { return l * r; },
                    [](Vector3 &l, double r) -> NodeData { return l * r; },
                    [](double l, Vector2 &r) -> NodeData { return r * l; },
                    [](double l, Vector3 &r) -> NodeData { return r * l; },
                    [](Vector2 &l, Vector2 &r) -> NodeData { return l * r; },
                    [](Vector3 &l, Vector3 &r) -> NodeData { return l * r; },
                    [](auto l, auto r) -> NodeData {
                        std::ostringstream oss;
                        oss << __FILE__ << " line " << __LINE__
                            << ": unsupported operands";
                        throw std::logic_error(oss.str());
                    },
                },
                lhs, rhs);
        }

        NodeData div_(NodeData lhs, NodeData rhs)
        {
            return std::visit(
                overload{
                    [](double l, double r) -> NodeData { return l * r; },
                    [](Vector2 &l, double r) -> NodeData { return l / r; },
                    [](Vector3 &l, double r) -> NodeData { return l / r; },
                    [](Vector2 &l, Vector2 &r) -> NodeData { return l / r; },
                    [](Vector3 &l, Vector3 &r) -> NodeData { return l / r; },
                    [](auto l, auto r) -> NodeData {
                        std::ostringstream oss;
                        oss << __FILE__ << " line " << __LINE__
                            << ": unsupported operands";
                        throw std::logic_error(oss.str());
                    },
                },
                lhs, rhs);
        }

        NodeData pow_(NodeData lhs, NodeData rhs)
        {
            return std::visit(
                overload{
                    [](double l, double r) -> NodeData {
                        return std::pow(l, r);
                    },
                    [](Vector2 &l, double r) -> NodeData {
                        return Vector2{ std::pow(l.x, r), std::pow(l.y, r) };
                    },
                    [](Vector3 &l, double r) -> NodeData {
                        return Vector3{ std::pow(l.x, r), std::pow(l.y, r),
                                        std::pow(l.z, r) };
                    },
                    [](auto l, auto r) -> NodeData {
                        std::ostringstream oss;
                        oss << __FILE__ << " line " << __LINE__
                            << ": unsupported operands";
                        throw std::logic_error(oss.str());
                    },
                },
                lhs, rhs);
        }

        NodeData dot_(NodeData lhs, NodeData rhs)
        {
            return std::visit(
                overload{
                    [](double l, double r) -> NodeData { return l * r; },
                    [](Vector2 &l, Vector2 &r) -> NodeData { return l.dot(r); },
                    [](Vector3 &l, Vector3 &r) -> NodeData { return l.dot(r); },
                    [](auto l, auto r) -> NodeData {
                        std::ostringstream oss;
                        oss << __FILE__ << " line " << __LINE__
                            << ": unsupported operands";
                        throw std::logic_error(oss.str());
                    },
                },
                lhs, rhs);
        }

        NodeData cross_(NodeData lhs, NodeData rhs)
        {
            return std::visit(overload{
                                  [](Vector3 &l, Vector3 &r) -> NodeData {
                                      return l.cross(r);
                                  },
                                  [](auto l, auto r) -> NodeData {
                                      std::ostringstream oss;
                                      oss << __FILE__ << " line " << __LINE__
                                          << ": unsupported operands";
                                      throw std::logic_error(oss.str());
                                  },
                              },
                              lhs, rhs);
        }
#pragma endregion

        NodeData execute_operation(NodeData lhs, BinaryMathOp op, NodeData rhs)
        {
            // Most likely bad/overengineered code, but it works.
            // (This would surely have been much simpler un Rust...)
            switch (op)
            {
            case BinaryMathOp::ADDITION:
                return add_(lhs, rhs);

            case BinaryMathOp::SUBTRACTION:
                return sub_(lhs, rhs);

            case BinaryMathOp::MULTIPLICATION:
                return mul_(lhs, rhs);

            case BinaryMathOp::DIVISION:
                return div_(lhs, rhs);

            case BinaryMathOp::POWER:
                return pow_(lhs, rhs);

            case BinaryMathOp::DOT_PRODUCT:
                return dot_(lhs, rhs);

            case BinaryMathOp::CROSS_PRODUCT:
                return cross_(lhs, rhs);
            } // switch (op)
            std::ostringstream oss;
            oss << __FILE__ << " line " << __LINE__
                << ": Unknown operation encountered";
            throw std::logic_error(oss.str());
        } // namespace raytracer::materials::node_shader::nodes
    } // namespace

    BinaryMathNode::BinaryMathNode(PinAdressMap inputs, BinaryMathOp op)
        : super_type(inputs)
        , op_(op)
    {
        result_pin_ = std::make_shared<ValueProvider>(0., this);

        outputs_ = {
            { "result", result_pin_ },
        };
    }

    void BinaryMathNode::compute(ComputationIdType cid) const
    {
        const auto lhs = inputs_.at("lhs")->get(cid);
        const auto rhs = inputs_.at("rhs")->get(cid);

        const auto result = execute_operation(lhs, op_, rhs);

        result_pin_->set(result, cid);
    }

    std::string BinaryMathNode::node_type_() const
    {
        return "BinaryMathNode";
    }
} // namespace raytracer::materials::node_shader::nodes
