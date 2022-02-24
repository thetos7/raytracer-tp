#pragma once

#include <ostream>

namespace colors
{
    struct RGB
    {
        int r;
        int g;
        int b;
        RGB(int r, int g, int b);
    };

    std::ostream &operator<<(const std::ostream &out, RGB &color);
} // namespace colors