#include "camera.hh"

namespace raytracer
{
    Camera::Camera(const points::Point3 &position, const points::Point3 &focus,
                   const vectors::Vector3 &up, double fov, double aspectRatio,
                   double zMin)
        : position{ position }
        , focus{ focus }
        , up{ up.normalized() }
        , forward{ (focus - position).normalized() }
        , left{ up.cross(forward).normalized() }
        , fov{ fov }
        , aspectRatio{ aspectRatio }
        , zMin{ zMin }
    {}

    std::ostream &operator<<(std::ostream &out, const Camera &camera)
    {
        return out << "Camera{ position: " << camera.position
                   << ", focus: " << camera.focus << ", up: " << camera.up
                   << ", forward: " << camera.forward
                   << ", left: " << camera.left << ", fov: " << camera.fov
                   << ", aspectRatio: " << camera.aspectRatio
                   << ", zMin: " << camera.zMin << " }";
    }
} // namespace raytracer
