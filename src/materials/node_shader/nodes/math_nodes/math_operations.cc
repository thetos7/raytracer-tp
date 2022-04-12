#include "math_operations.hh"

#include <string>
#include <unordered_map>

namespace raytracer::materials::node_shader::nodes
{
    const char *math_op_str(UnaryMathOp uop)
    {
        constexpr const char *strings[] = {
            "negation",
            "norm",
            "sq_norm",
        };
        return strings[static_cast<size_t>(uop)];
    }

    const char *math_op_str(BinaryMathOp bop)
    {
        constexpr const char *strings[] = {
            "addition", "subtraction", "multiplication", "division",
            "power",    "dot_product", "cross_product",
        };
        return strings[static_cast<size_t>(bop)];
    }

    UnaryMathOp unary_math_op_from_str(std::string str)
    {
        static const std::unordered_map<std::string, UnaryMathOp> map = {
            { "negation", UnaryMathOp::NEGATION },
            { "norm", UnaryMathOp::NORM },
            { "sq_norm", UnaryMathOp::SQ_NORM },
        };
        return map.at(str);
    }

    BinaryMathOp binary_math_op_from_str(std::string str)
    {
        static const std::unordered_map<std::string, BinaryMathOp> map = {
            { "addition", BinaryMathOp::ADDITION },
            { "subtraction", BinaryMathOp::SUBTRACTION },
            { "multiplication", BinaryMathOp::MULTIPLICATION },
            { "division", BinaryMathOp::DIVISION },
            { "power", BinaryMathOp::POWER },
            { "dot_product", BinaryMathOp::DOT_PRODUCT },
            { "cross_product", BinaryMathOp::CROSS_PRODUCT },
        };
        return map.at(str);
    }

} // namespace raytracer::materials::node_shader::nodes
