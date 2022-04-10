#include "mesh.hh"

#define TINYOBJLOADER_IMPLEMENTATION

#include <iostream>

#include "intersection/intersection.hh"
#include "materials/material_properties.hh"
#include "tiny_obj_loader.hh"
#include "utils/utils.hh"

using UvCoord = vectors::Vector2;
// points should be defined in a clockwise direction
using PointsType = std::array<points::Point3, 3>;
using NormalsType = std::array<vectors::Vector3, 3>;
using UvsType = std::array<UvCoord, 3>;

namespace raytracer::objects
{
    Mesh::Mesh(const Mesh::TriangleCollection &triangles)
        : Object(nullptr)
        , triangles_(triangles)

    {}

    Mesh Mesh::loadFromObj(const std::string &path,
                           const Object::MaterialPtr &matPtr, const points::Point3 &center, const double scale /* = 1. */)
    {
        tinyobj::ObjReader reader;
        if (!reader.ParseFromFile(path))
        {
            if (!reader.Error().empty())
            {
                throw std::invalid_argument("Can't read obj file " + reader.Error());
            }
        }
        if (!reader.Warning().empty())
        {
            std::cout << "TinyObjReader: " << reader.Warning();
        }

        auto components = TriangleCollection();

        auto &attrib = reader.GetAttrib();
        auto &shapes = reader.GetShapes();

        // Loop over shapes
        for (size_t s = 0; s < shapes.size(); s++)
        {
            // Loop over faces(polygon)
            size_t index_offset = 0;
            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
            {
                size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
                if (fv != 3)
                {
                    std::cout << "Found non triangle face, not parsing...\n";
                    continue;
                }
                PointsType points;
                bool foundNormals = 0;
                NormalsType normals;
                bool foundUvs = 0;
                UvsType uvs;
                // Loop over vertices in the face.
                for (size_t v = 0; v < fv; v++)
                {
                    // access to vertex
                    auto idx = shapes[s].mesh.indices[index_offset + v];
                    points[v].x =
                        ((double)attrib.vertices[3 * size_t(idx.vertex_index) + 0]) * scale + center.x;
                    points[v].y =
                        ((double)
                            attrib.vertices[3 * size_t(idx.vertex_index) + 1]) * scale + center.y;
                    points[v].z =
                        ((double)
                            attrib.vertices[3 * size_t(idx.vertex_index) + 2]) * scale + center.z;

                    // Check if `normal_index` is zero or positive. negative =
                    // no normal data
                    if (idx.normal_index >= 0)
                    {
                        foundNormals = 1;
                        normals[v].x =
                            (double)attrib
                                .normals[3 * size_t(idx.normal_index) + 0];
                        normals[v].y =
                            (double)attrib
                                .normals[3 * size_t(idx.normal_index) + 1];
                        normals[v].z =
                            (double)attrib
                                .normals[3 * size_t(idx.normal_index) + 2];
                    }

                    // Check if `texcoord_index` is zero or positive. negative =
                    // no texcoord data
                    if (idx.texcoord_index >= 0)
                    {
                        foundUvs = 1;
                        uvs[v].x =
                            (double)attrib
                                .texcoords[2 * size_t(idx.texcoord_index) + 0];
                        uvs[v].y =
                            (double)attrib
                                .texcoords[2 * size_t(idx.texcoord_index) + 1];
                    }
                }
                if (foundNormals && foundUvs)
                    components.push_back(std::make_shared<Triangle>(
                        points, normals, uvs, matPtr));
                else if (foundNormals)
                    components.push_back(
                        std::make_shared<Triangle>(points, normals, matPtr));
                else if (foundUvs)
                    components.push_back(
                        std::make_shared<Triangle>(points, uvs, matPtr));
                else
                    components.push_back(
                        std::make_shared<Triangle>(points, matPtr));
                index_offset += fv;
            }
        }
        return Mesh(components);
    }

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

    const materials::MaterialProperties
    Mesh::get_texture(const Intersection &intersection) const
    {
        return intersection.object->get_texture(intersection);
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
