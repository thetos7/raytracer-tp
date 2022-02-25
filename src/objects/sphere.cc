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

    virtual double Sphere::intersects_ray(const Ray &ray)
    {
        return -1; // TODO
    }

    virtual vectors::Vector3 Sphere::get_normal(double u, double v)
    {
        return vectors::Vector3::null(); // TODO
    }
} // namespace raytracer