#include "rgb.hh"

#include <ostream>
#include <string>

namespace colors
{
    RGB::RGB(unsigned int r, unsigned int g, unsigned int b)
        : r{ r }
        , g{ g }
        , b{ b }
    {}

    std::ostream &operator<<(const std::ostream &out, RGB &color)
    {
        return out << "RGB{" << color.r << ", " << color.g << ", " << color.b
                   << "}";
    }
} // namespace colors