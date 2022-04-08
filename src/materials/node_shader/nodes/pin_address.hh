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
    };

} // namespace raytracer::materials::node_shader::nodes
