#pragma once

#include "light.hh"
#include "vectors/vector3.hh"

namespace raytracer::lights
{
    class AmbientLight : public Light
    {
    public:
        vectors::Vector3 color;

        AmbientLight(const vectors::Vector3 &color);

        virtual vectors::Vector3
        get_illumination(const Intersection &intersection) const override;

    private:
        virtual std::ostream &print(std::ostream &out) const override;
    };
} // namespace raytracer::lights
