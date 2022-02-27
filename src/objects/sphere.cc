#include "sphere.hh"

#include "object.hh"
#include "points/point3.hh"
#include "vectors/vector3.hh"

namespace raytracer
{
    Sphere::Sphere(const points::Point3 &center, double radius,
                   Object::MaterialPtr material)
        : Object{ material }
        , center_{ center }
        , radius_{ radius }
    {}

    double Sphere::intersects_ray(const Ray &ray)
    {
        return -1; // TODO
    }

    vectors::Vector3 Sphere::get_normal(double u, double v)
    {
        return vectors::Vector3::zero(); // TODO
    }
} // namespace raytracer