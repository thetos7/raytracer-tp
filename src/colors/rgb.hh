#pragma once

#include <ostream>

namespace colors
{
    struct RGB
    {
        unsigned int r;
        unsigned int g;
        unsigned int b;
        RGB();
        RGB(unsigned int r, unsigned int g, unsigned int b);
    };

    std::ostream &operator<<(std::ostream &out, const RGB &color);
} // namespace colors
