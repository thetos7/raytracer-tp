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

        static RGB gray(unsigned int scale);
        static RGB white();
        static RGB black();
    };

    std::ostream &operator<<(std::ostream &out, const RGB &color);
} // namespace colors
