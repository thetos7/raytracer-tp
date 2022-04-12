#include "pin_address.hh"

namespace raytracer::materials::node_shader::nodes
{
    PinAddress PinAddress::from_str(std::string str)
    {
        auto dot_idx = str.find('.');
        auto node_name = str.substr(0, dot_idx);
        auto pin_name = str.substr(dot_idx + 1);
        return PinAddress{ node_name, pin_name };
    }
} // namespace raytracer::materials::node_shader::nodes
