#include "rgb.hh"

#include <iostream>
#include <string>

namespace colors
{
    RGB::RGB()
        : RGB{ 0, 0, 0 }
    {}
    RGB::RGB(unsigned int r, unsigned int g, unsigned int b)
        : r{ r }
        , g{ g }
        , b{ b }
    {}

    std::ostream &operator<<(std::ostream &out, const RGB &color)
    {
        return out << "RGB{" << color.r << ", " << color.g << ", " << color.b
                   << "}";
    }
} // namespace colors