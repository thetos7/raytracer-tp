#include "triangle.hh"

#include <ostream>

#include "intersection/intersection.hh"
#include "ray/ray.hh"
#include "utils/utils.hh"

namespace raytracer::objects
{
    namespace
    {
        struct TriangleIntersectionData
        {
            /** barycentric u coordinate */
            double bu;
            /** barycentric v coordinate */
            double bv;

            TriangleIntersectionData(double bu, double bv)
                : bu{ bu }
                , bv{ bv }
            {}

            static auto from_storage(Intersection::StoragePtr storage)
            {
                return std::static_pointer_cast<TriangleIntersectionData>(
                    storage);
            }
        };

        vectors::Vector3 compute_raw_face_normal(Triangle::PointsType points)
        {
            return (points[2] - points[1]).cross(points[1] - points[0]);
        }

        vectors::Vector3 compute_face_normal(Triangle::PointsType points)
        {
            return compute_raw_face_normal(points).normalized();
        }
    } // namespace

    Triangle::Triangle()
        : Triangle{ {}, nullptr }
    {}

    Triangle::Triangle(const PointsType &points,
                       const Object::MaterialPtr &material)
        : Object{ material }
        , points_(points)
        , normals_()
        , raw_face_normal_{ compute_raw_face_normal(points) }
        , face_normal_{ raw_face_normal_.normalized() }
        , flat_{ true }
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
        , raw_face_normal_{ compute_raw_face_normal(points) }
        , face_normal_{ raw_face_normal_.normalized() }
        , flat_{ false }
    {}

    std::optional<Intersection> Triangle::intersects_ray(const Ray &ray) const
    {
        double u, v;
        // TODO: optimize? (maybe suggested solution in subject is faster,
        // but I'm too dumb to understand it) ray-plane intersection
        using utils::EPSILON;
        const auto denom_plane = raw_face_normal_.dot(ray.direction);
        if (std::abs(denom_plane) < EPSILON)
        {
            return {}; // parallel
        }
        const auto t =
            (raw_face_normal_.dot(points_[0] - ray.origin)) / denom_plane;

        // checking intersection point is in triangle
        const auto intersection_point = ray.origin + ray.direction * t;

        const auto edge0 = points_[1] - points_[0];
        const auto sideA =
            edge0.cross(intersection_point - points_[0]).dot(raw_face_normal_)
            > 0;
        if (sideA)
        {
            return {};
        }

        const auto edge1 = points_[2] - points_[1];
        const auto sideB = (u = edge1.cross(intersection_point - points_[1])
                                    .dot(raw_face_normal_))
            > 0;

        if (sideB)
        {
            return {}; // not in triangle
        }

        const auto edge2 = points_[0] - points_[2];
        const auto sideC = (v = edge2.cross(intersection_point - points_[2])
                                    .dot(raw_face_normal_))
            > 0;
        if (sideC)
        {
            return {}; // not in triangle
        }

        double denom_bary = raw_face_normal_.dot(raw_face_normal_);
        u /= denom_bary;
        v /= denom_bary;
        // u and v are barycentric coordinates
        return Intersection{
            ray,  t,
            0,    0,
            this, std::shared_ptr<void>(new TriangleIntersectionData{ -u, -v }),
        };
    }

    vectors::Vector3
    Triangle::get_normal(const Intersection &intersection) const
    {
        vectors::Vector3 normal;
        if (flat_)
        {
            normal = face_normal_;
        }
        else
        {
            const auto storage =
                TriangleIntersectionData::from_storage(intersection.storage);
            const auto &u = storage->bu, &v = storage->bv;
            normal =
                normals_[0] * u + normals_[1] * v + normals_[2] * (1. - u - v);
        }

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
                       << normals_[1] << ", " << normals_[2] << " ] }";
        }

        return out << "Triangle{ points: [ " << utils::compact_on << points_[0]
                   << ", " << points_[1] << ", " << points_[2]
                   << " ], normals: [ " << normals_[0] << ", " << normals_[1]
                   << ", " << normals_[2] << utils::compact_off << " ] }";
    }
} // namespace raytracer::objects
