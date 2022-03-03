#include "illumination.hh"

namespace raytracer::lights
{
    Illumination::Illumination(
        const Illumination::LightDirection &light_direction,
        const vectors::Vector3 &light_intensity)
        : light_direction{ light_direction }
        , light_intensity{ light_intensity }
    {}
} // namespace raytracer::lights
