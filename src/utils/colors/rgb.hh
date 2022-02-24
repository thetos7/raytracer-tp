#pragma once

#include <ostream>

namespace colors
{
    struct RGB
    {
        unsigned int r;
        unsigned int g;
        unsigned int b;
        RGB(unsigned int r, unsigned int g, unsigned int b);
    };

    std::ostream &operator<<(const std::ostream &out, RGB &color);
} // namespace colors