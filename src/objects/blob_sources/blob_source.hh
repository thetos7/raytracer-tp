#pragma once

#include "points/point3.hh"

namespace raytracer::objects::blob_sources
{
    class BlobSource
    {
    public:
        virtual double get_radius() const = 0;
        virtual points::Point3 get_nearest(points::Point3 target) const = 0;

    private:
        virtual std::ostream &print(std::ostream &out) const = 0;
        friend std::ostream &operator<<(std::ostream &out,
                                        const BlobSource &source);
    };
    std::ostream &operator<<(std::ostream &out, const BlobSource &source);

} // namespace raytracer::objects::blob_sources
