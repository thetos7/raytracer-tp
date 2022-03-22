#pragma once

#include "blob_source.hh"
#include "points/point3.hh"

namespace raytracer::objects::blob_sources
{
    class BlobPoint : public BlobSource
    {
    public:
        BlobPoint(double radius, points::Point3 center);
        virtual double get_radius() const override;
        virtual points::Point3 get_nearest(points::Point3) const override;

        double radius;
        points::Point3 center;

    private:
    virtual std::ostream &print(std::ostream &out) const override;
    };

} // namespace raytracer::objects::blob_sources
