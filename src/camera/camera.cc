#include "camera.hh"

#include <ostream>

#include "points/point3.hh"
#include "utils/utils.hh"
#include "vectors/vector3.hh"
namespace raytracer
{
    Camera::Camera()
        : fov{ 0 }
        , aspectRatio{ 0 }
        , zMin{ 0 }
    {}
    Camera::Camera(const points::Point3 &position, const points::Point3 &focus,
                   const vectors::Vector3 &up, double fov, double aspectRatio,
                   double zMin)
        : position{ position }
        , focus{ focus }
        , up{ up.normalized() }
        , forward{ (focus - position).normalized() }
        , right{ up.cross(forward).normalized() }
        , fov{ fov }
        , aspectRatio{ aspectRatio }
        , zMin{ zMin }
    {}

    std::ostream &operator<<(std::ostream &out, const Camera &camera)
    {
        if (utils::compact_enabled(out))
            return out << "Camera{ " << camera.position << ", " << camera.focus
                       << ", " << camera.up << ", " << camera.forward << ", "
                       << camera.right << ", " << camera.fov << ", "
                       << camera.aspectRatio << ", " << camera.zMin << " }";

        return out << "Camera{ position: " << camera.position
                   << ", focus: " << camera.focus << ", up: " << camera.up
                   << ", forward: " << camera.forward
                   << ", right: " << camera.right << ", fov: " << camera.fov
                   << ", aspectRatio: " << camera.aspectRatio
                   << ", zMin: " << camera.zMin << " }";
    }
} // namespace raytracer
