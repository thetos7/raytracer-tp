#include "intersection_info_node.hh"

namespace raytracer::materials::node_shader::nodes
{
    IntersectionInfoNode::IntersectionInfoNode()
        : super_type({})
        , uv_pin_(std::make_shared<ValueProvider>(Vector2(), this))
        , t_pin_(std::make_shared<ValueProvider>(0, this))
        , ray_origin_pin_(std::make_shared<ValueProvider>(Vector3(), this))
        , ray_direction_pin_(std::make_shared<ValueProvider>(Vector3(), this))
    {
        outputs_ = {
            { "uv", uv_pin_ },
            { "t", t_pin_ },
            { "ray_origin", ray_origin_pin_ },
            { "ray_direction", ray_direction_pin_ },
        };
    }

    void IntersectionInfoNode::compute(ComputationIdType cid) const
    {
        auto intersection = context_->get_intersection();

        uv_pin_->set(intersection.uv, cid);
        t_pin_->set(intersection.t, cid);
        auto &ray_origin_point = intersection.ray.origin;
        Vector3 ray_origin_vec(ray_origin_point.x, ray_origin_point.y,
                               ray_origin_point.z);
        ray_origin_pin_->set(ray_origin_vec, cid);
        ray_direction_pin_->set(intersection.ray.direction, cid);
    }

    std::string IntersectionInfoNode::node_type_() const
    {
        return "IntersectionInfoNode";
    }
} // namespace raytracer::materials::node_shader::nodes
