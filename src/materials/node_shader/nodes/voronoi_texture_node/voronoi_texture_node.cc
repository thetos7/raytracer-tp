#include "voronoi_texture_node.hh"

#include <cmath>

namespace raytracer::materials::node_shader::nodes
{
    namespace
    {
        double randfloat()
        {
            return static_cast<double>(std::rand())
                / static_cast<double>(RAND_MAX);
        }

    } // namespace

    VoronoiTextureNode::VoronoiTextureNode(PinAdressMap inputs, size_t size)
        : super_type(inputs)
        , voro_size_(size)
        , voro_cell_size_(1. / size)
        , points_((size + 2) * (size + 2))
        , initialized_(false)
    {
        factor_pin_ = std::make_shared<ValueProvider>(0., this);
        outputs_ = {
            { "factor", factor_pin_ },
        };
    }

    size_t VoronoiTextureNode::voro_idx(int x, int y) const
    {
        return (y + 1) * (voro_size_ + 2) + (x + 1);
    }

    void VoronoiTextureNode::init()
    {
        super_type::init();

        if (initialized_)
            return;

        for (int y = 0; y < voro_size_; ++y)
            for (int x = 0; x < voro_size_; ++x)
            {
                auto px = randfloat() * voro_cell_size_;
                auto py = randfloat() * voro_cell_size_;
                points_[voro_idx(x, y)] = { px, py };
            }
        for (int x = 0; x < voro_size_; ++x)
        {
            points_[voro_idx(x, -1)] = points_[voro_idx(x, voro_size_ - 1)];
            points_[voro_idx(x, voro_size_)] = points_[voro_idx(x, 0)];
        }
        for (int y = -1; y < voro_size_ + 1; ++y)
        {
            points_[voro_idx(-1, y)] = points_[voro_idx(voro_size_ - 1, y)];
            points_[voro_idx(voro_size_, y)] = points_[voro_idx(0, y)];
        }
        for (int y = -1; y < voro_size_ + 1; ++y)
            for (int x = -1; x < voro_size_ + 1; ++x)
            {
                auto &p = points_[voro_idx(x, y)];
                p.x += x * voro_cell_size_;
                p.y += y * voro_cell_size_;
            }
        initialized_ = true;
    }

    void VoronoiTextureNode::compute(ComputationIdType cid) const
    {
        double nearest_dist = 4;

        auto uv = std::get<Vector2>(inputs_.at("uv")->get(cid)).fract();

        const auto u = uv.x;
        const auto v = uv.y;
        const int cx = static_cast<int>(std::floor(u / voro_cell_size_));
        const int cy = static_cast<int>(std::floor(v / voro_cell_size_));

        for (int ox = -1; ox <= 1; ++ox)
            for (int oy = -1; oy <= 1; ++oy)
            {
                nearest_dist =
                    std::min(nearest_dist,
                             (uv - points_[voro_idx(cx + ox, cy + oy)]).norm());
            }
        const auto dist = nearest_dist / (voro_cell_size_);

        const auto result = std::clamp(dist, 0., 1.);

        factor_pin_->set(result, cid);
    }

    std::string VoronoiTextureNode::node_type_() const
    {
        return "VoronoiTextureNode";
    }
} // namespace raytracer::materials::node_shader::nodes
