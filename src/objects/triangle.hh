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
        using UvCoord = vectors::Vector2;
        // points should be defined in a clockwise direction
        using PointsType = std::array<points::Point3, 3>;
        using NormalsType = std::array<vectors::Vector3, 3>;
        using UvsType = std::array<UvCoord, 3>;
        static constexpr UvsType DEFAULT_UVS{ UvCoord{ 0, 0 }, UvCoord{ 1, 0 },
                                              UvCoord{ 0, 1 } };

        Triangle();
        Triangle(const PointsType &points, const Object::MaterialPtr &material);
        Triangle(const PointsType &points, const NormalsType &normals,
                 const Object::MaterialPtr &material);
        Triangle(const PointsType &points, const UvsType &uv_map,
                 const Object::MaterialPtr &material);
        Triangle(const PointsType &points, const NormalsType &normals,
                 const UvsType &uv_map, const Object::MaterialPtr &material);
        Triangle(const PointsType &points, const NormalsType &normals,
                 const UvsType &uv_map, bool flat,
                 const Object::MaterialPtr &material);

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
