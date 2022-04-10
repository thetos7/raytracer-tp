#include "fractal_noise_texture_node.hh"

#include <cmath>

#include "utils/utils.hh"

// implementation basse on the one in the book of shaders
// https://thebookofshaders.com/13/
namespace raytracer::materials::node_shader::nodes
{
    namespace
    {
        using utils::fract;

        double random(Vector2 pos)
        {
            constexpr Vector2 combining_factors{ 25.3548, 59.7468 };
            constexpr double scale_factor = 51634.255352;
            return fract(std::sin(pos.dot(combining_factors) * scale_factor));
        }

        double noise(Vector2 pos)
        {
            Vector2 i = pos.floor();
            Vector2 f = pos - i;
            double a = random(i);
            double b = random(i + Vector2(1.0, 0.0));
            double c = random(i + Vector2(0.0, 1.0));
            double d = random(i + Vector2(1.0, 1.0));

            Vector2 u = f * f * (3.0 - 2.0 * f);

            return utils::lerp(a, b, u.x) + (c - a) * u.y * (1.0 - u.x)
                + (d - b) * u.x * u.y;
        }
    } // namespace

    FractalNoiseTextureNode::FractalNoiseTextureNode(PinAdressMap inputs,
                                                     double scale,
                                                     size_t octaves)
        : super_type(inputs)
        , scale_(scale)
        , octaves_(octaves)
    {
        factor_pin_ = std::make_shared<ValueProvider>(0, this);

        outputs_ = {
            { "factor", factor_pin_ },
        };
    }

    double FractalNoiseTextureNode::fbm(Vector2 pos) const
    {
        double value = 0.0;
        double amplitude = 0.5;
        constexpr double GAIN = 0.4;
        constexpr double LACUNARITY = 2.;

        for (size_t i = 0; i < octaves_; ++i)
        {
            value += amplitude * noise(pos);
            pos *= LACUNARITY;
            amplitude *= GAIN;
        }
        return value;
    }

    void FractalNoiseTextureNode::compute(ComputationIdType cid) const
    {
        const auto uv = std::get<Vector2>(inputs_.at("uv")->get(cid));

        const auto result = fbm(uv * scale_);

        factor_pin_->set(result, cid);
    }

    std::string FractalNoiseTextureNode::node_type_() const
    {
        return "FractalNoiseTextureNode";
    }

} // namespace raytracer::materials::node_shader::nodes
