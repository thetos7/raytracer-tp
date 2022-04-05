#pragma once

#include "object.hh"
#include "points/point3.hh"
#include "vectors/vector2.hh"
#include "vectors/vector3.hh"

namespace raytracer::objects
{
    class Triangle : public Object
    {
    public:
        // points should be defined in a clockwise direction
        using PointsType = std::array<points::Point3, 3>;
        using NormalsType = std::array<vectors::Vector3, 3>;
        using UvsType = std::array<vectors::Vector2, 3>;

        Triangle();
        Triangle(const PointsType &points, const Object::MaterialPtr &material);
        Triangle(const PointsType &points, const NormalsType &normals,
                 const Object::MaterialPtr &material);
        Triangle(const PointsType &points, const UvsType &uv_map,
                 const Object::MaterialPtr &material);
        Triangle(const PointsType &points, const NormalsType &normals,
                 const UvsType &uv_map, const Object::MaterialPtr &material);
        Triangle(const PointsType &points, const NormalsType &normals,
                 const UvsType &uv_map, bool flat, const Object::MaterialPtr &material);

        virtual std::optional<Intersection>
        intersects_ray(const Ray &ray) const override;

        virtual vectors::Vector3
        get_normal(const Intersection &intersection) const override;

    private:
        virtual std::ostream &print(std::ostream &out) const override;

        PointsType points_;
        NormalsType normals_;
        UvsType uv_map_;
        vectors::Vector3 raw_face_normal_;
        vectors::Vector3 face_normal_;
        bool flat_;
    };

} // namespace raytracer::objects
