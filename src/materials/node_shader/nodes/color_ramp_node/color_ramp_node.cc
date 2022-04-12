#include "color_ramp_node.hh"

#include <algorithm>
#include <sstream>

namespace raytracer::materials::node_shader::nodes
{
    using ColorStop = ColorRampNode::ColorStop;

    namespace
    {
        bool color_stop_less_than_value(const ColorStop &lhs,
                                        const ColorStop &rhs)
        {
            return lhs.value < rhs.value;
        };
    } // namespace

    ColorRampNode::ColorRampNode(PinAdressMap inputs, StopCollection stops)
        : super_type(inputs)
    {
        if (stops.size() < 2)
        {
            std::ostringstream oss;
            oss << __FILE__ << " line " << __LINE__
                << ": Not enough stops for ColorRampNode.";
            throw std::logic_error(oss.str());
        }

        // IO
        color_pin_ = std::make_shared<ValueProvider>(Vector3::zero(), this);
        outputs_ = {
            { "color", color_pin_ },
        };
        // internal structure
        StopCollection sorted_stops(stops);

        std::sort(sorted_stops.begin(), sorted_stops.end(),
                  color_stop_less_than_value);

        for (size_t i = 1; i < sorted_stops.size(); ++i)
        {
            ranges_.emplace_back(sorted_stops[i - 1], sorted_stops[i]);
        }
        min_value_ = sorted_stops.front().value;
        max_value_ = sorted_stops.back().value;
    }

    void ColorRampNode::compute(ComputationIdType cid) const
    {
        const auto input = std::get<double>(inputs_.at("value")->get(cid));

        if (input < min_value_)
        {
            color_pin_->set(ranges_.front().low.color, cid);
            return;
        }
        if (input >= max_value_)
        {
            color_pin_->set(ranges_.back().high.color, cid);
            return;
        }

        ColorRange range;
        for (const auto &r : ranges_)
        {
            if (input >= r.low.value && input < r.high.value)
            {
                range = r;
                break;
            }
        }
        const auto factor =
            (input - range.low.value) / (range.high.value - range.low.value);
        const auto result =
            range.low.color.lerp_to(range.high.color, factor);

        color_pin_->set(result, cid);
    }

    std::string ColorRampNode::node_type_() const
    {
        return "ColorRampNode";
    }
} // namespace raytracer::materials::node_shader::nodes
