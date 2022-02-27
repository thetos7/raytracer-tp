#include "intersection.hh"

namespace raytracer
{
    using ObjectPtr = Intersection::ObjectPtr;
    Intersection::Intersection(const Ray ray,
                               const double t, const double u, const double v,
                               ObjectPtr object)
        : ray{ ray }
        , u{ u }
        , v{ v }
        , object{ object }
        , t{ t }
    {}
} // namespace raytracer