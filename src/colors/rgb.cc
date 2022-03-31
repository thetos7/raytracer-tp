#include "rgb.hh"

#include <algorithm>
#include <cmath>
#include <ostream>
#include <string>

#include "vectors/vector3.hh"

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

    RGB RGB::gray(unsigned int scale)
    {
        return RGB{ scale, scale, scale };
    }
    RGB RGB::white()
    {
        return RGB::gray(255);
    }
    RGB RGB::black()
    {
        return RGB{};
    }

    RGB RGB::from_linear(vectors::Vector3 linearColor)
    {
        auto clamped = vectors::Vector3{
            std::pow(std::clamp(linearColor.x, 0., 1.), 1 / 2.2),
            std::pow(std::clamp(linearColor.y, 0., 1.), 1 / 2.2),
            std::pow(std::clamp(linearColor.z, 0., 1.), 1 / 2.2),
        };

        auto mapped = clamped * 255;

        return RGB{
            static_cast<unsigned int>(std::round(mapped.x)),
            static_cast<unsigned int>(std::round(mapped.y)),
            static_cast<unsigned int>(std::round(mapped.z)),
        };
    }

    RGB RGB::from_hex(unsigned int code)
    {
        static constexpr auto byte = 0xFF;
        return RGB{
            (code >> 16) & byte,
            (code >> 8) & byte,
            code & byte,
        };
    }

    std::ostream &operator<<(std::ostream &out, const RGB &color)
    {
        return out << "RGB{" << color.r << ", " << color.g << ", " << color.b
                   << "}";
    }
} // namespace colors
