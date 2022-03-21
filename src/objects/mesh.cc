#include "mesh.hh"

#include "intersection/intersection.hh"
#include "utils/utils.hh"

namespace raytracer::objects
{
    Mesh::Mesh(Mesh::TriangleCollection &&triangles, MaterialPtr material)
        : Object(material)
        , triangles_(triangles)

    {}

    std::optional<Intersection> Mesh::intersects_ray(const Ray &ray) const
    {
        std::optional<Intersection> minIntersection;
        for (const auto &tri : triangles_)
        {
            const auto intersection = tri->intersects_ray(ray);
            if (intersection
                && (!minIntersection || minIntersection->t > intersection->t))
            {
                minIntersection = intersection;
            }
        }
        return minIntersection;
    }

    vectors::Vector3 Mesh::get_normal(const Intersection &intersection) const
    {
        return intersection.object->get_normal(intersection);
    }

    std::ostream &Mesh::print(std::ostream &out) const
    {
        if (utils::compact_enabled(out))
        {
            out << "Mesh{ [ ";
            utils::stream_join(out, triangles_, ", ") << " ] }";
            return out;
        }
        out << "Mesh { triangles: [ ";
        utils::stream_join(out, triangles_, ", ") << " ] }";
        return out;
    }
} // namespace raytracer::objects
