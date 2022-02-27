#include "light.hh"

namespace raytracer::lights
{
    std::ostream &operator<<(std::ostream &out, const Light &light)
    {
        return light.print(out);
    }
} // namespace raytracer::lights
