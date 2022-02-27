#pragma once

#include "points/point3.hh"
#include "vectors/vector3.hh"

namespace raytracer
{
    class Camera
    {
    public:
        Camera(const points::Point3 &position, const points::Point3 &focus,
               const vectors::Vector3 &up, double xFOV, double aspectRatio,
               double zMin);

        const points::Point3 position;
        const points::Point3 focus;
        const vectors::Vector3 up;
        const vectors::Vector3 forward;
        const vectors::Vector3 left;
        const double xFOV;
        const double aspectRatio;
        const double zMin;

    private:
    };
} // namespace raytracer
