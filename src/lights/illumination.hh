#pragma once

#include <optional>

#include "vectors/vector3.hh"

namespace raytracer::lights
{
    class Illumination
    {
    public:
        using LightDirection = std::optional<vectors::Vector3>;
        /** Direction towards the light */
        LightDirection light_direction;
        /** Light intensity on each RGB channel */
        vectors::Vector3 light_intensity;

        Illumination(const LightDirection &light_direction,
                     const vectors::Vector3 &light_intensity);

    private:
    };
} // namespace raytracer::lights
