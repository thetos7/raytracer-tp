#pragma once

#include <ostream>

namespace raytracer::lights
{

    class Light
    {
    public:
    private:
        virtual std::ostream &print(std::ostream &out) const = 0;

        friend std::ostream &operator<<(std::ostream &out, const Light &light);
    };

    std::ostream &operator<<(std::ostream &out, const Light &light);
} // namespace raytracer::lights
