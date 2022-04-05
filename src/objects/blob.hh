#pragma once

#include <memory>
#include <vector>

#include "blob_sources/fwd.hh"
#include "mesh.hh"
#include "object.hh"
#include "points/fwd.hh"

namespace raytracer::objects
{
    class Blob : public Object
    {
    public:
        using SourceCollection =
            std::vector<std::shared_ptr<blob_sources::BlobSource>>;
        Blob(const points::Point3 &center, double size, size_t divisions,
             double threshold, const SourceCollection &sources,
             const MaterialPtr &material);

        virtual std::optional<Intersection>
        intersects_ray(const Ray &ray) const override;
        virtual vectors::Vector3
        get_normal(const Intersection &intersection) const override;
        virtual const materials::MaterialProperties
        get_texture(const Intersection &intersection) const override;

        void build_mesh();

        points::Point3 sample_point_pos(points::Point3i pos) const;
        using Edge = std::pair<points::Point3i, points::Point3i>;
        Edge get_edge(int x, int y, int z, int index);

        std::vector<std::shared_ptr<Triangle>>
        marching_cube_at(size_t x, size_t y, size_t z);

        points::Point3 center;
        double size;
        double div_size;
        points::Point3 bot_back_left_corner;
        size_t divisions;
        size_t sample_line_count;
        size_t plane_points;
        size_t point_count;
        double threshold;
        SourceCollection sources;
        std::optional<Mesh> mesh;
        std::vector<double> point_samples;
        std::vector<vectors::Vector3> sample_normals;

    private:
        virtual std::ostream &print(std::ostream &out) const override;
        std::pair<double, vectors::Vector3>
        blob_value(points::Point3 position) const;
        double source_contribution(double radius, double distance) const;
        size_t cube_index(size_t x, size_t y, size_t z) const;
        size_t cube_index(points::Point3i pos) const;
        int intersection_index(double thresh, int x, int y, int z) const;
        void compute_point_samples();
    };

} // namespace raytracer::objects
