#include "int_point3.hh"

#include <ostream>
#include <string>

#include "utils/utils.hh"
#include "vectors/int_vector3.hh"

namespace points
{
    Point3i Point3i::origin()
    {
        return Point3i{ 0, 0, 0 };
    }

    Point3i Point3i::from_vector(const std::vector<int> &v)
    {
        return Point3i{ v[0], v[1], v[2] };
    }

    Point3i &Point3i::operator+=(const vectors::Vector3i &vect)
    {
        x += vect.x;
        y += vect.y;
        z += vect.z;
        return *this;
    }

    Point3i &Point3i::operator-=(const vectors::Vector3i &vect)
    {
        x += vect.x;
        y += vect.y;
        z += vect.z;
        return *this;
    }

    Point3i Point3i::operator+(const vectors::Vector3i &vect) const
    {
        auto copy = *this;
        copy += vect;
        return copy;
    }

    Point3i Point3i::operator-(const vectors::Vector3i &vect) const
    {
        auto copy = *this;
        copy -= vect;
        return copy;
    }

    vectors::Vector3i Point3i::operator-(const Point3i &other) const
    {
        return vectors::Vector3i{ x - other.x, y - other.y, z - other.z };
    }

    std::ostream &operator<<(std::ostream &out, const Point3i &point)
    {
        if (utils::compact_enabled(out))
        {
            return out << "(" << point.x << ", " << point.y << ", " << point.z
                       << ")";
        }
        return out << "Point3i(" << point.x << ", " << point.y << ", " << point.z
                   << ")";
    }
} // namespace points
