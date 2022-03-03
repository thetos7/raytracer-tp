#pragma once

#include <ostream>

#include "vectors/fwd.hh"

namespace raytracer
{
    class Intersection;
    namespace lights
    {

        class Light
        {
        public:
            virtual vectors::Vector3
            get_illumination(const Intersection &intersection) const = 0;

        private:
            virtual std::ostream &print(std::ostream &out) const = 0;

            friend std::ostream &operator<<(std::ostream &out,
                                            const Light &light);
        };

        std::ostream &operator<<(std::ostream &out, const Light &light);
    } // namespace lights
} // namespace raytracer
