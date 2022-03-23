#include "blob_point.hh"

#include "utils/utils.hh"

namespace raytracer::objects::blob_sources
{
    BlobPoint::BlobPoint(double radius, points::Point3 center)
        : radius{ radius }
        , center{ center }
    {}

    double BlobPoint::get_radius() const
    {
        return radius;
    }

    points::Point3 BlobPoint::get_nearest(points::Point3) const
    {
        return center;
    }

    std::ostream &BlobPoint::print(std::ostream &out) const
    {
        if (utils::compact_enabled(out))
        {
            return out << "BlobPoint{ " << radius << ", " << center << " }";
        }
        return out << "BlobPoint{ radius: " << radius
                   << ", center: " << center << " }";
    }
} // namespace raytracer::objects::blob_sources
