#pragma once

#include <string>

namespace raytracer::materials::node_shader::nodes
{
    enum class BinaryMathOp
    {
        ADDITION = 0,
        SUBTRACTION,
        MULTIPLICATION,
        DIVISION,
        POWER,
        DOT_PRODUCT,
        CROSS_PRODUCT,
    };

    enum class UnaryMathOp
    {
        NEGATION = 0,
        NORM,
        SQ_NORM,
    };

    const char *math_op_str(UnaryMathOp uop);
    const char *math_op_str(BinaryMathOp bop);
    UnaryMathOp unary_math_op_from_str(std::string str);
    BinaryMathOp binary_math_op_from_str(std::string str);
} // namespace raytracer::materials::node_shader::nodes
