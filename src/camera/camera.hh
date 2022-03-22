#pragma once

#include <iosfwd>

#include "points/point3.hh"
#include "vectors/vector3.hh"

namespace raytracer
{
    class Camera
    {
    public:
        Camera();
        Camera(const points::Point3 &position, const points::Point3 &focus,
               const vectors::Vector3 &up, double fov, double aspectRatio,
               double zMin);

        points::Point3 position;
        points::Point3 focus;
        vectors::Vector3 up;
        vectors::Vector3 forward;
        vectors::Vector3 right;
        double fov;
        double aspectRatio;
        double zMin;

    private:
    };

    std::ostream &operator<<(std::ostream &out, const Camera &camera);
} // namespace raytracer
