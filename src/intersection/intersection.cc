#include "intersection.hh"

namespace raytracer
{
    using ObjectPtr = Intersection::ObjectPtr;
    Intersection::Intersection(const Ray ray, const double t, const double u,
                               const double v, ObjectPtr object)
        : ray{ ray }
        , u{ u }
        , v{ v }
        , object{ object }
        , t{ t }
    {}

    std::ostream &operator<<(std::ostream &out,
                             const Intersection &intersection)
    {
        return out << "Intersection{ ray: " << intersection.ray
                   << ", u: " << intersection.u << ", v: " << intersection.v
                   << ", object: " << *intersection.object
                   << ", t: " << intersection.t << " }";
    }
} // namespace raytracer
