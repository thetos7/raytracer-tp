#include "node_shader.hh"

#include <sstream>
#include <stdexcept>

#include "nodes/constant_value_provider.hh"

namespace raytracer::materials::node_shader
{
    using nodes::ConstantValueProvider;
    using namespace vectors;

    NodeShader::NodeShader(NodeCollection nodes,
                           OutputPinAddressType diffuse_output,
                           OutputPinAddressType specular_output,
                           OutputPinAddressType specular_spread_output,
                           OutputPinAddressType reflectivity_output)
        : nodes_(nodes)
        , cid_(0)
        , current_intersection_()
    {
        using nodes::NodeData;
        for (auto &[k, v] : nodes)
        {
            v->set_context(this);
        }
        for (auto &[k, v] : nodes)
        {
            v->init();
        }

        if (diffuse_output)
        {
            diffuse_output_ = fetch_pin(*diffuse_output);
        }
        else
        {
            diffuse_output_ =
                std::make_shared<ConstantValueProvider>(NodeData(Vector3::zero()));
        }

        if (specular_output)
        {
            specular_output_ = fetch_pin(*specular_output);
        }
        else
        {
            
            specular_output_ = std::make_shared<ConstantValueProvider>(0.);
        }

        if (specular_spread_output)
        {
            specular_spread_output_ = fetch_pin(*specular_spread_output);
        }
        else
        {
            specular_spread_output_ =
                std::make_shared<ConstantValueProvider>(0.);
        }

        if (reflectivity_output)
        {
            reflectivity_output_ = fetch_pin(*reflectivity_output);
        }
        else
        {
            reflectivity_output_ = std::make_shared<ConstantValueProvider>(0.);
        }
    }

    std::shared_ptr<nodes::ValueProvider> NodeShader::fetch_pin(PinAddress pin)
    {
        if (!nodes_.contains(pin.node_name))
        {
            std::ostringstream oss;
            oss << __FILE__ << " line " << __LINE__
                << ": Reference to unknown node `" << pin.node_name << "`.";
            throw std::logic_error(oss.str());
        }

        return nodes_.at(pin.node_name)->get_output(pin.pin_name);
    }

    MaterialProperties
    NodeShader::compute_material_properties(Intersection intersection)
    {
        cid_++;
        current_intersection_ = intersection;

        auto diffuse = std::get<Vector3>(diffuse_output_->get(cid_));
        auto specular = std::get<double>(specular_output_->get(cid_));
        auto specular_spread =
            std::get<double>(specular_spread_output_->get(cid_));
        auto reflectivity = std::get<double>(reflectivity_output_->get(cid_));

        return MaterialProperties{
            diffuse,
            specular,
            specular_spread,
            reflectivity,
        };
    }

    NodeShader::ComputationIdType NodeShader::get_era() const
    {
        return cid_;
    }

    Intersection NodeShader::get_intersection()
    {
        return current_intersection_;
    }
} // namespace raytracer::materials::node_shader
