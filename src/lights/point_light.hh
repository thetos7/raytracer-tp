#pragma once

#include "light.hh"
#include "points/point3.hh"
#include "vectors/vector3.hh"

namespace raytracer::lights
{
    class PointLight : public Light
    {
    public:
        PointLight(points::Point3 position, vectors::Vector3 intensity);

        virtual IlluminationResult
        get_illumination(const Intersection &intersection) const override;

        const points::Point3 position;
        const vectors::Vector3 intensity;

    private:
        virtual std::ostream &print(std::ostream &out) const override;
    };
} // namespace raytracer::lights
