#pragma once

#include "light.hh"
#include "points/point3.hh"
#include "vectors/vector3.hh"

namespace raytracer::lights
{
    class PointLight : Light
    {
    public:
        PointLight(points::Point3 position, vectors::Vector3 intensity);

        const points::Point3 position;
        const vectors::Vector3 intensity;
    };
} // namespace raytracer::lights
