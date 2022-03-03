#pragma once

#include "light.hh"
#include "vectors/vector3.hh"

namespace raytracer::lights
{
    class SunLight : public Light
    {
    public:
        vectors::Vector3 direction;
        vectors::Vector3 color;

        SunLight(const vectors::Vector3 &direction,
                 const vectors::Vector3 &color);

        virtual IlluminationResult
        get_illumination(const Intersection &intersection) const override;

    private:
        virtual std::ostream &print(std::ostream &out) const override;
    };
} // namespace raytracer::lights
