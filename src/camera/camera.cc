#include "camera.hh"

namespace raytracer
{
    Camera::Camera(const points::Point3 &position, const points::Point3 &focus,
                   const vectors::Vector3 &up, double xFOV, double yFOV,
                   double zMin)
        : position{ position }
        , focus{ focus }
        , up{ up.normalized() }
        , forward{ (focus - position).normalized() }
        , left{ up.cross(forward).normalized() }
        , xFOV{ xFOV }
        , yFOV{ yFOV }
        , zMin{ zMin }
    {}
} // namespace raytracer
