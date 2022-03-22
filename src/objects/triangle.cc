#include "triangle.hh"

#include <ostream>

#include "intersection/intersection.hh"
#include "ray/ray.hh"
#include "utils/utils.hh"

namespace raytracer::objects
{
    namespace
    {
        vectors::Vector3 compute_face_normal(Triangle::PointsType points)
        {
            return (points[2] - points[1])
                .cross(points[1] - points[0])
                .normalized();
        }
    } // namespace

    Triangle::Triangle(const PointsType &points,
                       const Object::MaterialPtr &material)
        : Object{ material }
        , points_(points)
        , face_normal_{ compute_face_normal(points) }
        , normals_()
    {
        for (auto &n : normals_)
        {
            n = face_normal_;
        }
    }

    Triangle::Triangle(const PointsType &points, const NormalsType &normals,
                       const Object::MaterialPtr &material)
        : Object{ material }
        , points_(points)
        , normals_(normals)
        , face_normal_{ compute_face_normal(points) }
    {}

    std::optional<Intersection> Triangle::intersects_ray(const Ray &ray) const
    {
        // TODO: optimize? (maybe suggested solution in subject is faster, but
        // I'm too dumb to understand it) ray-plane intersection
        using utils::EPSILON;
        const auto denom = face_normal_.dot(ray.direction);
        if (std::abs(denom) < EPSILON)
        {
            return {}; // parallel
        }
        const auto t = (face_normal_.dot(points_[0] - ray.origin)) / denom;
        // checking intersection point is in triangle
        const auto intersection_point = ray.origin + ray.direction * t;
        const auto sideA =
            utils::signum((points_[1] - points_[0])
                              .cross(intersection_point - points_[0])
                              .dot(face_normal_));
        const auto sideB =
            utils::signum((points_[2] - points_[1])
                              .cross(intersection_point - points_[1])
                              .dot(face_normal_));
        if (sideB != sideA)
        {
            return {}; // not in triangle
        }

        const auto sideC =
            utils::signum((points_[0] - points_[2])
                              .cross(intersection_point - points_[2])
                              .dot(face_normal_));
        if (sideC != sideA)
        {
            return {}; // not in triangle
        }
        return Intersection{ ray, t, 0, 0, this };
    }

    vectors::Vector3
    Triangle::get_normal(const Intersection &intersection) const
    {
        // Improvement: Interpolate point normal using intersection position.
        const auto normal = face_normal_;
        if (intersection.ray.direction.dot(normal) > 0)
        {
            return -normal;
        }
        return normal;
    }

    std::ostream &Triangle::print(std::ostream &out) const
    {
        if (utils::compact_enabled(out))
        {
            return out << "Triangle{ [ " << points_[0] << ", " << points_[1]
                       << ", " << points_[2] << " ], [ " << normals_[0] << ", "
                       << normals_[1] << ", " << normals_[2] << " ], "
                       << face_normal_ << " }";
        }

        return out << "Triangle{ points: [ " << utils::compact_on << points_[0]
                   << ", " << points_[1] << ", " << points_[2]
                   << " ], normals: [ " << normals_[0] << ", " << normals_[1]
                   << ", " << normals_[2] << utils::compact_off
                   << " ], face_normal: " << face_normal_ << " }";
    }
} // namespace raytracer::objects
