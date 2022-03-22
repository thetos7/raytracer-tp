#include "blob_source.hh"

namespace raytracer::objects::blob_sources
{
    std::ostream &operator<<(std::ostream &out, const BlobSource &source)
    {
        return source.print(out);
    }
} // namespace raytracer::objects::blob_sources
