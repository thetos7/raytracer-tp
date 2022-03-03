#pragma once

#include <ostream>

#include "vectors/fwd.hh"

namespace colors
{
    struct RGB
    {
        unsigned int r;
        unsigned int g;
        unsigned int b;
        RGB();
        RGB(unsigned int r, unsigned int g, unsigned int b);

        static RGB gray(unsigned int scale);
        static RGB white();
        static RGB black();
        static RGB from_linear(vectors::Vector3 linearColor);
        static RGB from_hex(unsigned int code);
    };

    std::ostream &operator<<(std::ostream &out, const RGB &color);
} // namespace colors
