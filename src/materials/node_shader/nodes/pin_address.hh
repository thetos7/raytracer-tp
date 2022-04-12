#pragma once

#include <string>

namespace raytracer::materials::node_shader::nodes
{
    class PinAddress
    {
        using string = std::string;

    public:
        PinAddress(string node_name, string pin_name)
            : node_name{ node_name }
            , pin_name{ pin_name }
        {}
        string node_name;
        string pin_name;
        static PinAddress from_str(std::string str);
    };

} // namespace raytracer::materials::node_shader::nodes
