#pragma once

#include "materials/node_shader/nodes/node.hh"

namespace raytracer::materials::node_shader::nodes
{
    class ColorRampNode : public Node
    {
    public:
        struct ColorStop
        {
            constexpr ColorStop()
                : ColorStop(0, Vector3::zero())
            {}
            constexpr ColorStop(double value, Vector3 color)
                : value(value)
                , color(color)
            {}
            double value;
            Vector3 color;
        };
        // Inputs:
        // value: double - value at which to sample the color
        using super_type = Node;
        using StopCollection = std::vector<ColorStop>;

        ColorRampNode(PinAdressMap inputs, StopCollection stops);
        virtual void compute(ComputationIdType cid) const override;

    private:
        struct ColorRange
        {
            constexpr ColorRange()
                : ColorRange({}, {})
            {}
            constexpr ColorRange(ColorStop low, ColorStop high)
                : low(low)
                , high(high)
            {}
            ColorStop low;
            ColorStop high;
        };
        using RangeCollection = std::vector<ColorRange>;
        virtual std::string node_type_() const override;
        PinType color_pin_;
        RangeCollection ranges_;
        double max_value_;
        double min_value_;
    };

} // namespace raytracer::materials::node_shader::nodes
