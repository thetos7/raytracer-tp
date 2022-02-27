#pragma once

#include <ostream>

#include "points/point3.hh"
#include "vectors/vector3.hh"

namespace raytracer
{
    class Camera
    {
    public:
        Camera(const points::Point3 &position, const points::Point3 &focus,
               const vectors::Vector3 &up, double fov, double aspectRatio,
               double zMin);

        const points::Point3 position;
        const points::Point3 focus;
        const vectors::Vector3 up;
        const vectors::Vector3 forward;
        const vectors::Vector3 left;
        const double fov;
        const double aspectRatio;
        const double zMin;

    private:
    };

    std::ostream &operator<<(std::ostream &out, const Camera &camera);
} // namespace raytracer
