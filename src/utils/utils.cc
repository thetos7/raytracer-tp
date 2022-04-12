#include "utils.hh"

#include <cmath>
#include <ostream>

namespace utils
{
    namespace
    {
        inline int get_compact()
        {
            static int i = std::ios_base::xalloc();
            return i;
        }
    } // namespace
    std::ostream &compact_on(std::ostream &out)
    {
        out.iword(get_compact()) = 1;
        return out;
    }

    std::ostream &compact_off(std::ostream &out)
    {
        out.iword(get_compact()) = 0;
        return out;
    }

    bool compact_enabled(std::ostream &out)
    {
        return out.iword(get_compact()) == 1;
    }

    double fract(double x)
    {
        return x - std::floor(x);
    }
} // namespace utils
